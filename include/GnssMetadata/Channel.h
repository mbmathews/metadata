/**
 * File: Channel.h
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

#ifndef CHANNEL_H_H
#define CHANNEL_H_H

#include "AttributedObject.h"
#include "Frequency.h"
#include "Duration.h"
#include "System.h"
#include "BaseTypes.h"
#include <list>

namespace GnssMetadata
{
	/**
	 * Channel defines a finite spectrum of bandwidth that has been translated and processed in some manner resulting in a translated frequency output. Formerly known as band.
	 */
	class Channel: public AttributedObject
	{
		
	public:
		Channel( const String& id) : AttributedObject( id), _inverted(false){}
		Channel() : _inverted(false) {}
		Channel(const Channel& rhs) 
			: AttributedObject( rhs), _centerFrequency(rhs._centerFrequency),
			_translatedFrequency( rhs._translatedFrequency), 
			_delayBias( rhs._delayBias),
			_inverted( rhs._inverted),
			_system( rhs._system)
		{}	

		const Channel& operator=( const Channel& rhs)
		{
			if( &rhs == this)
				return *this;
			AttributedObject::operator =(rhs);
			_centerFrequency = rhs._centerFrequency;
			_translatedFrequency = rhs._translatedFrequency;
			_delayBias = rhs._delayBias;
			_inverted = rhs._inverted;
			_system = rhs._system;
			return *this;
		}

		const Frequency& CenterFrequency( ) const
		{
			return _centerFrequency;
		}
		Frequency& CenterFrequency( ) 
		{
			return _centerFrequency;
		}
		void CenterFrequency( const Frequency& centerFrequency )
		{
			_centerFrequency = centerFrequency;
		}

		const Frequency& TranslatedFrequency( ) const
		{
			return _translatedFrequency;
		}
		Frequency& TranslatedFrequency( )
		{
			return _translatedFrequency;
		}
		void TranslatedFrequency( const Frequency& translatedFrequency )
		{
			_translatedFrequency = translatedFrequency;
		}

		const Duration& DelayBias( ) const
		{
			return _delayBias;
		}
		Duration& DelayBias( ) 
		{
			return _delayBias;
		}
		void DelayBias( const Duration& delayBias )
		{
			_delayBias = delayBias;
		}

		bool Inverted( ) const
		{
			return _inverted;
		}
		void Inverted( const bool inverted )
		{
			_inverted = inverted;
		}
		void System( const GnssMetadata::System& system )
		{
			_system = system;
		}
		GnssMetadata::System System( ) const
		{
			return _system;
		}
		GnssMetadata::System& System( )
		{
			return _system;
		}

		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
		
	private:
		Frequency _centerFrequency;
		Frequency _translatedFrequency;
		Duration  _delayBias;
		
		/**
		 * True if spectrum is inverted. Default is false.
		 */
		bool _inverted;
		
		GnssMetadata::System _system;
		
		
		
	};

	typedef std::list<Channel> ChannelList;
}


#endif
