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
#include <GnssMetadata/Metadata.h>
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
	bool  bRetVal = true;

	Metadata& metadata = dynamic_cast<Metadata&>( *ctxt.pContainer);

	//TODO Process the included metadata references.

	bRetVal &= ReadList<DataFile>(metadata.DataFiles(), "datafile", ctxt, elem);
	bRetVal &= ReadList<Session>(metadata.Sessions(), "session", ctxt, elem);
	bRetVal &= ReadList<Channel>(metadata.Channels(), "channel", ctxt, elem);
	bRetVal &= ReadList<System>(metadata.Systems(), "system", ctxt, elem);
	bRetVal &= ReadList<Stream>(metadata.Streams(), "stream", ctxt, elem);

	//Parse Artifacts and Comments.
	bRetVal &= ReadAttributedObject( metadata, ctxt, elem, false);
	return bRetVal;
}
/**
 * Write the current object 
 */
void MetadataTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, XMLNode & elem )
{
	const Metadata* pmetadata = dynamic_cast< const Metadata*>(pObject);
	if( pmetadata == NULL) 
		throw TranslationException("MetadataTranslator cannot cast Metadata object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	//Set the namespace for the Metadata.
	pelemc->SetAttribute( "xmlns", METADATA_NAMESPACE);

	//TODO Write include elements.

	//Write datafiles
	WriteList<DataFile>( pmetadata->DataFiles(), "datafile", ctxt, *pelemc);
	WriteList<Session>( pmetadata->Sessions(), "session", ctxt, *pelemc);
	WriteList<Channel>( pmetadata->Channels(), "channel", ctxt, *pelemc);
	WriteList<System>( pmetadata->Systems(), "system", ctxt, *pelemc);
	WriteList<Stream>( pmetadata->Streams(), "stream", ctxt, *pelemc);
	
	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *pmetadata, ctxt, *pelemc, false);
	elem.InsertEndChild( pelemc);
}
