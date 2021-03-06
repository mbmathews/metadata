/**
 * File: Duration.h
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

#ifndef DURATION_H_H
#define DURATION_H_H

#include "BaseTypes.h"
namespace GnssMetadata
{
	/**
	* Class represents a duration in time.
	*/
	class Duration: public Object
	{
		
	public:
		enum DurationFormat
		{
			sec,
			msec,
			usec,
			nsec,
			psec
		};

	public:
		Duration( double value =0.0, DurationFormat format = sec)
			: _value( value), _format( format)
		{ }

		Duration( const Duration& rhs) 
			: _value( rhs._value), _format( rhs._format)
		{}

		DurationFormat Format( ) const
		{
			return _format;
		}

		void Value( const double value, DurationFormat fmt = sec )
		{
			_format = fmt;
			_value = value;
		}
		double Value( ) const
		{
			return _value;
		}

		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );

	private:
		DurationFormat _format;
		
		/**
		 * The duration  value.
		 */
		double _value;
		
		
	};
	
}


#endif
