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

#include "Log.h"

/** 
 * This <code>ConnectedMethod</code> represents a connection using a cables
 * modem.
 *
 * TODO: Refactor-rename CablesPPtP ?
 *
 * @author duvduv
 */
class Cables : public ConnectionMethod {
public:

    /* --- Constructors --- */

    /** 
     * Constructor.
     *
     * @param defaultGateway The default gateway of the ISP.
     * @param dialingDestination The place where the PPtP should dial to
     *        (non-DHCP cables connection are usually PPtP).
     */
    Cables(std::string defaultGateway,
           std::string dialingDestination) : ConnectionMethod() {
        this->defaultGateway = defaultGateway;
        this->dialingDestination = dialingDestination;

        Log::debug("Cables created successfully");
    }

    /**
     * TODO
     */
    Cables(const xercesc::DOMElement *root) throw (XMLSerializationException) :
            ConnectionMethod() {
        fromXML(root);
    }

    /** 
     * Destructor, does nothing.
     */
    virtual ~Cables() {
        Log::debug("Cables released successfully");
    }

    /* --- Inherited from ConnectionMethod --- */

    /** 
     * @return Whether this connection method has a default gateway. It does.
     */
    virtual bool hasDefaultGateway() const {
        return true;
    }
    
    /** 
     * @return The default gateway
     */
    virtual std::string getDefaultGateway() const {
        return defaultGateway;
    }

    /** 
     * @return The dialing destination (an IP or a resolvable URI).
     */
    virtual std::string getDialingDestination() const {
        return dialingDestination;
    }

    /* --- Inherited from Printable --- */

    /** 
     * @return The name of this dialing method.
     */
    virtual const std::string toString() const {
        return "Cables";
    }

    /* --- Inherited from XMLReadable --- */

    /** 
     * TODO
     */
    void fromXML(const xercesc::DOMElement *root)
        throw (XMLSerializationException);

private:

    /* --- Private Methods --- */

    /**
     * TODO
     */
    void extractGatewayFromXML(const xercesc::DOMElement *root)
        throw (XMLSerializationException);

    /**
     * TODO
     */
    void extractDialingDestinationFromXML(const xercesc::DOMElement *root)
        throw (XMLSerializationException);

    /* --- Data Members --- */

    /** The default gateway */
    std::string defaultGateway;

    /** The dialing destination */
    std::string dialingDestination;
};

#endif
