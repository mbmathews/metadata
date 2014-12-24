/**
 * File: Duration.cpp
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

#include <GnssMetadata/Duration.h>
using namespace GnssMetadata;

/**
 *  Returns a string representation of the object.
 *  
 */
String Duration::toString( const String & sFormat )
{
	const char* szFormat[]={"sec.", "msec.", "usec.", "nsec.", "psec."};
	char buff[255];

	const String& sfmt = (sFormat == DefaultFormat) ? "%0.3lf %s" : sFormat;
	_snprintf( buff, sizeof(buff), sfmt.c_str(), _value, szFormat[_format]);
	return String(buff);	
}

