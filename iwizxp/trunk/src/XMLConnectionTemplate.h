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

#ifndef __XML_CONNECTION_TEMPLATE_H__
#define __XML_CONNECTION_TEMPLATE_H__

#include "ConnectionTemplate.h"
#include "NamedXMLReadable.h"

/**
 * TODO: JavaDocs
 *
 * @author Itay 'z9u2k' Duvdevani
 */
class XMLConnectionTemplate : public NamedXMLReadable,
                              public ConnectionTemplate {
public:

    /* --- Constructors ---- */

    /**
     * Destructor.
     * TODO: JavaDocs
     */
    virtual ~XMLConnectionTemplate() {
        // Nothing to do
    }

    /* --- Inherited from XMLReadable --- */

    /**
     * De-serializes from XML. Loads all the names for all the kernel
     * classes.
     *
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    void fromXML(xercesc::DOMElement *root);

    /* --- Inherited from Printable --- */

    /**
     * TODO: JavaDocs
     */
    virtual const std::string toString() const {
        return getName() + " - " + getDescription();
    }

private:

    /* --- Data Members --- */
};

#endif
