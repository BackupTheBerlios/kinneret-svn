/***************************************************************************
 *   Copyright (C) 2005 by Itay 'z9u2K' Duvdevani                          *
 *   itay AT z9u2kHomelinuxCom                                             *
 *   (replace uppercase letters with '.' and lowercase letter)             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __XML_MODEM_LOADER_H__
#define __XML_MODEM_LOADER_H__

#include "ModemLoader.h"

/**
 * Loads a modem from XML.
 *
 * @author duvduv
 */
class XMLModemLoader : public ModemLoader {
public:

	/* --- Constructors ---- */

	/**
	 * Constructor.
	 *
	 * Does nothing.
	 */
	XMLModemLoader() {
		Log::debug(LOG_LOCATION("XMLModemLoader", "XMLModemLoader"),\
			"Constructing XMLModemLoader");
	}

	/**
	 * Destructor.
	 *
	 * Does nothing.
	 */
	virtual ~XMLModemLoader() {
		Log::debug(LOG_LOCATION("XMLModemLoader", "~XMLModemLoader"),
			"Destroying XMLModemLoader");
	}

	/* --- Public Methods --- */

	/**
	 * This method parses the stream as if it was XML, and de-serializes a
	 * modem from the parsed DOM tree.
	 *
	 * @param inStream The stream to parse.
	 * @return A new and initialized <code>Modem</code>.
	 * @throws LoadException Thrown when the stream could not be parsed, or
	 *         an <code>XMLSerializationException</code> was thrown from
	 *         <code>Modem</code>'s <code>fromXML</code>.
	 */
	virtual Modem *loadModem(std::istream &inStream) const;
};

#endif
