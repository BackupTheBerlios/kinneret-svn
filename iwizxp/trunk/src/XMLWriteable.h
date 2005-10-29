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

#ifndef __XML_WRITEABLE_H__
#define __XML_WRITEABLE_H__

#include <xercesc/dom/DOMElement.hpp>

/**
 * This interface provides the ability to serialize an instance of a derived
 * class to DOM tree that can be written as XML. It does that through the
 * <code>toXML</code> method, which adds to the given DOM tree a sub-tree,
 * under a certain, given, element, a DOM tree that can be used later to
 * de-serialize this class using <code>XMLReadable</code>.
 *
 * @author duvduv
 */
class XMLWriteable {
public:

	/* --- Constructors ---- */

	/**
	 * Destructor.
	 */
	virtual ~XMLWriteable() {
		// Nothing to do
	}

	/* --- Public Methods --- */

	/**
	 * Serializes this object to XML. The root element will be placed under
	 * <code>root</code>.
	 *
	 * @param root The root element that will be the father of the root
	 *        element of this class' serialization.
	 */
	virtual void toXML(xercesc::DOMElement *root) const = 0;
};

#endif
