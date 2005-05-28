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

#ifndef __CABLES_CONNECTION_METHOD_H__
#define __CABLES_CONNECTION_METHOD_H__

#include "ConnectionMethod.h"

/** 
 * TODO 
 */
class Cables : public ConnectionMethod {
public:

    /* --- Constructors --- */

    /** 
     * TODO 
     */
    Cables(std::string defaultGateway,
           std::string dialingDestination) : ConnectionMethod() {
        this->defaultGateway = defaultGateway;
        this->dialingDestination = dialingDestination;
    }

    /** 
     * TODO 
     */
    virtual ~Cables() {
    }

    /* --- Inherited from ConnectionMethod --- */

    /** 
     * TODO 
     */
    virtual bool hasDefaultGateway() const {
        return true;
    }
    
    /** 
     * TODO 
     */
    virtual std::string getDefaultGateway() const {
        return defaultGateway;
    }

    /** 
     * TODO 
     */
    virtual std::string getDialingDestination() const {
        return dialingDestination;
    }

    /* --- Inherited from Printable --- */

    /** 
     * TODO 
     */
    virtual const std::string toString() const {
        return "Cables";
    }

private:

    /* --- Data Members --- */

    /** TODO */
    std::string defaultGateway;

    /** TODO */
    std::string dialingDestination;
};

#endif
