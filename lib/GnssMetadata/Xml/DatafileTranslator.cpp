/**
 * File: DatafileTranslator.cpp
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


#include "DatafileTranslator.h"
#include <GnssMetadata/DataFile.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

// Endian Values
static const char* _szEndian[] = {"Big","Little", "Undefined"};
SubFrame::WordEndian ToEndian( const char* pszFmt)
{
	for( int i = 0; i < sizeof( _szEndian); i++)
	{
		if( strcmp( _szEndian[i], pszFmt) == 0)
			return (SubFrame::WordEndian)i;
	}
	return (SubFrame::WordEndian)2;
}

// Sample Format Values
static const char* _szWordAlignment[] = {"Left","Right","Unspecified"};
SubFrame::WordAlignment ToWordAlignment( const char* pszFmt)
{
	for( int i = 0; i < sizeof( _szWordAlignment); i++)
	{
		if( strcmp( _szWordAlignment[i], pszFmt) == 0)
			return (SubFrame::WordAlignment)i;
	}
	return (SubFrame::WordAlignment)2;
}

NODELIST_BEGIN(_DataFileNodes)
	NODELIST_ENTRY( "url",			TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "owner",		TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "copyright",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "createDate",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "modDate",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "session",	TE_SESSION)
	NODELIST_ENTRY( "rate",		TE_FREQUENCY)
	NODELIST_ENTRY( "offset",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "subframe", TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "frame",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "next",		TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "previous",	TE_SYSTEM)
	NODELIST_ENTRY( "stream",	TE_STREAM)
	NODELIST_ENTRY( "comment",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact", TE_SIMPLE_TYPE)
NODELIST_END

DatafileTranslator::DatafileTranslator() 
: Translator( (NodeEntry*) _DataFileNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool DatafileTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	const XMLElement* pchild;
	if( pAdaptor == NULL)
		return false;
	DataFile datafile;

	bool bRetVal = true;

	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( datafile, ctxt, elem, false))
		return false;

	//Done processing element, if no children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		datafile.IsReference(true);
	else
	{
		const char* pszval;

		//Parse url
		pchild = elem.FirstChildElement("url");
		datafile.Url().Value(pchild->GetText());

		//Parse owner
		pchild = elem.FirstChildElement("owner");
		datafile.Owner( (pchild != NULL) ? pchild->GetText():"");
		//Parse copyright
		pchild = elem.FirstChildElement("copyright");
		datafile.Copyright((pchild != NULL) ? pchild->GetText():"");

		//Parse createDate
		pchild = elem.FirstChildElement("createDate");
		datafile.CreateDate( Date(pchild->GetText()));

		//Parse modDate
		pchild = elem.FirstChildElement("modDate");
		if( pchild != NULL)	datafile.ModDate( Date(pchild->GetText()));

		//Parse session
		pchild = elem.FirstChildElement("session");
		AccessorAdaptor<DataFile, Session> adpt( &datafile, &DataFile::Session);
		bRetVal &= ReadElement( datafile, ctxt, *pchild, &adpt);

		//Parse rate
		pchild = elem.FirstChildElement("rate");
		AccessorAdaptor<DataFile, Frequency> adpt1( &datafile, &DataFile::Rate);
		bRetVal &= ReadElement( datafile, ctxt, *pchild, &adpt1);

		//Parse offset
		pchild = elem.FirstChildElement("offset");
		datafile.Offset( (pchild != NULL) ? atol( pchild->GetText()) : 0);

		//Parse subframe
		pchild = elem.FirstChildElement("subframe");
		if( pchild != NULL)
		{
			SubFrame sf;
			//words
			pszval = pchild->Attribute("words");
			sf.Words( (pszval != NULL) ? atoi( pszval) : 0);
			//size
			pszval = pchild->Attribute("size");
			sf.Size(  (pszval != NULL) ? atoi( pszval) : 0);
			//endian
			sf.Endian( ToEndian( pchild->Attribute("endian")));
			//alignment
			sf.Alignment( ToWordAlignment( pchild->Attribute("alignment")));
			datafile.SubFrame( sf);
		}

		//Parse frame
		pchild = elem.FirstChildElement("frame");
		if( pchild != NULL)
		{
			Frame frm;
			//sizeHeader
			pszval = pchild->Attribute("sizeHeader");
			frm.SizeHeader( (pszval != NULL) ? atol( pszval) : 0);
			//sizeFooter
			pszval = pchild->Attribute("sizeFooter");
			frm.SizeFooter( (pszval != NULL) ? atol( pszval) : 0);
			//count
			pszval = pchild->Attribute("count");
			frm.SizeHeader( (pszval != NULL) ? atol( pszval) : 0);
			datafile.Frame(frm);
		}

		//Parse next
		pchild = elem.FirstChildElement("next");
		datafile.Next().Value( (pchild != NULL) ? pchild->GetText() : "");
		
		//Parse previous
		pchild = elem.FirstChildElement("previous");
		datafile.Previous().Value((pchild != NULL) ? pchild->GetText() : "");

		//Parse Streams
		pchild = elem.FirstChildElement("stream");
		for( ;pchild != NULL; pchild = pchild->NextSiblingElement("stream")) 
		{ 
			ListAdaptor<Stream> adapt( datafile.Streams() ); 
			bRetVal &= ReadElement( datafile, ctxt, *pchild, &adapt); 
		} 
	}

	//Lastly set the datafile on the specified object.
	if( bRetVal)
		pAdaptor->set( &datafile);
	return bRetVal;
}
/**
 * Write the current object 
 */
void DatafileTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, XMLElement & elem )
{
	const DataFile* pdatafile = dynamic_cast< const DataFile*>(pObject);
	if( pdatafile == NULL) 
		throw TranslationException("DatafileTranslator cannot cast DataFile object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	if( !pdatafile->IsReference())
	{
		XMLElement* pelem;
		char buff[64];

		//Write url
		pelem = elem.GetDocument()->NewElement( "url");
		pelem->SetText( pdatafile->Url().Value().c_str());
		pelemc->InsertEndChild( pelem);

		//Write owner
		if( pdatafile->Owner().length() > 0)
		{
			pelem = elem.GetDocument()->NewElement( "owner");
			pelem->SetText( pdatafile->Owner().c_str());
			pelemc->InsertEndChild( pelem);
		}

		//Write copyright
		if( pdatafile->Copyright().length() > 0)
		{
			pelem = elem.GetDocument()->NewElement( "copyright");
			pelem->SetText( pdatafile->Copyright().c_str());
			pelemc->InsertEndChild( pelem);
		}

		//Write createDate
		pelem = elem.GetDocument()->NewElement( "createDate");
		pelem->SetText( pdatafile->CreateDate().toString().c_str());
		pelemc->InsertEndChild( pelem);

		//Write modDate
		pelem = elem.GetDocument()->NewElement( "modDate");
		pelem->SetText( pdatafile->CreateDate().toString().c_str());
		pelemc->InsertEndChild( pelem);

		//Write session
		WriteElement( &pdatafile->Session(), "session", ctxt, *pelemc);

		//Write rate
		WriteElement( &pdatafile->Rate(), "rate", ctxt, *pelemc);

		//Write offset
		pelem = elem.GetDocument()->NewElement( "offset");
		sprintf( buff, "%ld", pdatafile->Offset() );
		pelem->SetText( buff );
		pelemc->InsertEndChild( pelem);

		//Write subframe
		if( pdatafile->SubFrame().IsDefined())
		{
			const SubFrame& sf = pdatafile->SubFrame();
			pelem = elem.GetDocument()->NewElement( "subframe");
			sprintf(buff, "%ld", sf.Words());
			pelem->SetAttribute("words", buff);
			sprintf(buff, "%ld", sf.Size());
			pelem->SetAttribute("size",  buff);
			pelem->SetAttribute("endian", _szEndian[ sf.Endian()]);
			pelem->SetAttribute("alignment", _szWordAlignment[ sf.Alignment()] );
			pelemc->InsertEndChild( pelem);
		}

		//Write frame
		if( pdatafile->Frame().IsDefined())
		{
			const Frame& frm = pdatafile->Frame();
			pelem = elem.GetDocument()->NewElement( "frame");
			sprintf(buff, "%ld", frm.SizeHeader());
			pelem->SetAttribute("sizeHeader", buff);
			sprintf(buff, "%ld", frm.SizeFooter());
			pelem->SetAttribute("sizeFooter", buff);
			sprintf(buff, "%ld", frm.Count());
			pelem->SetAttribute("count", buff);			
			pelemc->InsertEndChild( pelem);
		}

		//Write next
		if( pdatafile->Next().Value().length() > 0)
		{
			pelem = elem.GetDocument()->NewElement( "next");
			pelem->SetText(pdatafile->Next().Value().c_str());
			pelemc->InsertEndChild( pelem);
		}

		//Write previous
		if( pdatafile->Previous().Value().length() > 0)
		{
			pelem = elem.GetDocument()->NewElement( "previous");
			pelem->SetText(pdatafile->Previous().Value().c_str());
			pelemc->InsertEndChild( pelem);
		}

		//Write streams
		StreamList::const_iterator iter = pdatafile->Streams().begin();
		for(; iter != pdatafile->Streams().end(); iter++)
		{
			WriteElement( &(*iter), "stream", ctxt, *pelemc);
		}
	}
	
	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *pdatafile, ctxt, *pelemc);
	elem.InsertEndChild( pelemc);
}
