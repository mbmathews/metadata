/**
 * File: MetadataTranslator.cpp
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


#include "MetadataTranslator.h"
#include <GnssMetadata/Channel.h>
#include <GnssMetadata/Xml/XmlProcessor.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>


using namespace GnssMetadata;
using namespace tinyxml2;

/******************************************************************************
* Metadata Nodes definition
/*****************************************************************************/
NODELIST_BEGIN( _MetadataNodes)
	NODELIST_ENTRY( "datafile", TE_DATAFILE)
	NODELIST_ENTRY( "channel", TE_CHANNEL)
	NODELIST_ENTRY( "system", TE_SYSTEM)
	NODELIST_ENTRY( "stream", TE_STREAM)
	NODELIST_ENTRY( "session", TE_SESSION)
NODELIST_END

// Helper macro Parses the list of an element.
#define PARSE_ELEMENTLIST( idElem, Tobj, list)	\
	pelem = elem.FirstChildElement(idElem); \
	for( ;pelem != NULL; pelem = pelem->NextSiblingElement(idElem)) \
	{ \
		ListAdaptor<Tobj> adapt( list ); \
		bRetVal &= ReadElement( *(ctxt.pContainer), ctxt, *pelem, &adapt); \
	} \


MetadataTranslator::MetadataTranslator() 
: Translator( (NodeEntry*) _MetadataNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool MetadataTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	//Parse the datafiles
	const XMLElement* pelem;
	bool  bRetVal = true;

	Metadata& metadata = dynamic_cast<Metadata&>( *ctxt.pContainer);
	//TODO Process the included metadata references.

	PARSE_ELEMENTLIST( "datafile", DataFile, metadata.DataFiles());	
	PARSE_ELEMENTLIST( "stream", Stream, metadata.Streams());	
	PARSE_ELEMENTLIST( "session", Session, metadata.Sessions());	
	PARSE_ELEMENTLIST( "system", System, metadata.Systems());	
	PARSE_ELEMENTLIST( "channel", Channel, metadata.Channels());	

	//Parse Artifacts and Comments.
	bRetVal &= ReadAttributedObject( metadata, ctxt, elem, false);
	return bRetVal;

}
/**
 * Write the current object 
 */
void MetadataTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, XMLElement & elem )
{
	const Channel* pchannel = dynamic_cast< const Channel*>(pObject);
	if( pchannel == NULL) 
		throw TranslationException("MetadataTranslator cannot cast Channel object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	if( !pchannel->IsReference())
	{
		XMLElement* pelem;

		//Write CenterFrequency
		WriteElement( &pchannel->CenterFrequency(), "centerfreq", ctxt, *pelemc);
	
		//Write Translated Frequency
		WriteElement( &pchannel->TranslatedFrequency(), "translatedfreq", ctxt, *pelemc);

		//Inverted Element
		pelem = elem.GetDocument()->NewElement( "inverted");
		pelem->SetText( (pchannel->Inverted())? "true":"false");
		*pelemc->InsertEndChild( pelem);

		//delaybias
		WriteElement( &pchannel->DelayBias(), "delaybias", ctxt, *pelemc);

		//System
		WriteElement( &pchannel->System(), "system", ctxt, *pelemc);
	}
	
	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *pchannel, ctxt, *pelemc);
	elem.InsertEndChild( pelemc);
}
