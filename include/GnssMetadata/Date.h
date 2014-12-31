/**
 * File: Date.h
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

#ifndef DATE_H_H
#define DATE_H_H

//Grab os time type.
#if defined(_WIN32) || defined(_WIN64)
	#include <time.h>
	struct timespec 
	{
		time_t tv_sec;
		long tv_nsec;
	};
#else
	#include <time.h>
#endif


#include "BaseTypes.h"
namespace GnssMetadata
{
	/**
	 * Simple Date and Time class with GPS time conversion support.
	 */
	class Date: public Object
	{
	public:
		static Date Now();
		Date();
		Date( const Date& rhs);
		Date( const timespec& tspec);
		Date(int year, int mon, int day, int hour, int min, double sec);
		Date(time_t time, double fracsec = 0.0);
		Date( double secGps, int wkGps, int secLeap = 0);
		Date( const char* pszDate);

		const Date& operator=( const Date& rhs);

		void TmPtr(struct tm* ptm) const { gmtime_s( ptm, &_dt.tv_sec);}
		int Year() const 		{ struct tm _tm; gmtime_s(&_tm, &_dt.tv_sec); return _tm.tm_year + 1900;}
		int Month() const 		{ struct tm _tm; gmtime_s(&_tm, &_dt.tv_sec); return _tm.tm_mon + 1; }
		int Day() const			{ struct tm _tm; gmtime_s(&_tm, &_dt.tv_sec); return _tm.tm_mday; }
		int DayOfYear() const	{ struct tm _tm; gmtime_s(&_tm, &_dt.tv_sec); return _tm.tm_yday; }
		int DayOfWeek() const	{ struct tm _tm; gmtime_s(&_tm, &_dt.tv_sec); return _tm.tm_wday; }
		int Hour() const		{ struct tm _tm; gmtime_s(&_tm, &_dt.tv_sec); return _tm.tm_hour; }
		int Minute() const		{ struct tm _tm; gmtime_s(&_tm, &_dt.tv_sec); return _tm.tm_min;  }
		double Second() const	{ struct tm _tm; gmtime_s(&_tm, &_dt.tv_sec); return _tm.tm_sec;  }

		/**
		 * Seconds since GPS 0
		 */
		timespec SinceGps0() const; 

		/**
		 * Returns the GPS week and seconds 
		 */
		void ToGpsWeekSec( int *pwkGps, double *psecGps) const;		

		/**
		 * Returns the GPS Week.  Note use ToGpsWeekSec for most efficient access.
		 */
		int  GpsWeek()   const { int wk; double sec; ToGpsWeekSec(&wk, &sec); return wk;}
		
		/**
		 * Returns the GPS Sec.  Note use ToGpsWeekSec for most efficient access.
		 */
		double GpsSec() const { int wk; double sec; ToGpsWeekSec(&wk, &sec); return sec;}

		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );


	private:
		timespec _dt;
		int _secLeap;
	};
	
}


#endif
