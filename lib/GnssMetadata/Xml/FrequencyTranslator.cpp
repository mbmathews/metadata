/**
 * File: FrequencyTranslator.cpp
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


#include "FrequencyTranslator.h"
#include <GnssMetadata/Frequency.h>
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

static const char* _szfmts[] = {"Hz","MHz", "GHz", "Ratio"};
Frequency::FrequencyFormat ToFormat( const char* pszFmt)
{
	for( int i = 0; i < sizeof( _szfmts); i++)
	{
		if( strcmp( _szfmts[i], pszFmt) == 0)
			return (Frequency::FrequencyFormat)i;
	}
	return (Frequency::FrequencyFormat)0;
}


FrequencyTranslator::FrequencyTranslator() 
: Translator( NULL)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool FrequencyTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	//The node as been tested as a Frequency Translator
	if( pAdaptor != NULL)
	{
		pcstr format = elem.Attribute("format","Hz");
		Frequency::FrequencyFormat fmt = ToFormat( format);
		Frequency freq;
		switch( fmt)
		{
		case Frequency::Ratio:
			{
				long num, denom;
				sscanf( elem.GetText(), "%ld,%ld", &num, &denom);
				freq.Value( num, denom);
			}
			break;
		default:
			{
				freq.Value( atof(elem.GetText()), fmt);
			}
			break;
		}

		//Set the accessor.
		pAdaptor->set( &freq);
		return true;
	}

	return false;
}
/**
 * Write the current object 
 */
void FrequencyTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, XMLElement & elem )
{
	const Frequency* pfreq = dynamic_cast< const Frequency*>(pObject);
	if( pfreq == NULL) 
		throw TranslationException("FrequencyTranslator cannot cast frequency object");

	XMLElement* pelemf = elem.GetDocument()->NewElement( pszName);
	pelemf->Attribute("format", _szfmts[ pfreq->Format()]);
	char buff[64];
	const Frequency::ValueType& val = pfreq->Value();
	
	switch( pfreq->Format() )
	{
	case Frequency::Ratio:
		{
			sprintf(buff, "%ld,%ld", val.ratioVal.numerator,
				val.ratioVal.denominator);
		}
		break;
	default:
		{
			sprintf(buff, "%0.16le", val.doubleVal);
		}
		break;
	}
	pelemf->SetText( buff);
	elem.InsertEndChild( pelemf);

}
