/**
 * File: DataFile.h
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

#ifndef DATAFILE_H_H
#define DATAFILE_H_H

#include "BaseTypes.h"
#include "AnyUri.h"
#include "Stream.h"
#include "Session.h"
#include "Date.h"
#include "Frequency.h"
#include "SubFrame.h"
#include "Frame.h"
#include <list>

namespace GnssMetadata
{
	/**
	 * Class defines metadata for a specific data file. 
	 */
	class DataFile  : public AttributedObject
	{
		
	public:
		DataFile( const String& id) : AttributedObject( id){}
		DataFile() {}
		DataFile(const DataFile& rhs) 
			: AttributedObject( rhs)
		{}	

		const AnyUri& Url( ) const
		{
			return _url;
		}
		AnyUri& Url( ) 
		{
			return _url;
		}
		void Url( const AnyUri& url )
		{
			_url = url;
		}


		String Copyright( ) const
		{
			return _copyright;
		}
		void Copyright( const String copyright )
		{
			_copyright = copyright;
		}
		
		Date CreateDate( ) const
		{
			return _createDate;
		}
		void CreateDate( const Date createDate )
		{
			_createDate = createDate;
		}
		
		Date ModDate( ) const
		{
			return _modDate;
		}
		void ModDate( const Date modDate )
		{
			_modDate = modDate;
		}

		const GnssMetadata::Frame& Frame( ) const
		{
			return _frame;
		}
		GnssMetadata::Frame& Frame( ) 
		{
			return _frame;
		}
		void Frame( const GnssMetadata::Frame& frame )
		{
			_frame = frame;
		}

		const GnssMetadata::SubFrame& SubFrame( ) const
		{
			return _subFrame;
		}
		GnssMetadata::SubFrame& SubFrame( ) 
		{
			return _subFrame;
		}
		void SubFrame( const GnssMetadata::SubFrame& subFrame )
		{
			_subFrame = subFrame;
		}


		size_t Offset( ) const
		{
			return _offset;
		}
		void Offset( const size_t offset )
		{
			_offset = offset;
		}

		String Owner( ) const
		{
			return _owner;
		}
		void Owner( const String owner )
		{
			_owner = owner;
		}

		const AnyUri& Previous( ) const
		{
			return _previous;
		}
		AnyUri& Previous( )
		{
			return _previous;
		}
		void Previous( const AnyUri& previous )
		{
			_previous = previous;
		}

		const AnyUri& Next( ) const
		{
			return _next;
		}
		AnyUri& Next( )
		{
			return _next;
		}
		void Next( const AnyUri& next )
		{
			_next = next;
		}

		const Frequency& Rate( ) const
		{
			return _rate;
		}
		Frequency& Rate( ) 
		{
			return _rate;
		}
		void Rate( const Frequency& rate )
		{
			_rate = rate;
		}

		const GnssMetadata::Session& Session( ) const
		{
			return _session;
		}
		GnssMetadata::Session& Session( ) 
		{
			return _session;
		}
		void Session( const GnssMetadata::Session& session )
		{
			_session = session;
		}

		const StreamList& Streams( ) const
		{
			return _streams;
		}
		StreamList& Streams( )
		{
			return _streams;
		}

		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
		
	private:
		/**
		 * url points to the file 
		 */
		AnyUri _url;

		String _copyright;
		
		Date _createDate;
		
		
		/**
		 * Modification date of the datafile.  This is an optional element.
		 */
		Date _modDate;
		
		/**
		 * Previous file URI in the sequence.
		 */
		AnyUri _next;
		
		/**
		 * Byte offset into file for start of stream.
		 */
		size_t _offset;
		
		String _owner;
		
		/**
		 * Previous file URI in the sequence.
		 */
		AnyUri _previous;
		
		Frequency _rate;
		
		GnssMetadata::Session _session;
		
		StreamList _streams;
		
		GnssMetadata::SubFrame _subFrame;
		GnssMetadata::Frame _frame;
	
	};

	typedef std::list<DataFile> DataFileList;
}


#endif
