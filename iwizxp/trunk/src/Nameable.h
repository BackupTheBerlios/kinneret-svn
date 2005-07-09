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
 * TODO: JavaDocs
 *
 * @author duvduv
 */
class Nameable : public Printable {
public:

    /* --- Constructors ---- */

    /**
     * Constructor.
     * TODO: JavaDocs
     */
    Nameable(const std::string name) : Printable () {
        this->name = name;
    }

    /**
     * Destructor.
     * TODO: JavaDocs
     */
    virtual ~Nameable() {
        // Nothing to do
    }

    /* --- Public Methods --- */

    /**
     * TODO: JavaDocs
     */
    virtual std::string getName() const {
        return name;
    }

    /* --- Inherited from Printable --- */

    /**
     * TODO: JavaDocs
     */
    virtual const std::string toString() const {
        return getName();
    }

protected:

    /* --- Protected Methods --- */

    /**
     * TODO: JavaDocs
     */
    void setName(std::string name) {
        this->name = name;
    }

private:

    /* --- Data Members --- */

    /** TODO: JavaDocs */
    std::string name;
};

#endif
