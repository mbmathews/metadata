/**
 * File: XmlProcessor.h
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

#ifndef XMLPROCESSOR_H_H
#define XMLPROCESSOR_H_H

#include "../BaseTypes.h"
#include "../Metadata.h"
#include "Context.h"
#include <tinyxml2.h>

namespace GnssMetadata
{
	/**
	 * Processor loads/saves metadata information with XML file format.  The processor reads metadata compliant with the GnssMetadata Schema.
	 */
	class XmlProcessor: public Object
	{
		friend class Translator;
	public:
		/**
		 * Loads a metadata object with data in the specified file.
		 */
		bool Load( const String & sfilename, const bool bProcessIncludes, Metadata & metadata );

		/**
		 * Save the metadata object to the specified XML file.
		 */
		bool Save( const String & sfilename, const Metadata & metadata );

		/**
		 * Returns a reference to the XML Document
		 */
		tinyxml2::XMLDocument& XmlDoc() { return _doc;}
		const tinyxml2::XMLDocument& XmlDoc() const { return _doc;}


		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
	protected:
		/**
		 * Processes the current element within the context of the attributed object.
		 */
		bool ReadElement(AttributedObject& aobj, Context & ctxt, const tinyxml2::XMLElement & elem, AccessorAdaptorBase* pAdaptor);
		
		/**
		 * Writes the specified metadata object to xml within specified context 
		 */
		void WriteElement( const Object * pObject, const char* pszName, Context & ctxt, tinyxml2::XMLElement & elem );



	private:
		tinyxml2::XMLDocument _doc;

		
	};
}
#endif
