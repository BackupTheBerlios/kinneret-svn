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

#include <xercesc/dom/DOMElement.hpp>

#include "NamedXMLReadable.h"
#include "ConnectionMethod.h"
#include "IpAddress.h"
#include "Log.h"

/** 
 * This class represents an ISP.
 *
 * @author duvduv
 */
class Isp : public NamedXMLReadable {
public:

    /* --- Constructors --- */

    /** 
     * Constructor.
     *
     * @param name ISP's name.
     */
    Isp(const std::string name) : NamedXMLReadable(name) {
        this->name = name;
    }

    /**
     * Constructor. De-serializes from XML.
     *
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    Isp(xercesc::DOMElement *root) : NamedXMLReadable() {
        fromXML(root);
        Log::debug(std::string("Isp: ") + name + " created successfully");
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
    const std::vector<IpAddress> &getDnsServers() const {
        return dnsServers;
    }

    /** 
     * @return Vector of supported connection methods.
     */
    const std::vector<ConnectionMethod*> &getConnectionMethods() const {
        return methods;
    }

    /* --- Inherited from XMLReadable --- */
    
    /**
     * Initializes variables according to the given element.
     *
     * We make this method not-virtual so we could call it from the
     * constructor.
     *
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    void fromXML(xercesc::DOMElement *root);

private:

    /* --- Utilitiy --- */

    /**
     * Sorts the list of DNS servers from the XML, and sets the current list
     * to be it.
     * 
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    void extractDnsServersFromXML(xercesc::DOMElement *root);

    /**
     * Sorts the list of <code>ConnectionMethod</code>s from the XML, creates
     * the method and de-serializes them from XML, giving them the item
     * element as the root element.
     * 
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat, or one of the connection methods failed to
     *         de-serialize.
     */
    void extractConnectionMethodsFromXML(xercesc::DOMElement *root);

    /* --- Data Members --- */

    /** Name */
    std::string name;

    /** List of DNS servers */
    std::vector<IpAddress> dnsServers;
    
    /** List of supported connection methods */
    std::vector<ConnectionMethod*> methods;
};

#endif
