/**
 * File: Metadata.h
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

#ifndef METADATA_H_H
#define METADATA_H_H

#include "AttributedObject.h"
#include "Channel.h"
#include "DataFile.h"
#include "AnyUri.h"
#include "Stream.h"
#include "Session.h"
#include "System.h"
#include "BaseTypes.h"
namespace GnssMetadata
{
	/**
	 * Container class for all GNSS Metadata information. This class is the starting
	 * point for creating metadata for datafiles.
	 */
	class Metadata: public AttributedObject
	{
		
	public:
		Metadata( const String& id) : AttributedObject( id){}
		Metadata() {}
		Metadata(const Metadata& rhs) 
			: AttributedObject( rhs)
		{}	

		const AnyUriList& Includes() const 
		{
			return _includes;
		}
		AnyUriList& Includes()
		{
			return _includes;
		}

		const DataFileList& DataFile( ) const
		{
			return _datafiles;
		}
		DataFileList& DataFile( )
		{
			return _datafiles;
		}

		const ChannelList& Channels( ) const
		{
			return _channels;
		}
		ChannelList& Channels( ) 
		{
			return _channels;
		}

		const StreamList& Stream( ) const
		{
			return _streams;
		}
		StreamList& Stream( )
		{
			return _streams;
		}

		const SessionList& Sessions( ) const
		{
			return _sessions;
		}
		SessionList& Sessions( )
		{
			return _sessions;
		}

		const SystemList& Systems( ) const
		{
			return _systems;
		}
		SystemList& Systems( )
		{
			return _systems;
		}
		
		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
		
	private:
		AnyUriList  _includes;

		DataFileList _datafiles;

		ChannelList  _channels;

		StreamList _streams;
		
		SessionList _sessions;

		SystemList _systems;	
	};
	
}


#endif
