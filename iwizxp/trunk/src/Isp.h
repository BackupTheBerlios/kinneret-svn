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
 * TODO 
 */
class Isp : public Printable {
public:

    /* --- Constructors --- */

    /** 
     * TODO 
     */
    Isp(std::string name) : Printable() {
        this->name = name;
    }
    
    /** 
     * TODO 
     */
    virtual ~Isp();

    /* --- Public Methods --- */

    /** 
     * TODO 
     */
    void addDnsServer(IpAddress dnsServer) {
        dnsServers.push_back(dnsServer);
    }

    /**
     * TODO
     */
    void addConnectionMethod(ConnectionMethod *method) {
        methods.push_back(method);
    }
    
    /** 
     * TODO 
     */
    const std::vector<IpAddress> getDnsServers() const {
        return dnsServers;
    }

    /** 
     * TODO 
     */
    std::vector<ConnectionMethod*> getConnectionMethods() const {
        return methods;
    }

    /**
     * TODO
     */
    const std::string getName() const {
        return name;
    }

    /* --- Inherited from Printable --- */

    /** 
     * TODO 
     */
    virtual const std::string toString() const;

private:

    /* --- Data Members --- */

    /** TODO */
    std::string name;

    /** TODO */
    std::vector<IpAddress> dnsServers;
    
    /** TODO */
    std::vector<ConnectionMethod*> methods;
};


#endif
