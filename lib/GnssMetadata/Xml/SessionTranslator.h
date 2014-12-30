/**
 * File: SessionTranslator.h
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

#ifndef SESSIONTRANSLATOR_H_H
#define SESSIONTRANSLATOR_H_H

#include <GnssMetadata/BaseTypes.h>
#include <GnssMetadata/Xml/Translator.h>

namespace GnssMetadata
{
	/**
	* Class implements xml translation for Session Type.
	*/
	class SessionTranslator : public Translator
	{
		
	public:
		SessionTranslator();

	protected:
		/**
		 * Reads a node from the document and parses into metadata.
		 */
		virtual bool OnRead( Context & ctxt, const tinyxml2::XMLElement & elem, AccessorAdaptorBase* pAdaptor = NULL );
		/**
		 * Write the current object 
		 */
		virtual void OnWrite( const Object * pObject,  pcstr pszName, Context & ctxt, tinyxml2::XMLElement & elem );
		
	};
}
#endif
