/**
 * File: BaseTypes.h
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

#ifndef BASETYPES_H_H
#define BASETYPES_H_H

#include <string>
#include <stdexcept>


namespace GnssMetadata
{
	/**
	* Standard string type used throughout the API.
	*/
	typedef std::string String;

	/**
	 * Base class of all GnssMetadata objects and primitives.
	 */
	class Object
	{
	public:
		static const String DefaultFormat;
		
	public:
		/**
		 * Returns a string representation of the object.
		 */
		virtual String toString( const String& sFormat =  DefaultFormat ) = 0;
	};
	

	/**
	 * Standard API exception
	 */
	class ApiException : public std::exception
	{
	public:
		enum ErrorType
		{
			Unspecified,
			ArgumentError,
			OutOfRange,
			TranslationError,
			NotImplemented
		};
	public:
		ApiException( const char *const& _What, ErrorType errType = Unspecified )
			: std::exception( _What), _error(errType)
		{
		}

		ApiException( const exception& _That) : std::exception( _That),
			_error( Unspecified)
		{
		}
		ErrorType Error() const { return _error;}
	private:
		ErrorType _error;
	};

	/**
	 * Exception thrown whenever an invalid argument encountered.
	 */
	class ArgumentException : public ApiException
	{
	public:
		ArgumentException( const char *const& _What = "Argument Error",
			ErrorType errType = ArgumentError)
			: ApiException( _What)
		{
		}
	};

	/**
	 * Exception thrown whenever an argument is out of range.
	 */
	class OutOfRangeException : public ArgumentException
	{
	public:
		OutOfRangeException( const char *const& _What = "Argument out of range")
			: ArgumentException( _What, OutOfRange)
		{
		}
	};


	/**
	 * Exception thrown whenever a file parsing error occurs.
	 */
	class TranslationException : public ApiException
	{
	public:
		TranslationException( const char *const& _What = "Translation Error", int  iderror = 0)
			: ApiException( _What, TranslationError), XmlError( iderror)
		{
		
		}
		size_t XmlError;
	};

	/**
	 * Exception thrown whenever not implemented code is encountered.
	 */
	class NotImplementedException : public ApiException
	{
	public:
		NotImplementedException( const char *const& _What = "Not Implemented")
			: ApiException( _What, NotImplemented)
		{
		}
	};

	/**
	* Template validates the range of a value. Throwns OutOfRangeException if invalid.
	*/
	template< class ctype> void ValidateRange( const ctype& val, const ctype& min, 
		const ctype& max, const char* const& paramName)
	{
		if( val < min || val > max ) throw GnssMetadata::OutOfRangeException( paramName);
	}


}


#endif
