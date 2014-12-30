/**
 * File: AnyUri.h
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

#ifndef ANYURI_H_H
#define ANYURI_H_H

#include "BaseTypes.h"
#include <list>

namespace GnssMetadata
{
	/**
	 * Class represents an XML any URI type.  
	 */
	class AnyUri: public Object
	{
		
	public:
		AnyUri( const String& value)
			: _value( value)
		{
		}
		AnyUri() {}

		AnyUri( const AnyUri& rhs)
			: _value( rhs._value)
		{
		}

		/**
		 * Returns true if the URI value is defined.
		 */
		bool IsDefined() const { return _value.length() > 0;}

		/**
		 * Sets the URI Value. 
		 */
		void Value( const String& value )
		{
			_value = value;
		}

		/**
		 * Gets the URI Value. 
		 */
		String Value( ) const
		{
			return _value;
		}

	/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
		
	private:
		/**
		 * The URI Value. 
		 */
		String _value;
		
		
	};

	/**
	 * Container is a list of AnyUri objects
	 */
	typedef std::list<AnyUri> AnyUriList;
}


#endif
