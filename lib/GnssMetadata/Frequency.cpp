/**
 * File: Frequency.cpp
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


#include <GnssMetadata/Frequency.h>
#include <string.h>
using namespace GnssMetadata;

/**
 * Returns a string representation of the object.
 */
String Frequency::toString( const String& sFormat )
{
	const char* szFormat[] = { "Hz", "MHz", "GHz", "Ratio"};

	char buff[256];
	switch (_format)
	{
	case Ratio:
	{
		const String& fmt = (sFormat == DefaultFormat) ? "%ld/%ld" : sFormat;
		_snprintf(buff, sizeof(buff), fmt.c_str(), _value.ratioVal.numerator, _value.ratioVal.denominator);
	}
		break;
	default:
	{
		const String& fmt = (sFormat == DefaultFormat) ? "%0.3lf %s" : sFormat;
		_snprintf(buff, sizeof(buff), fmt.c_str(), _value.doubleVal, szFormat[_format]);
	}
		break;
	}
	return String( buff);
}