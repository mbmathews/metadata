/**
 * File: RfConfiguration.h
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

#ifndef RFCONFIGURATION_H_H
#define RFCONFIGURATION_H_H

#include "AttributedObject.h"
namespace GnssMetadata
{
	class RfConfiguration:  public AttributedObject
	{
	public:
		RfConfiguration( const String& id) : AttributedObject( id){}
		RfConfiguration() {}
		RfConfiguration(const RfConfiguration& rhs) 
			: AttributedObject( rhs)
		{}
		const RfConfiguration& operator=( const RfConfiguration& rhs)
		{
			if( &rhs == this)
				return *this;
			AttributedObject::operator =(rhs);
			return *this;
		}
	};
	
}


#endif
