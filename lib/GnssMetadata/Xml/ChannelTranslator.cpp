/**
 * File: ChannelTranslator.cpp
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


#include "ChannelTranslator.h"
#include <GnssMetadata/Channel.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_ChannelNodes)
	NODELIST_ENTRY( "centerfreq", TE_FREQUENCY)
	NODELIST_ENTRY( "translatedfreq", TE_FREQUENCY)
	NODELIST_ENTRY( "inverted",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "delaybias", TE_DURATION)
	NODELIST_ENTRY( "system",	TE_SYSTEM)
	NODELIST_ENTRY( "comment",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact", TE_SIMPLE_TYPE)
NODELIST_END


ChannelTranslator::ChannelTranslator() 
: Translator( (NodeEntry*) _ChannelNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool ChannelTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	const XMLElement* pchild;
	if( pAdaptor == NULL)
		return false;
	Channel channel;

	bool bRetVal = true;

	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( channel, ctxt, elem))
		return false;

	//Done processing element, if no children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		channel.IsReference(true);
	else
	{
		//Parse CenterFrequency
		pchild = elem.FirstChildElement("centerfreq");
		AccessorAdaptor<Channel, Frequency> adpt( &channel, &Channel::CenterFrequency);
		bRetVal = ReadElement( channel, ctxt, *pchild, &adpt);

		//Parse Parse Translated Frequency
		pchild = elem.FirstChildElement("translatedfreq");
		AccessorAdaptor<Channel, Frequency> adpt1( &channel, &Channel::TranslatedFrequency);
		bRetVal &= ReadElement( channel, ctxt, *pchild, &adpt1);

		//Inverted Element
		pchild = elem.FirstChildElement("inverted");
		bool binverted = pchild != NULL && (strcmp( pchild->GetText(),"false")==0);
		channel.Inverted(binverted);

		//delaybias
		pchild = elem.FirstChildElement("delaybias");
		AccessorAdaptor<Channel, Duration> adpt2( &channel, &Channel::DelayBias);
		bRetVal &= ReadElement( channel, ctxt, *pchild, &adpt2);

		//System
		pchild = elem.FirstChildElement("system");
		AccessorAdaptor<Channel, System> adpt3( &channel, &Channel::System);
		bRetVal &= ReadElement( channel, ctxt, *pchild, &adpt3);
	}

	//Lastly set the channel on the specified object.
	if( bRetVal)
		pAdaptor->set( &channel);
	return bRetVal;
}
/**
 * Write the current object 
 */
void ChannelTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem )
{
	const Channel* pchannel = dynamic_cast< const Channel*>(pObject);
	if( pchannel == NULL) 
		throw TranslationException("ChannelTranslator cannot cast Channel object");

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
		pelemc->InsertEndChild( pelem);

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
