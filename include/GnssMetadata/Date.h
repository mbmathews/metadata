/**
 * File: Date.h
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

#ifndef DATE_H_H
#define DATE_H_H

#include "BaseTypes.h"
namespace GnssMetadata
{
	class Date: public Object
	{
		
	public:
		Date() {}
		Date( const char* pszDate) : _sdate( pszDate){}
		Date( int wk, double seconds) 
		{

		}
		const Date& operator=( const Date& rhs){return *this;}
		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
	private:
		String _sdate;
	};
	
}


#endif
