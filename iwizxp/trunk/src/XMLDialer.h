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

#ifndef __XML_DIALER_H__
#define __XML_DIALER_H__

#include "Dialer.h"
#include "NamedXMLReadable.h"

/**
 * TODO: JavaDocs
 */
class XMLDialer : public Dialer, public NamedXMLReadable {
public:

	/* --- Constructors ---- */

	/**
	 * Constructor.
	 * TODO: JavaDocs
	 */
	XMLDialer() : Dialer(), NamedXMLReadable() {
		// Nothing to do
	}

	/**
	 * Destructor.
	 * TODO: JavaDocs
	 */
	virtual ~XMLDialer() {
		// Nothing to do
	}

	/* --- Inherited from XMLReadable --- */

	/**
	 * TODO: JavaDocs
	 *
	 * @param root Root node of the object
	 * @throws XMLSerializationException When the given XML is of incorrect
	 *         fromat.
	 */
	virtual void fromXML(xercesc::DOMElement *root);

private:

	/* --- Utility Methods --- */

	/**
	 * TODO: JavaDocs
	 */
	void extractConnectionScriptsFromXML(xercesc::DOMElement *root);

	/**
	 * TODO: JavaDocs
	 */
	void extractDisconnectionScriptsFromXML(xercesc::DOMElement *root);

	/**
	 * TODO: JavaDocs
	 */
	static Script *loadScripByName(std::string scriptName);
};

#endif
