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

#ifndef __NAMEABLE_H__
#define __NAMEABLE_H__

#include "Printable.h"

/**
 * This class is nameable, meaning, it has a name. For non-derived classes, this
 * class is immutable, the name is set once and never changes. Derived
 * classes can set the name, but it is advised to do it only once, during
 * construction, or near it.
 *
 * TODO: This might be desiged a bit smarter. The <code>setName</code> method
 * exists for the benefit of <code>NamedXMLReadable</code>, that doesn't know
 * the name of the object at construction time, but must change it in
 * <code>fromXML</code>. Problem is, derived classes can change their name
 * whenevery they want - which is not what we intended (<code>Nameable</code>
 * shoule be immutable).
 *
 * @author duvduv
 */
class Nameable : public Printable {
public:

	/* --- Constructors ---- */

	/**
	 * Default contrcutor. Used by someone who wishes to set the name after
	 * construction.
	 */
	Nameable() : Printable() {
		// Empty constructor
	}

	/**
	 * Constructor. Does nothinf interesting.
	 * 
	 * @param name The name of this <code>Nameable</code>.
	 */
	Nameable(const std::string name) : Printable () {
		this->name = name;
	}

	/**
	 * Destructor. Does nothing interesting.
	 */
	virtual ~Nameable() {
		// Nothing to do
	}

	/* --- Public Methods --- */

	/**
	 * @return Name of this <code>Nameable</code>.
	 */
	virtual std::string getName() const {
		return name;
	}

	/* --- Inherited from Printable --- */

	/**
	 * @return Name of this <code>Nameble</code>.
	 */
	virtual const std::string toString() const {
		return getName();
	}

protected:

	/* --- Protected Methods --- */

	/**
	 * @param name New name.
	 */
	void setName(std::string name) {
		this->name = name;
	}

private:

	/* --- Data Members --- */

	/** Our Name */
	std::string name;
};

#endif
