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
using namespace GnssMetadata;


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
bool XmlProcessor::Load( const String & sfilename, const bool bProcessIncludes, Metadata & metadata )
{
	return false;
}
/**
 * Save the metadata object to the specified XML file.
 */
bool XmlProcessor::Save( const String & sfilename, const Metadata & metadata )
{
	return false;
}

/**
 * Processes the current element within the context of the attributed object.
 */
bool ReadElement(AttributedObject& aobj, Context & ctxt, const tinyxml2::XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	return true;
}
/**
 * Writes the specified metadata object to xml within specified context 
 */
void WriteElement( const Object * pObject, const char* pszName, Context & ctxt, tinyxml2::XMLElement & elem )
{
}
