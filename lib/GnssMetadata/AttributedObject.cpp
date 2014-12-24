/**
 * File: AttributedObject.cpp
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

#include <GnssMetadata/AttributedObject.h>
using namespace GnssMetadata;

/**
 *This should be defined in basetypes.cpp, but that file
 *does not currently exist.
 */
const String Object::DefaultFormat = "";


/**
 *  Returns a string representation of the object.
 *  
 */
String AttributedObject::toString( const String & sFormat  )
{
	return _id;
}
