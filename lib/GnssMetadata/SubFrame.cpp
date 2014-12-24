/**
 * File: SubFrame.cpp
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



#include <GnssMetadata/SubFrame.h>
using namespace GnssMetadata;

/**
 * Calculates the size of the subframe by calculating the word size and adding the specified padding.
 */
void CalculateSize( const Datafile* pDatafile, const int bytesPadding = 0 )
{
	throw NotImplementedException();
	
}
/**
 * Returns a string representation of the object.
 */
String SubFrame::toString( const String & sFormat )
{
	return String("Subframe toString not implmented yet.");
}