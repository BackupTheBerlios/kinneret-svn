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

#ifndef __CONNECTION_METHOD_H__
#define __CONNECTION_METHOD_H__

#include "Printable.h"

/** 
 * This interface represents a certain method an ISP offers for connection.
 *
 * @author duvduv
 */
class ConnectionMethod : public Printable {
public:

    /* --- Constructors --- */

    /** 
     * Constructor.
     */
    ConnectionMethod() : Printable() {
        // Nothing to do
    }

    /** 
     * Destructor. 
     */
    virtual ~ConnectionMethod() {
        // Nothing to do
    }

    /* --- Abstract Methods --- */

    /** 
     * Does this connected method requires that we'll set a default gateway?
     *
     * @return <code>true</code>, if we should, <code>false</code> otherwise.
     */
    virtual bool hasDefaultGateway() const = 0;
    
    /** 
     * @return The default gateway. An IP address, or a resolvable URI.
     */
    virtual std::string getDefaultGateway() const = 0;

    /** 
     * @return The dialing destination. Whether a phone number, or a PPtP
     *         host etc.
     */
    virtual std::string getDialingDestination() const = 0;
};


#endif
