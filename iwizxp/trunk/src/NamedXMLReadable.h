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

#ifndef __NAMED_XML_READABLE_H__
#define __NAMED_XML_READABLE_H__

#include "Nameable.h"
#include "XMLReadable.h"

/**
 * This class is a <code>Nameable</code> class, that can load its name from
 * XML. It loads its name from the <code>&lt;name&gt;</code> tag found under the
 * root.
 *
 * A note regarding the virtual base <code>Nameable</code> can be found at
 * the description of the {@link Isp} class.
 *
 * @see Isp
 * 
 * @author duvduv
 */
class NamedXMLReadable : public virtual Nameable, public XMLReadable {
public:

	/* --- Constructors ---- */

	/**
	 * Constructor. Use it when you know the name of the
	 * <code>Nameable</code> at construction time.
	 *
	 * @param name Name.
	 */
	NamedXMLReadable(const std::string name) :
			Nameable(name), XMLReadable() {
		// Nothing to do
	}

	/**
	 * Constructor. Use it when the name is not known at construction time.
	 * In this case, use the <code>setName</code> method the set the name
	 * later. It is advised to do this only once, <code>Nameable</code>
	 * should be an immutable class.
	 *
	 * @see #setName()
	 */
	NamedXMLReadable() : Nameable(), XMLReadable() {
		// Nothing to do
	}

	/**
	 * Destructor. Does nothing interesting.
	 */
	virtual ~NamedXMLReadable() {
		// Nothing to do
	}

	/* --- Inherited from XMLReadable --- */

	/**
	 * Loads the name of the object from the <code>&lt;name&gt;</code> tag
	 * that's in it.
	 *
	 * Note that if the tag is present, but empty, the name of this class
	 * will be empty as well.
	 *
	 * @param root Root node. Must contain a <code>name</code> tag right
	 *        below it in the hirarchy.
	 * @throws XMLSerializationException If the tag isn't found under the
	 *         given root.
	 */
	virtual void fromXML(xercesc::DOMElement *root);
};

#endif
