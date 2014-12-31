/**
 * File: Translator.h
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

#ifndef XMLDEFS_H_H
#define XMLDEFS_H_H
#include<list>

#define METADATA_NAMESPACE "http://www.ion.org/XMLSchema/GnssMetadata.xsd"

namespace GnssMetadata
{
	class Context;

	enum TranslatorId
	{
	
		TE_FREQUENCY,
		TE_DURATION,
		TE_STREAM,
		TE_CHANNEL,
		TE_DATAFILE,
		TE_SYSTEM,
		TE_SESSION,
		TE_RFCONFIG,
		TE_OSCILLATOR,
		TE_METADATA,
		TE_END,
		TE_SIMPLE_TYPE

	};

	/**
	 * NodeEntry is a single entry in a Node list array.
	 */
	struct NodeEntry
	{ 
		const char* pszNodeName; 
		TranslatorId idTranslator;
	};

	/**
	* Nodelists are defined to specify allowed child nodes within current node.
	* Macros are used to specify nodelists on heap.
	*/
	#define NODELIST_BEGIN(name) static const GnssMetadata::NodeEntry  name[] = { 
	#define NODELIST_ENTRY( nodename, idTranslator) { nodename, idTranslator },
	#define NODELIST_END {"",TE_END} }; 

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

	template< typename Tobj>
	struct ListAdaptor : public AccessorAdaptorBase
	{
		typedef std::list< typename Tobj> List;
		ListAdaptor( List& list) : _list( list){}

		virtual void set( void* pval)
		{
			_list.push_back( *static_cast<Tobj*>(pval));
		}
	private:
		List& _list;
	};

}
#endif
