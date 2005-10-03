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
#include "Log.h"

/** 
 * This interface represents a certain connection method an ISP offers for
 * the subscribers.
 *
 * The connection method is the method you use to connect to your ISPs
 * servers, thus gaining access to the entire internet.
 *
 * A typical connection method might be dial-in, ADSL or cables.
 *
 * The connection method class holds information regrading the method itself
 * (such as server addresses, phone numbers etc.). It does not hold modem
 * specific information (such as ethernet address).
 *
 * TODO: Rethink about this interface, something is wrong here... see
 * getDialingDestination.
 *
 * @author duvduv
 */
class ConnectionMethod : public Printable {
public:

    /* --- Constructors --- */

    /**
     * Constructor. Does nothing but printing a pretty log message.
     */
    ConnectionMethod() {
        Log::debug("Constructing ConnectionMethod");
    }

    /** 
     * Destructor. Does nothing but printing a pretty log message.
     */
    virtual ~ConnectionMethod() {
        Log::debug("Destroying ConnectionMethod");
    }

    /* --- Abstract Methods --- */

    /** 
     * Does this connected method requires that we'll set a default gateway?
     *
     * The default gateway is the address we should use as the routing
     * destination for the new connection. If this method says we should, it
     * means the default gateway is obtained during the process of
     * connection, and that it is dynamic.
     *
     * @return <code>true</code>, if we should, <code>false</code> otherwise.
     */
    virtual bool hasDefaultGateway() const = 0;
    
    /** 
     * The default gateway is the host we should route through when
     * interacting with the internet.
     *
     * @return The default gateway. An IP address, or a resolvable URI.
     */
    virtual std::string getDefaultGateway() const = 0;

    /**
     * The dialing destination holds information regarding where to "call"
     * in order to establish a connectin. It might be a phone number we're
     * calling to, or an IP address of the ISP's PPtP server.
     *
     * TODO: This is why something is wrong. the dialing destination might
     * come from the ISP, of from the modem (like the alcatel speed touch
     * home). Mybe add hasDialingDestination() ?
     * 
     * @return The dialing destination. Whether a phone number, or a PPtP
     *         host etc.
     */
    virtual std::string getDialingDestination() const = 0;
};

#endif
