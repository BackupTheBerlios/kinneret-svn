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

#include "Nameable.h"
#include "ConnectionMethod.h"
#include "IpAddress.h"
#include "Log.h"

/** 
 * This class represents an ISP.
 *
 * A note about the virtual base <code>Nameable</code>:
 * An ISP is a <code>Nameable</code> object. The ISP object is responsible for
 * the ISP-ish behaviour of the object, alone.
 * The idea is that each class will have a single responsibility. That's why,
 * <code>Isp</code> has a son named <code>XMLIsp</code>. <code>XMLIsp</code>
 * is responsible for the serialization and deserialization of the ISP to and
 * from XML, alone.  Since <code>XMLIsp</code> is a son of
 * <code>NamedXMLReadable</code> as well, <code>Nameable</code> must be a
 * virtual base (Look at the hirarchy of <code>NamedXMLReadable</code>).
 * According to this design, if someday other methods of serialization will
 * be required, all we'll have to do is to sub-class <code>Isp</code> and
 * change the <code>IspLoader</code> at the <code>GlobalRepository</code>.
 *
 * @author duvduv
 */
class Isp : public virtual Nameable {
public:

    /* --- Constructors --- */

    /**
     * Constructor. Creates an unnamed ISP.
     * This constructor is presented for the use of classes that does not
     * know the name of the ISP at construction time, but will know it later.
     *
     * @see #setName
     */
    Isp() : Nameable() {
        // Nothing to do
    }

    /** 
     * Constructor. Creates a named ISP.
     *
     * @param name ISP's name.
     */
    Isp(const std::string name) : Nameable(name) {
        // Nothing to do
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
     * @return DNS servers.
     */
    const std::vector<IpAddress> &getDnsServers() const {
        return dnsServers;
    }

    /** 
     * @return Supported connection methods.
     */
    const std::vector<ConnectionMethod*> &getConnectionMethods() const {
        return methods;
    }

private:

    /* --- Data Members --- */

    /** Ordered list of DNS servers */
    std::vector<IpAddress> dnsServers;
    
    /** List of supported connection methods */
    std::vector<ConnectionMethod*> methods;
};

#endif
