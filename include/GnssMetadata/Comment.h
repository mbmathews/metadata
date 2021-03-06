/**
 * File: Comment.h
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

#ifndef COMMENT_H_H
#define COMMENT_H_H

#include "BaseTypes.h"
#include <list>

namespace GnssMetadata
{
	/**
	* Class defines a comment attribute for GNSS metadata.
	*/
	class Comment: public Object
	{
		
	public:
		enum CommentFormat
		{
			html,
			text
		};
	public:
		/**
		 * Standard constructor.
		 */
		Comment( const String& value, CommentFormat format)
			: _value( value), _format( format)
		{
			
		}

		Comment( const Comment& rhs)
			: _value( rhs._value), _format( rhs._format)
		{}

		/**
		 * Gets the format of the comment.
		 */
		CommentFormat Format( ) const
		{
			return _format;
		}

		/**
		 * Sets the comment value and format.
		 */
		void Value( const String& value, const CommentFormat format )
		{
			_value = value;
		}

		/**
		 * Gets the comments value.
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
		CommentFormat _format;
		
		/**
		 * The comment string value. 
		 */
		String _value;
		
		
	};

	/**
	 * Collection is a list of comments.
	 */
	typedef std::list<Comment> CommentList;
}


#endif
