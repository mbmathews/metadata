/**
 * File: Frame.h
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

#ifndef FRAME_H_H
#define FRAME_H_H

#include "BaseTypes.h"

namespace GnssMetadata
{
	/**
	 * Frame defines the packing of subframes with the optional 
	 * specification for a header and footer.  This is known as a chunk
	 * in the draft specification.
	 */
	class Frame: public Object
	{
		
	public:
		Frame(): _count(1), _sizeHeader(0), _sizeFooter(0)
		{
		}

		Frame(const Frame& rhs): _count(rhs._count), 
			_sizeHeader(rhs._sizeHeader), _sizeFooter(rhs._sizeFooter)
		{
		}

		/**
		 * Returns true if Frame state is not in default configuration.
		 */
		bool IsDefined() const 
		{
			return _count > 1 || _sizeHeader > 0 || _sizeFooter > 0;
		}

		/**
		 * Gets the count of subframes per frame
		 */
		size_t Count( ) const
		{
			return _count;
		}
		/**
		 * Sets the count of subframes per frame
		 */
		void Count( const size_t count )
		{
			_count = count;
		}

		/**
		 * Gets the size of the header in bytes.
		 */
		size_t SizeHeader( ) const
		{
			return _sizeHeader;
		}
		/**
		 * Sets the size of the header in bytes.
		 */
		void SizeHeader( const size_t sizeHeader )
		{
			_sizeHeader = sizeHeader;
		}

		/**
		 * Gets the size of the frame footer in bytes.
		 */
		size_t SizeFooter( ) const
		{
			return _sizeFooter;
		}
		/**
		 * Sets the size of footer in bytes.
		 */
		void SizeFooter( const size_t sizeFooter )
		{
			_sizeFooter = sizeFooter;
		}

		/**
		 * Returns a string representation of the object.
		 */
		virtual String toString( const String & sFormat = DefaultFormat );

	private:
		/**
		 * Count of subframes per frame.
		 */
		size_t _count;
		
		/**
		 * The size of header in bytes.
		 */
		size_t _sizeHeader;

		/**
		 * Size of footer in bytes
		 */
		size_t _sizeFooter;
		

		
		
	};
	
}


#endif
