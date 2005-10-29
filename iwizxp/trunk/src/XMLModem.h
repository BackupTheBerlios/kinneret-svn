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

#ifndef __XML_MODEM_H__
#define __XML_MODEM_H__

#include "Modem.h"
#include "NamedXMLReadable.h"

/**
 * This class represents a modem that can be de-serialized from XML.
 * 
 * @author duvudv
 */
class XMLModem : public Modem, public NamedXMLReadable {
public:

	/* --- Constructors ---- */

	/**
	 * Constructor.
	 *
	 * Does nothing.
	 */
	XMLModem() : Modem(), NamedXMLReadable() {
		// Nothing to do
	}

	/**
	 * Destructor.
	 *
	 * Does nothing.
	 */
	virtual ~XMLModem() {
		// Nothing to do
	}

	/* --- Inherited from XMLReadable --- */

	/**
	 * De-serializes from XML. Loads all the dialers and modules.
	 *
	 * @param root Root node of the object
	 * @throws XMLSerializationException When the given XML is of incorrect
	 *         fromat.
	 */
	void fromXML(xercesc::DOMElement *root);

private:

	/* --- Utility Methods --- */

	/**
	 * Loads the list of the required modules for the modem. Created a
	 * <code>KernelModule</code> for every entry, and de-serializes from XML
	 * using the item node as the root node of the module.
	 *
	 * @param root Root node of the object
	 * @throws XMLSerializationException When the given XML is of incorrect
	 *         fromat or deserialization of the module failed.
	 */
	void loadModulesFromXML(xercesc::DOMElement *root);

	/**
	 * Loads the default dialer, and the exceptions, from XML.
	 *
	 * @param root Root node of the object
	 * @throws XMLSerializationException When the given XML is of incorrect
	 *         fromat.
	 */
	void loadDialersFromXML(xercesc::DOMElement *root);

	/**
	 * Extracts the name of the default dialer from the tag, loads the
	 * dialer and sets it as the default dialer for this modem.
	 *
	 * @param dialerNode node of the dialer we wish to load.
	 * @throws XMLSerializationException When the given XML is of incorrect
	 *         fromat.
	 */
	void loadDefaultDialer(xercesc::DOMElement *dialerNode);

	/**
	 * Fills the exceptions map. Sorts the list, loads the dialers and puts
	 * them in the map.
	 *
	 * @param dialerNode Root node of the object
	 * @throws XMLSerializationException When the given XML is of incorrect
	 *         fromat.
	 */
	void loadExceptions(xercesc::DOMElement *dialerNode);
};

#endif
