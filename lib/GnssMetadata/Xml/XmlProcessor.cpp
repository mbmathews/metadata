/**
 * File: XmlProcessor.cpp
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


#include <GnssMetadata/Xml/XmlProcessor.h>
#include "MetadataTranslator.h"
#include "StreamTranslator.h"
#include "ChannelTranslator.h"
#include "FrequencyTranslator.h"
#include "DatafileTranslator.h"
#include "DurationTranslator.h"
#include "SystemTranslator.h"
#include "SessionTranslator.h"
#include "RfConfigTranslator.h"
#include "OscillatorTranslator.h"
#include "XmlDefs.h"
using namespace GnssMetadata;
using namespace tinyxml2;



/******************************************************************************
* Translator Lookup Implementation
/*****************************************************************************/



/**
 * Define a static array of translators.
 */
static struct TranslatorEntry
{
	TranslatorId id;
	Translator& translator;
} _Translators[] =  
{
	TE_FREQUENCY, *(new FrequencyTranslator()),
	TE_DURATION, *(new DurationTranslator()),
	TE_STREAM, *(new StreamTranslator()),
	TE_CHANNEL, *(new ChannelTranslator()),
	TE_DATAFILE, *(new DatafileTranslator()),
	TE_SYSTEM, *(new SystemTranslator()),
	TE_SESSION, *(new SessionTranslator()),
	TE_RFCONFIG, *(new RfConfigTranslator()),
	TE_OSCILLATOR, *(new OscillatorTranslator()), 
	TE_METADATA, *(new MetadataTranslator())
};
#define COUNT_TRANSLATORS (sizeof(_Translators)/sizeof(TranslatorEntry))

Translator& TranslatorFromId( TranslatorId id)
{
	for( int i = 0; i < COUNT_TRANSLATORS; i++)
	{
		if( id == _Translators[i].id)
			return _Translators[i].translator;
	}
	
	throw GnssMetadata::OutOfRangeException( "Invalid translator ID");
}

TranslatorId TranslatorIdFromElemName( const char* szNodeName, NodeEntry* pNodes)
{
	//Iterate to the end of the node entries.
	while( pNodes->idTranslator != TE_END)
	{
		if( strcmp( szNodeName, pNodes->pszNodeName) == 0)
		{
			return pNodes->idTranslator;
		}
		
		//Onto next node.
		pNodes++;
	}
	return TE_END;

}


/******************************************************************************
* XmlProcessor Implementation
/*****************************************************************************/


/**
 * Returns a string representation of the object.
 */
String XmlProcessor::toString( const String & sFormat )
{
	return "XmlProcessor";
}

/**
 * Loads a metadata object with data in the specified file.
 */
bool XmlProcessor::Load( const char* szFilename, const bool bProcessIncludes, Metadata & metadata )
{
	tinyxml2::XMLDocument doc;
	XMLError err = doc.LoadFile( szFilename);
	if( err != XML_SUCCESS)
		throw TranslationException( "Tiny XML Parsing Error", err);

	//Find the metadata element. There should be only one per file.
	const XMLElement* pmetadata = doc.FirstChildElement( "metadata");
	if( pmetadata == NULL)
		throw TranslationException("Metadata element not found in file");


	Context ctxt( *this, NULL, &metadata);
	Translator& trans = TranslatorFromId( TE_METADATA);

	//Note the metadata translator does not create 
	//a new metadata object.
	bool bRetVal = trans.OnRead( ctxt, *pmetadata, NULL);
	if( bRetVal && bProcessIncludes)
	{
		//Todo, process includes.
	}

	return bRetVal;

}
/**
 * Save the metadata object to the specified XML file.
 */
bool XmlProcessor::Save( const char* szFilename, const Metadata & metadata )
{
	return false;
}

/**
 * Processes the current element within the context of the attributed object.
 */
bool XmlProcessor::ReadElement( Context & ctxt, const tinyxml2::XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	TranslatorId id = TE_END;
	const char* szNodeName = elem.Name();

	//Use the current translator if available to lookup appropriate
	//translator for the current element.   If not available,
	//do a global search.
	if( ctxt.pParent != NULL)
	{
		id = TranslatorIdFromElemName( szNodeName, ctxt.pParent->GetAllowedNodes() );	
	}
	else //Do a global lookup.  
	{
		for( int i = 0; i < COUNT_TRANSLATORS && id == TE_END; i++)
		{
			NodeEntry* pNodes = _Translators[i].translator.GetAllowedNodes();
			if(pNodes == NULL) continue;

			id = TranslatorIdFromElemName( szNodeName, pNodes);	
		}
	}

	//Get the translator and attempt to process the current
	//element.
	Translator& trans = TranslatorFromId( id);
	return trans.OnRead( ctxt, elem, pAdaptor);
}
/**
 * Writes the specified metadata object to xml within specified context 
 */
void XmlProcessor::WriteElement( const Object * pObject, const char* pszName, Context & ctxt, tinyxml2::XMLElement & elem )
{
}
