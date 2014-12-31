/**
 * File: StreamTranslator.cpp
 * Author: M.B. Mathews
 *  
 * Copyright(c) 2014 Institute of Navigation
 * http://www.ion.org
 *  
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include "StreamTranslator.h"
#include <GnssMetadata/Stream.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

// Alignment Values
static const char* _szAlignFmts[] = {"Left","Right", "Undefined"};
Stream::StreamAlignment ToAlignmentFormat( const char* pszFmt)
{
	for( int i = 0; i < sizeof( _szAlignFmts); i++)
	{
		if( strcmp( _szAlignFmts[i], pszFmt) == 0)
			return (Stream::StreamAlignment)i;
	}
	return (Stream::StreamAlignment)2;
}

// Sample Format Values
static const char* _szSampleFmts[] = {"IF","IFn","IQ",
	"IQn","InQ","InQn","QI","QIn","QnI","QnIn"};
Stream::SampleFormat ToSampleFormat( const char* pszFmt)
{
	for( int i = 0; i < sizeof( _szSampleFmts); i++)
	{
		if( strcmp( _szSampleFmts[i], pszFmt) == 0)
			return (Stream::SampleFormat)i;
	}
	return (Stream::SampleFormat)2;
}



//NODELIST_BEGIN(_StreamNodes)
//	NODELIST_ENTRY( "url",			TE_SIMPLE_TYPE)
//	NODELIST_ENTRY( "owner",		TE_SIMPLE_TYPE)
//	NODELIST_ENTRY( "copyright",	TE_SIMPLE_TYPE)
//	NODELIST_ENTRY( "createDate",	TE_SIMPLE_TYPE)
//	NODELIST_ENTRY( "modDate",	TE_SIMPLE_TYPE)
//	NODELIST_ENTRY( "session",	TE_SESSION)
//	NODELIST_ENTRY( "rate",		TE_FREQUENCY)
//	NODELIST_ENTRY( "offset",	TE_SIMPLE_TYPE)
//	NODELIST_ENTRY( "subframe", TE_SIMPLE_TYPE)
//	NODELIST_ENTRY( "frame",	TE_SIMPLE_TYPE)
//	NODELIST_ENTRY( "next", TE_DURATION)
//	NODELIST_ENTRY( "previous",	TE_SYSTEM)
//	NODELIST_ENTRY( "stream",	TE_STREAM)
//	NODELIST_ENTRY( "comment",	TE_SIMPLE_TYPE)
//	NODELIST_ENTRY( "artifact", TE_SIMPLE_TYPE)
//NODELIST_END

NODELIST_BEGIN(_StreamNodes)
	NODELIST_ENTRY( "ratefactor",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "quantization",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "packedbits",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "alignment",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "encoding",		TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "format",		TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "delaybias",	TE_DURATION)
	NODELIST_ENTRY( "channel",		TE_CHANNEL)
	NODELIST_ENTRY( "comment",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact", TE_SIMPLE_TYPE)
NODELIST_END

StreamTranslator::StreamTranslator() 
: Translator( (NodeEntry*) _StreamNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool StreamTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	const XMLElement* pchild;
	if( pAdaptor == NULL)
		return false;
	Stream stream;

	bool bRetVal = true;

	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( stream, ctxt, elem))
		return false;

	//Done processing element, if no children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		stream.IsReference(true);
	else
	{
		//Parse ratefactor
		pchild = elem.FirstChildElement("ratefactor");
		stream.RateFactor( atol( pchild->GetText()));

		//Parse quantization
		pchild = elem.FirstChildElement("quantization");
		stream.Quantization( atol( pchild->GetText()));

		//Parse packedbits (optional)
		pchild = elem.FirstChildElement("packedbits");
		if( pchild != NULL)
			stream.Packedbits( atol( pchild->GetText()));
		else
			stream.Packedbits(stream.Quantization());

		//Parse alignment
		if( pchild != NULL)
		{
			pchild = elem.FirstChildElement("alignment");
			stream.Alignment( ToAlignmentFormat(pchild->GetText()));
		}

		//Parse encoding
		pchild = elem.FirstChildElement("encoding");
		stream.Encoding( pchild->GetText());

		//Parse format
		pchild = elem.FirstChildElement("format");
		stream.Format( ToSampleFormat(pchild->GetText()));

		//Parse Delaybias.
		pchild = elem.FirstChildElement("delaybias");
		if( pchild != NULL)
		{
			AccessorAdaptor<Stream, Duration> adpt2( &stream, &Stream::DelayBias);
			bRetVal &= ReadElement( stream, ctxt, *pchild, &adpt2);
		}

		//Parse Channel.
		pchild = elem.FirstChildElement("channel");
		AccessorAdaptor<Stream, Channel> adpt3( &stream, &Stream::Channel);
		bRetVal &= ReadElement( stream, ctxt, *pchild, &adpt3);
	}

	//Lastly set the stream on the specified object.
	if( bRetVal)
		pAdaptor->set( &stream);
	return bRetVal;
}
/**
 * Write the current object 
 */
void StreamTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem )
{
	const Stream* pstream = dynamic_cast< const Stream*>(pObject);
	if( pstream == NULL) 
		throw TranslationException("StreamTranslator cannot cast Stream object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	if( !pstream->IsReference())
	{
		XMLElement* pelem;
		char buff[64];

		//Write ratefactor
		pelem = elem.GetDocument()->NewElement( "ratefactor");
		sprintf( buff, "%ld", pstream->RateFactor() );
		pelem->SetText( buff );
		pelemc->InsertEndChild( pelem);

		//Write quantization
		pelem = elem.GetDocument()->NewElement( "quantization");
		sprintf( buff, "%ld", pstream->Quantization() );
		pelem->SetText( buff );
		pelemc->InsertEndChild( pelem);

		//Write packedbits
		if( pstream->Packedbits() >0 && pstream->Packedbits() != pstream->Quantization())
		{
			pelem = elem.GetDocument()->NewElement( "packedbits");
			sprintf( buff, "%ld", pstream->Packedbits() );
			pelem->SetText( buff );
			pelemc->InsertEndChild( pelem);

			//Write alignment
			pelem = elem.GetDocument()->NewElement( "alignment");
			pelem->SetText( _szAlignFmts[ pstream->Alignment()] );
			pelemc->InsertEndChild( pelem);
		}

		//Write encoding
		pelem = elem.GetDocument()->NewElement( "encoding");
		pelem->SetText( pstream->Encoding().c_str() );
		pelemc->InsertEndChild( pelem);

		//Write format
		pelem = elem.GetDocument()->NewElement( "format");
		pelem->SetText( _szSampleFmts[pstream->Format()] );
		pelemc->InsertEndChild( pelem);
		
		//Write delaybias
		if( pstream->DelayBias().Value() > 0)
			WriteElement( &pstream->DelayBias(), "delaybias", ctxt, *pelemc);

		//Write channel
		WriteElement( &pstream->Channel(), "channel", ctxt, *pelemc);
	}
	
	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *pstream, ctxt, *pelemc);
	elem.InsertEndChild( pelemc);
}
