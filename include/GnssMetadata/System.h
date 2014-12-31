/**
 * File: System.h
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

#ifndef SYSTEM_H_H
#define SYSTEM_H_H

#include "AttributedObject.h"
#include "RfConfiguration.h"
#include "Oscillator.h"
#include "BaseTypes.h"
#include <list>

namespace GnssMetadata
{
	/**
	 * Class defines system metadata attributes.
	 */
	class System: public AttributedObject
	{
	public:
		enum SystemType
		{
			Processor,
			Receiver,
			Simulator,
			Undefined
		};
	public:
		System( const String& id = "", bool bIsReference = false, SystemType type=Undefined) 
			: AttributedObject( id, bIsReference), _type( type) {}
		System(const System& rhs) 
			: AttributedObject( rhs), _type( rhs._type), _model( rhs._model),
			_oscillator( rhs._oscillator), _rfconfig( rhs._rfconfig){}		
		const System& operator=( const System& rhs)
		{
			if( &rhs == this)
				return *this;
			AttributedObject::operator =(rhs);
			_type = rhs._type;
			_model = rhs._model;
			_oscillator = rhs._oscillator;
			_rfconfig = rhs._rfconfig;
			return *this;
		}

		/**
		 * Gets the system model information.
		 */
		String Model( ) const
		{
			return _model;
		}
		/**
		 * Sets the system model information.
		 */
		void Model( const String model )
		{
			_model = model;
		}

		const GnssMetadata::Oscillator& Oscillator( ) const
		{
			return _oscillator;
		}

		GnssMetadata::Oscillator& Oscillator( )
		{
			return _oscillator;
		}
		void Oscillator( const GnssMetadata::Oscillator& oscillator )
		{
			_oscillator = oscillator;
		}

		const RfConfiguration& Rfconfig( ) const
		{
			return _rfconfig;
		}
		RfConfiguration& Rfconfig( )
		{
			return _rfconfig;
		}

		void Rfconfig( const RfConfiguration& rfconfig )
		{
			_rfconfig = rfconfig;
		}
		/**
		 * Sets the System type.
		 */
		void Type( const SystemType type )
		{
			_type = type;
		}
		/**
		 * Gets the System type.
		 */
		SystemType Type( ) const
		{
			return _type;
		}

		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
		
	private:
		/**
		 * Specifies the general type of the system responsible for producing the data.
		 */
		SystemType _type;

		/**
		 * Specifies the model information for the system.
		 */
		String _model;
		
		/**
		 * System oscillator information.
		 */
		GnssMetadata::Oscillator _oscillator;
		
		/**
		 * Specifes multiple RF configurations
		 */
		GnssMetadata::RfConfiguration _rfconfig;
		
		
		
	};

	typedef std::list<System> SystemList;
	
}


#endif
