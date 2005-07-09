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

#ifndef __XML_READABLE_H__
#define __XML_READABLE_H__

#include <xercesc/dom/DOMElement.hpp>

#include "Exception.h"

/**
 * This interface provide a class the ability to be de-serialized from XML. It
 * does that through the <code>fromXML</code> method, that receives a DOM
 * tree element, and using the tree under it, constructs and initializes an
 * object.
 *
 * @author duvduv
 */
class XMLReadable {
public:

    /* --- Exceptions --- */

    /**
     * Serialization exception occures when the given DOM tree cannot be used
     * as a tree for the creation of this object.
     */
    NewException(XMLSerializationException);

    /* --- Constructors ---- */

    /**
     * Destructor.
     */
    virtual ~XMLReadable() {
        // Nothing to do
    }

    /* --- Public Methods --- */

    /**
     * Initializes the object from a DOM tree.
     *
     * @param root Element inside a docuement that is the root of a tree that
     *        can be used to build this object.
     * @throws XMLSerializationException Thrown when the given root element
     *        cannot be used to initialize this object.
     */
    virtual void fromXML(xercesc::DOMElement *root) = 0;
};

#endif
