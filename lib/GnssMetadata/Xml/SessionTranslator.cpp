/**
 * File: SessionTranslator.cpp
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


#include "SessionTranslator.h"
#include <GnssMetadata/Session.h>
#include <GnssMetadata/RfConfiguration.h>
#include <GnssMetadata/Oscillator.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_SessionNodes)
	NODELIST_ENTRY( "scenario",      TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "campaign",		 TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "location",		 TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "contact",		 TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "poc",			 TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "comment",		 TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact",		 TE_SIMPLE_TYPE)
NODELIST_END

SessionTranslator::SessionTranslator() 
: Translator( (NodeEntry*) _SessionNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool SessionTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	const XMLElement* pchild;
	const char* pszValue;

	if( pAdaptor == NULL)
		return false;
	Session session;

	bool retval = false;

	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( session, ctxt, elem))
		return false;

	//Done processing element, if no children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		session.IsReference(true);
	else
	{
		//Parse scenario
		pchild = elem.FirstChildElement("scenario");
		pszValue = (pchild != NULL) ? pchild->GetText() : "";
		session.Scenario(pszValue );

		//Parse campaign
		pchild = elem.FirstChildElement("campaign");
		pszValue = (pchild != NULL) ? pchild->GetText() : "";
		session.Campaign(pszValue );
		
		//Parse location
		pchild = elem.FirstChildElement("location");
		try
		{
			double lat = atof( pchild->Attribute("lat"));
			double lon = atof( pchild->Attribute("lon"));
			double height= atof( pchild->Attribute("height"));
			Location loc(lat, lon, height);
			session.Location( loc);
		}
		catch(...)
		{
			throw TranslationException("Couldn't parse Location element");
		}

		//Parse contact
		pchild = elem.FirstChildElement("contact");
		pszValue = (pchild != NULL) ? pchild->GetText() : "";
		session.Contact(pszValue );

		//Parse poc
		pchild = elem.FirstChildElement("poc");
		pszValue = (pchild != NULL) ? pchild->GetText() : "";
		session.Poc(pszValue );
	}

	//Lastly set the session on the specified object.
	pAdaptor->set( &session);
	return true;
}
/**
 * Write the current object 
 */
void SessionTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, XMLElement & elem )
{
	const Session* psession = dynamic_cast< const Session*>(pObject);
	if( psession == NULL) 
		throw TranslationException("SessionTranslator cannot cast Session object");
	else if( psession->Id().length() == 0)
		return;
	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	if( !psession->IsReference())
	{
		XMLElement* pelem;

		//Write scenario
		pelem = elem.GetDocument()->NewElement( "scenario");
		pelem->SetText( psession->Scenario().c_str());
		pelemc->InsertEndChild(pelem);
		
		//Write campaign
		pelem = elem.GetDocument()->NewElement( "campaign");
		pelem->SetText( psession->Campaign().c_str());
		pelemc->InsertEndChild(pelem);

		//Write location
		pelem = elem.GetDocument()->NewElement( "location");
		char buff[128];
		const Location& llh = psession->Location();
		sprintf(buff,"%0.8lf", llh.Latitude());
		pelem->SetAttribute("lat", buff);
		sprintf(buff,"%0.8lf", llh.Longitude());
		pelem->SetAttribute("lon", buff);
		sprintf(buff,"%0.3lf", llh.Height());
		pelem->SetAttribute("height", buff);
		pelemc->InsertEndChild(pelem);

		//Write conact
		pelem = elem.GetDocument()->NewElement( "contact");
		pelem->SetText( psession->Campaign().c_str());
		pelemc->InsertEndChild(pelem);

		//Write poc
		pelem = elem.GetDocument()->NewElement( "poc");
		pelem->SetText( psession->Campaign().c_str());
		pelemc->InsertEndChild(pelem);
	}
	
	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *psession, ctxt, *pelemc);
	elem.InsertEndChild( pelemc);
}
