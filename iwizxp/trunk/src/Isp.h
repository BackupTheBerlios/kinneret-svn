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

#ifndef __ISP_H__
#define __ISP_H__

#include <vector>

#include "Printable.h"
#include "ConnectionMethod.h"
#include "IpAddress.h"

/** 
 * This class represents an ISP.
 *
 * @author duvduv
 */
class Isp : public Printable {
public:

    /* --- Constructors --- */

    /** 
     * Constructor.
     *
     * @param name ISP's name.
     */
    Isp(std::string name) : Printable() {
        this->name = name;
    }
    
    /** 
     * Destructor.
     */
    virtual ~Isp();

    /* --- Public Methods --- */

    /** 
     * Adds a DNS server to the list of the ISP's DNS servers.
     *
     * @param dnsServer IP address of the server.
     */
    void addDnsServer(IpAddress dnsServer) {
        dnsServers.push_back(dnsServer);
    }

    /**
     * Adds a connection method that's supported by this ISP.
     *
     * @param method Pointer to a supported method.
     */
    void addConnectionMethod(ConnectionMethod *method) {
        methods.push_back(method);
    }
    
    /** 
     * @return Vector of DNS servers.
     */
    const std::vector<IpAddress> getDnsServers() const {
        return dnsServers;
    }

    /** 
     * @return Vector of supported connection methods.
     */
    std::vector<ConnectionMethod*> getConnectionMethods() const {
        return methods;
    }

    /**
     * @return ISP's name.
     */
    const std::string getName() const {
        return name;
    }

    /* --- Inherited from Printable --- */

    /** 
     * @return ISP's name.
     */
    virtual const std::string toString() const {
        return getName();
    }

private:

    /* --- Data Members --- */

    /** Name */
    std::string name;

    /** List of DNS servers */
    std::vector<IpAddress> dnsServers;
    
    /** List of supported connection methods */
    std::vector<ConnectionMethod*> methods;
};

#endif
