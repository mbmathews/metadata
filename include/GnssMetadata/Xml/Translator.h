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
	class  Object;
	struct NodeEntry;
	struct AccessorAdaptorBase;

	/**
	 * All XML translators derive from this class and conform to the interface specifications
	 */
	class Translator
	{
		friend class XmlProcessor;
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
		* Accesor returns the array of allowed xml nodes for this
		* instance of a translator.  Translators are associated with a xml
		* element, and provides the information on valid sub-elements, if any.
		* return NULL If sub-elements are not allowed.
		*/
		NodeEntry* GetAllowedNodes() const { return _nodesAllowed;}

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
		static bool ReadAttributedObject( AttributedObject& aobj, Context& ctxt, const tinyxml2::XMLElement & elem, bool bIdAttributeRequired = true);
		
		/**
		 * Writes the attributed object id, comments, and artifacts.
		 */
		static void WriteAttributedObject(const AttributedObject& aobj, Context& ctxt, tinyxml2::XMLElement & elem);

	private:
		NodeEntry* _nodesAllowed;
	};

}
#endif
