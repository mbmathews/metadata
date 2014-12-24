/**
 * File: Translator.h
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

#ifndef TRANSLATOR_H_H
#define TRANSLATOR_H_H

#include "Context.h"
#include <tinyxml2.h>

namespace GnssMetadata
{
	class Object;
	struct NodeEntry;

	/**
	 * All XML translators derive from this class and conform to the interface specifications
	 */
	class Translator
	{
	protected:
		typedef const char* pcstr;
		
	public:
		Translator( NodeEntry* nodesAllowed) : _nodesAllowed(nodesAllowed)
		{
		}

		/**
		 * Reads the current node and translates into metadata defined
		 * by the subclass.
		 */
		virtual bool OnRead( Context & ctxt, const tinyxml2::XMLElement & elem, AccessorAdaptorBase* pAdaptor = NULL) = 0;
		/**
		 * Write the current object 
		 */
		virtual void OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLElement & elem ) = 0;
	protected:
		/**
		 * Processes the current element within the context of the attributed object, delegates
		 * out to XmlProcessor to allow other translators to process the data.
		 */
		bool ReadElement(AttributedObject& aobj, Context & ctxt, const tinyxml2::XMLElement & elem, AccessorAdaptorBase* pAdaptor);
		
		/**
		 * Writes the specified metadata object to xml within specified context 
		 */
		void WriteElement( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLElement & elem );

		/**
		 * Reads the attributed object id, comments, and artifacts.
		 */
		bool ReadAttributedObject( AttributedObject& aobj, Context& ctxt, const tinyxml2::XMLElement & elem);
		
		/**
		 * Writes the attributed object id, comments, and artifacts.
		 */
		void WriteAttributedObject(const AttributedObject& aobj, Context& ctxt, tinyxml2::XMLElement & elem);
	protected:
		NodeEntry* _nodesAllowed;
	};


	/**
	 * NodeEntry is a single entry in a Node list array.
	 */
	struct NodeEntry
	{ 
		const char* pszNodeName; 
		const char* pszTranslatorId;
	};

	/**
	* Nodelists are defined to specify allowed child nodes within current node.
	* Macros are used to specify nodelists on heap.
	*/
	#define NODELIST_BEGIN(name) static const GnssMetadata::NodeEntry  name[] = { 
	#define NODELIST_ENTRY( nodename, idTranslator) { nodename, idTranslator },
	#define NODELIST_END {"",""} }; 

}
#endif
