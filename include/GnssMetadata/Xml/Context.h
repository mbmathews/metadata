/**
 * File: Context.h
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

#ifndef CONTEXT_H_H
#define CONTEXT_H_H

#include <tinyxml2.h>


namespace GnssMetadata
{
	class AttributedObject;
	class XmlProcessor;

	/**
	 * Structure implements common base class for all accessor
	 * adaptors.
	 */
	struct AccessorAdaptorBase
	{	
		virtual void set( void* pval) =0;
		//virtual const void* get() const = 0;
	};

	/**
	* Templatized adaptor converts member accesor
	* to mutable object.
	*/
	template<typename Tobj, typename Tmember>
	struct AccessorAdaptor : public AccessorAdaptorBase
	{
		typedef void (Tobj::*fncset)( const Tmember& val);
		AccessorAdaptor(Tobj* pObj, fncset f) : _pobj(pObj), _func(f)
		{}
		virtual void set( void* pval) 
		{
			const Tmember& rval = *static_cast< const Tmember*>(pval);
			(_pobj->*_func)(rval);
		}
	private:
		fncset _func;
		Tobj* _pobj; 
	};


	/**
	 * Class defines the current collection context 
	 */
	class Context
	{
	public:
		Context( XmlProcessor& _proc, AttributedObject* _pContainer)
			: proc( _proc), pContainer( _pContainer)
		{
		}

		XmlProcessor& proc;
		AttributedObject* pContainer;
	};
}

#endif
