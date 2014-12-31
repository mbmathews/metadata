/**
 * File: SystemTranslator.cpp
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


#include "SystemTranslator.h"
#include <GnssMetadata/System.h>
#include <GnssMetadata/RfConfiguration.h>
#include <GnssMetadata/Oscillator.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_SystemNodes)
	NODELIST_ENTRY( "model",      TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "rfconfig",   TE_RFCONFIG)
	NODELIST_ENTRY( "oscillator", TE_OSCILLATOR)
	NODELIST_ENTRY( "comment",	  TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact",	  TE_SIMPLE_TYPE)
NODELIST_END

static const char* _szTypes[] = {"Processor","Receiver", "Simulator", "Undefined"};
System::SystemType ToSystemType( const char* pszFmt)
{
	for( int i = 0; i < sizeof( _szTypes); i++)
	{
		if( strcmp( _szTypes[i], pszFmt) == 0)
			return (System::SystemType)i;
	}
	return (System::SystemType)3;
}


SystemTranslator::SystemTranslator() 
: Translator( (NodeEntry*) _SystemNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool SystemTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	const XMLElement* pchild;
	if( pAdaptor == NULL)
		return false;
	System system;

	bool retval = false;

	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( system, ctxt, elem))
		return false;

	//Done processing element, if no children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		system.IsReference(true);
	else
	{
		//Parse Type Attribute.
		System::SystemType stype = ToSystemType( elem.Attribute("type"));
		system.Type( stype);

		//Parse Model
		pchild = elem.FirstChildElement("model");
		const char* pszValue = (pchild != NULL) ? pchild->GetText() : "";
		system.Model( pszValue );

		//Parse RfConfig
		pchild = elem.FirstChildElement("rfconfig");
		AccessorAdaptor<System, RfConfiguration> adpt( &system, &System::Rfconfig);
		retval = ReadElement( system, ctxt, *pchild, &adpt);

		//Parse Oscillator
		pchild = elem.FirstChildElement("oscillator");
		AccessorAdaptor<System, Oscillator> adpt1( &system, &System::Oscillator);
		retval &= ReadElement( system, ctxt, *pchild, &adpt1);
	}

	//Lastly set the channel on the specified object.
	pAdaptor->set( &system);
	return true;
}
/**
 * Write the current object 
 */
void SystemTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem )
{
	const System* psystem = dynamic_cast< const System*>(pObject);
	if( psystem == NULL) 
		throw TranslationException("SystemTranslator cannot cast System object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	if( !psystem->IsReference())
	{
		XMLElement* pelem;

		//Write Type Attribute
		pelemc->SetAttribute("type", _szTypes[psystem->Type()]);
		
		//Write Model
		pelem = elem.GetDocument()->NewElement( "model");
		pelem->SetText( psystem->Model().c_str());
		pelemc->InsertEndChild(pelem);

		//Write RfConfig
		if( psystem->Rfconfig().Id().length() > 0)
			WriteElement( &psystem->Rfconfig(), "rfconfig", ctxt, *pelemc);

		//Write Oscillator.
		if( psystem->Oscillator().Id().length() > 0)
			WriteElement( &psystem->Oscillator(), "oscillator", ctxt, *pelemc);
	}
	
	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *psystem, ctxt, *pelemc);
	elem.InsertEndChild( pelemc);
}
