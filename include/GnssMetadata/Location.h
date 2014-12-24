/**
 * File: Location.h
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

#ifndef LOCATION_H_H
#define LOCATION_H_H

#include "BaseTypes.h"

namespace GnssMetadata
{
	/**
	 * Class represents the Latitude, Longitude, and height for a location.
	 */
	class Location: public Object
	{
		
	public:
		Location( double lat, double lon, double height) 
			: _latitude(lat), _longitude(lon), _height( height)
		{}
	
		Location() 
			: _latitude(0.0), _longitude(0.0), _height( 0.0)
		{}

		Location(const Location& rhs) 
			: _latitude(rhs._latitude), _longitude(rhs._longitude), _height( rhs._height)
		{}

		/**
		 * Sets the latitude in meters.
		 */
		void Latitude( const double latitude )
		{
			ValidateRange<double>( latitude, -90, 90,"Latitude");
			_latitude = latitude;
		}

		/**
		 * Gets the latitude in meters.
		 */
		double Latitude( ) const
		{
			return _latitude;
		}

		/**
		 * Sets the longitude in meters.
		 */
		void Longitude( const double longitude )
		{
			ValidateRange<double>( longitude, -360, 360,"Longitude");
			_longitude = longitude;
		}

		/**
		 * Gets the longitude in meters.
		 */
		double Longitude( ) const
		{
			return _longitude;
		}

		/**
		 * Sets the height in meters.  Typically above the geoid.
		 */
		void Height( const double height )
		{
			ValidateRange<double>( height, -5000, 50e6,"Latitude");
			_height = height;
		}

		/**
		 * Gets the height in meters.
		 */
		double Height( ) const
		{
			return _height;
		}


		/**
		 * Returns a string representation of the object.
		 */
		virtual String toString( const String& sFormat =  DefaultFormat );
		
	private:
		/**
		 * Height in meters
		 */
		double _height;
		
		/**
		 * Latitude in degrees.
		 */
		double _latitude;
		
		/**
		 * Longitude in degrees.
		 */
		double _longitude;
		
		
	};
	
}


#endif
