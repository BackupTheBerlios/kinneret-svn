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

#ifndef __PRINTABLE_H__
#define __PRINTABLE_H__

#include <string>

/**
 * Think of this class as Java's <code>Object.toString()</code> - All
 * implementing classes should be able to presents themselvs as a printable
 * string.
 *
 * This abstract class supplies an implicit conversion to
 * <code>std::string</code> using <code>toString()</code>.
 *
 * @author duvduv
 */
class Printable {
public:

    /* --- Construcotrs --- */
    
    /**
     * Default constructor. Does nothing interesting.
     */
    Printable() {
        // Nothing to do
    }

    /** 
     * Destructor. Does nothing interesting.
     */
    virtual ~Printable() {
        // Nothing to do
    }

    /* --- Abstract Methods --- */
    
    /** 
     * Abstract method that formates the implementing object to a printable
     * string.
     *
     * @return Printable string.
     */
    virtual const std::string toString() const = 0;

    /* --- Public Methods --- */

    /** 
     * Implicit conversion.
     *
     * @return <code>toString()</code>.
     */
    inline operator std::string() const {
        return toString();
    }
};

#endif
