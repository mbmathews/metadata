/**
 * File: AttributedObject.h
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

#ifndef ATTRIBUTEDOBJECT_H_H
#define ATTRIBUTEDOBJECT_H_H

#include "BaseTypes.h"
#include "AnyUri.h"
#include "Comment.h"

namespace GnssMetadata
{
	/**
	 * An attributed object can have comments and artifact URLs associated with it.
	 */
	class AttributedObject: public Object
	{
		
	public:
		AttributedObject( const String& id, bool bIsReference = false) 
			: _id( id), _bIsReference( bIsReference)
		{}
		AttributedObject() 
			: _bIsReference(false) 
		{}
		AttributedObject(const AttributedObject& rhs) 
			: _id( rhs._id), _bIsReference( rhs._bIsReference),
			_comments( rhs._comments), _artifacts(rhs._artifacts)
		{}

		void Id( const String& id )
		{
			_id = id;
		}
		String Id( ) const
		{
			return _id;
		}

		bool IsReference() const 
		{
			return _bIsReference;
		}
		void IsReference( bool bValue)
		{
			_bIsReference = bValue;
		}

		const CommentList& Comments( ) const
		{
			return _comments;
		}
		CommentList& Comments( ) 
		{
			return _comments;
		}

		const AnyUriList& Artifacts( ) const
		{
			return _artifacts;
		}

		AnyUriList& Artifacts( ) 
		{
			return _artifacts;
		}

		/**
		 *  Returns a string representation of the object.
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
		
	private:
		String		_id;
		bool		_bIsReference;
		CommentList _comments;
		AnyUriList  _artifacts;
		
		
		
		
	};
	
}


#endif
