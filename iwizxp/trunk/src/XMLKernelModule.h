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

#ifndef __XML_KERNEL_MODULE_H__
#define __XML_KERNEL_MODULE_H__

#include "KernelModule.h"
#include "NamedXMLReadable.h"

/**
 * This class represents a kernel module that can be de-serialized from XML.
 *
 * @author duvduv.
 */
class XMLKernelModule : public KernelModule, public NamedXMLReadable {
public:

    /* --- Constructors ---- */

    /**
     * Destructor.
     *
     * Does nothing.
     */
    virtual ~XMLKernelModule() {
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

private:

    /* --- Helper Methods --- */

    /**
     * Extracts the value of the <code>kernel</code> attribute from the given
     * element, and translate it to <code>KernelClass</code>.
     *
     * Format of the attribute is very simple, and goes like the regular
     * kernel notation (<code>&lt;major&gt;.&lt;minor&gt;</code>, e.g.
     * <code>2.4</code> and <code>2.6</code>).
     *
     * @return Class that corresponds the attribute in the element.
     * @param element Element that has an <code>kernel</code> attribute.
     * @throws XMLSerializationException When the given elements doesn't have
     *         a <code>kernel</code> attribue, or the attribute is not
     *         formatted correctly.
     */
    KernelClass kernelClassFromXML(xercesc::DOMElement *element) const;
};

#endif
