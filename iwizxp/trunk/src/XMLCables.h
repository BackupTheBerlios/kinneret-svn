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

#ifndef __XML_CABLES_CONNECTION_METHOD_H__
#define __XML_CABLES_CONNECTION_METHOD_H__

#include "ConnectionMethod.h"
#include "XMLReadable.h"

#include "Log.h"

/** 
 * This <code>ConnectedMethod</code> represents a connection using a cables
 * modem.
 *
 * TODO: Refactor-rename CablesPPtP ?
 *
 * @author duvduv
 */
class XMLCables : public ConnectionMethod, public XMLReadable {
public:

    /* --- Constructors --- */

    /**
     * Default constructor.
     */
    XMLCables() {
        // Nothing to do
    }

    /** 
     * Constructor.
     *
     * @param defaultGateway The default gateway of the ISP.
     * @param dialingDestination The place where the PPtP should dial to
     *        (non-DHCP cables connection are usually PPtP).
     */
    XMLCables(std::string defaultGateway,
           std::string dialingDestination) {
        this->defaultGateway = defaultGateway;
        this->dialingDestination = dialingDestination;

        Log::debug("Cables created successfully");
    }

    /** 
     * Destructor, does nothing.
     */
    virtual ~XMLCables() {
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
     * De-serializes an object from XML.
     * 
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    void fromXML(xercesc::DOMElement *root);

private:

    /* --- Private Methods --- */

    /**
     * Extracts the gateway from the XML representation of this object and
     * sets it as the current gateway.
     *
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    void extractGatewayFromXML(xercesc::DOMElement *root);

    /**
     * Extracts the dialing destination of the given XML, and sets it as the
     * current dialing destination.
     * 
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    void extractDialingDestinationFromXML(xercesc::DOMElement *root);

    /* --- Data Members --- */

    /** The default gateway */
    std::string defaultGateway;

    /** The dialing destination */
    std::string dialingDestination;
};

#endif
