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

#include "XMLIsp.h"

#include "Utils.h"
#include "xts.h"
#include "Cables.h"

using namespace std;
using namespace xercesc;
using namespace Utils;
using namespace Utils::DOM;

void XMLIsp::fromXML(DOMElement *root) {
    NamedXMLReadable::fromXML(root);
    extractDnsServersFromXML(root);
    extractConnectionMethodsFromXML(root);
}

void XMLIsp::extractDnsServersFromXML(xercesc::DOMElement *root) {
    DOMElement *dnsServerNode = getLoneElementByTagName(root, "dns");

    if (dnsServerNode == 0) {
        throw XMLSerializationException("No <dns> tag found!");
    }

    // Get a sorted list of servers
    vector<DOMElement*> items;
    elementsArrayFromXML(items, dnsServerNode, "server");

    // And add them
    for (int i = 0 ; i < items.size() ; i++) {
        if (items[i] != 0) {
            Log::debug("Adding DNS Server: " +
                xts(items[i]->getTextContent(), true).asString());
            addDnsServer(IpAddress(xts(items[i]->getTextContent(), true)));
        }
    }
}

void XMLIsp::extractConnectionMethodsFromXML(xercesc::DOMElement *root) {
    DOMElement *methodNode = getLoneElementByTagName(root, "methods");

    if (methodNode == 0) {
        throw XMLSerializationException("No <methods> tag found!");
    }

    // Get a sorted list of servers
    vector<DOMElement*> items;
    elementsArrayFromXML(items, methodNode, "method");

    // And add them
    for (int i = 0 ; i < items.size() ; i++) {
        if (items[i] != 0) {
            // TODO: Refactor-extract method: loadConnectionMethod or use a
            // factory
            string methodType = getAttributeValue(items[i], "type");
            if (methodType == "Cables") {
                if (items[i]->getNodeType() == DOMNode::ELEMENT_NODE) {
                    DOMElement *element = dynamic_cast<DOMElement*>(items[i]);

                    if (element == 0) {
                        Log::error("Object-type mismatch");
                    } else {                    
                        Log::debug("Adding ConnectionMethod: Cables.");
                        addConnectionMethod(new Cables(element));
                    }
                }
            } else {
                Log::debug("Unknown connection method " + methodType);
            }
        }
    }
}

