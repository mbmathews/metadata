/**
 * File: Translator.cpp
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

#include <GnssMetadata/Xml/Translator.h>
#include <GnssMetadata/Xml/XmlProcessor.h>
#include <tinyxml2.h>
using namespace GnssMetadata;
using namespace tinyxml2;


/******************************************************************************
* Translator Implementation
/*****************************************************************************/

/**
 * Processes the current element within the context of the attributed object, delegates
 * out to XmlProcessor to allow other translators to process the data.
 */
bool Translator::ReadElement(AttributedObject& aobj, Context & ctxt, const tinyxml2::XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	//Create a context for attributed object and then
	//process with the translator.
	Context ctxtnew( ctxt.proc, this, &aobj);

	return 	ctxt.proc.ReadElement( ctxtnew, elem, pAdaptor);
}

/**
 * Writes the specified metadata object to xml within specified context 
 */
void Translator::WriteElement( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLElement & elem )
{
	//Create a context for attributed object and then
	//process with the translator.
	Context ctxtnew( ctxt.proc, this, NULL);

	return 	ctxt.proc.WriteElement( pObject, pszName, ctxtnew, elem);
}

/**
 * Reads the attributed object id, comments, and artifacts.
 */
bool Translator::ReadAttributedObject( AttributedObject& aobj, 
		Context& ctxt, const tinyxml2::XMLElement & elem, bool bIdAttributeRequired )
{
	//Grab the ID.
	pcstr szid = elem.Attribute("id");
	if( szid == NULL)
	{
		if( bIdAttributeRequired )
			throw GnssMetadata::TranslationException( "Required id attribute not defined.");
	}
	else
		aobj.Id(szid);

	//Parse the comments.
	const XMLElement* pelem = elem.FirstChildElement("comment");
	for( ;pelem != NULL; pelem = pelem->NextSiblingElement("comment"))
	{
		const char* szFmt = pelem->Attribute("format");
		Comment::CommentFormat fmt = (strcmp(szFmt, "text") == 0)
			? Comment::text : Comment::html;
		Comment comment( pelem->GetText(), fmt);
		aobj.Comments().push_back( comment);
	}

	//Parse the Artifacts.
	pelem = elem.FirstChildElement("artifact");
	for( ;pelem != NULL; pelem = pelem->NextSiblingElement("artifact"))
	{
		AnyUri auri( pelem->GetText());
		aobj.Artifacts().push_back( auri);
	}

	return true;
}

/**
 * Writes the attributed object id, comments, and artifacts.
 */
void Translator::WriteAttributedObject(const AttributedObject& aobj, Context& ctxt, tinyxml2::XMLElement & elem)
{
	//Write the ID.
	elem.SetAttribute( "id", aobj.Id().c_str());

	//Write the comments.
	CommentList::const_iterator citer = aobj.Comments().begin();
	for(; citer != aobj.Comments().end(); citer++)
	{
		XMLElement* pec = elem.GetDocument()->NewElement( "comment");
		const Comment& cmt = *citer;
		const char* szFormat = (cmt.Format() == Comment::text) ? "text":"html";
		pec->SetAttribute("format",szFormat);
		pec->SetText( cmt.Value().c_str());
		elem.InsertEndChild(pec);
	}

	//Write the Artifacts.
	AnyUriList::const_iterator aiter = aobj.Artifacts().begin();
	for(; aiter != aobj.Artifacts().end(); aiter++)
	{
		XMLElement* pec = elem.GetDocument()->NewElement( "artifact");
		pec->SetText( aiter->Value().c_str());
		elem.InsertEndChild(pec);
	}
}
