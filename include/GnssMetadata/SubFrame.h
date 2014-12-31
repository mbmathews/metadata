/**
 * File: SubFrame.h
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

#ifndef SUBFRAME_H_H
#define SUBFRAME_H_H

#include "BaseTypes.h"

namespace GnssMetadata
{
	class Datafile;

	/**
	 * Class defines a collection of sample words organized into a contiguous block. This is known as a Lump in the 
	 * currente draft specfication.
	 */
	class SubFrame: public Object
	{
		
	public:
		enum WordEndian
		{
			Big,
			Little,
			Undefined
			
		};

		enum WordAlignment
		{
			Left,
			Right,
			Unspecified
		};

	public:
		/**
		 * Default constructor for the subframe.
		 */
		SubFrame( ) : _alignment( Unspecified ), _endian(Undefined), 
			_size(0), _words( 1 )
		{
			
		}

		SubFrame( size_t size, WordEndian endian = Undefined, size_t words =1, WordAlignment align = Unspecified)
			: _alignment( align), _endian( endian), _size(size), _words(words)
		{
		}

		SubFrame( const SubFrame& rhs) 
		: _alignment( rhs._alignment ), _endian(rhs._endian), 
			_size(rhs._size), _words( rhs._words)
		{
			
		}

		/**
		 * Returns true if Subframe state is not in default configuration.
		 */
		bool IsDefined() const 
		{
			return _alignment != Unspecified || _endian != Undefined || _size > 0;
		}

		/**
		 * Gets the word alignment for the subframe.
		 */
		WordAlignment Alignment( ) const
		{
			return _alignment;
		}

		/**
		 * Sets the word alignment for the subframe.
		 */
		void Alignment( const WordAlignment alignment )
		{
			_alignment = alignment;
		}

		/**
		 * Gets the endian ordering of the sample word.
		 */
		WordEndian  Endian( ) const
		{
			return _endian;
		}

		/**
		 * Sets the endian ordering of the sample word.
		 */
		void Endian( const  WordEndian endian )
		{
			_endian = endian;
		}

		/**
		 * Sets the number of sample words in a subframe.
		 */
		void Words( const size_t words )
		{
			_words = words;
		}

		/**
		 * Gets the number of sample words in the subframe.
		 */
		size_t Words( ) const
		{
			return _words;
		}

		/**
		 * Gets the size of the subframe in bits.
		 */
		size_t Size( ) const
		{
			return _size;
		}
		/**
		 * Sets the size of the subframe in bits.  If not defined it defaults to the size
		 * of the multiplexed sample stream.
		 */
		void Size( const size_t size )
		{
			_size = size;
		}

		/**
		 * Calculates the size of the subframe by calculating the word size and adding the specified padding.
		 */
		void CalculateSize( const Datafile* pDatafile, const int bitsPadding = 0 );
		/**
		 * Returns a string representation of the object.
		 */
		virtual String toString( const String & sFormat = DefaultFormat );

		
	private:
		/**
		 * Alignment of data in the subframe.
		 */
		WordAlignment _alignment;
		
		/**
		 * Endian ordering of the data.
		 */
		WordEndian _endian;
		
		/**
		 * Number of bits for multiplex samples.  Defaults to the size of the multipexed stream.
		 */
		size_t _size;
		
		/**
		 * Number of sample words per subframe, default is 1 if not defined.
		 */
		size_t _words;
		
		
	};
	
}


#endif
