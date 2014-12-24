/**
 * File: Session.h
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

#ifndef SESSION_H_H
#define SESSION_H_H

#include "Location.h"
#include "AttributedObject.h"
#include "BaseTypes.h"
#include <list>
namespace GnssMetadata
{
	class Session : public AttributedObject
	{
		
	public:
		Session( const String& id) : AttributedObject( id){}
		Session() {}
		Session(const Session& rhs) 
			: AttributedObject( rhs),
			_campaign(rhs._campaign), _contact(rhs._contact),
			_location(rhs._location), _poc(rhs._poc),
			_scenario(rhs._scenario)
		{}	

		String Campaign( ) const
		{
			return _campaign;
		}
		void Campaign( const String campaign )
		{
			_campaign = campaign;
		}
		String Contact( ) const
		{
			return _contact;
		}
		void Contact( const String contact )
		{
			_contact = contact;
		}


		const GnssMetadata::Location& Location( ) const
		{
			return _location;
		}
		GnssMetadata::Location& Location( ) 
		{
			return _location;
		}
		void Location( const GnssMetadata::Location& location )
		{
			_location = location;
		}

		String Poc( ) const
		{
			return _poc;
		}
		void Poc( const String poc )
		{
			_poc = poc;
		}
		
		void Scenario( const String scenario )
		{
			_scenario = scenario;
		}
		String Scenario( ) const
		{
			return _scenario;
		}
		
		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
		
	private:
		String _campaign;
		
		String _contact;
		
		String _id;
		
		GnssMetadata::Location _location;
		
		String _poc;
		
		String _scenario;
		
		
	};

	typedef std::list<Session> SessionList;
}


#endif
