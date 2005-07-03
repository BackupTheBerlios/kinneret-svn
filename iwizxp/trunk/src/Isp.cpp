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

#include <sstream>

#include <xercesc/dom/DOMElement.hpp>

#include "Isp.h"
#include "Cables.h"
#include "Utils.h"
#include "xts.h"

using namespace std;
using namespace xercesc;
using namespace Utils;

Isp::~Isp() {
    std::vector<ConnectionMethod*>::iterator iter;
    for (iter = methods.begin() ; iter != methods.end() ; iter++) {
        Log::debug(string("Releasing ") + (*iter)->toString() + "...");
        delete (*iter);
        (*iter) = 0;
    }
    
    Log::debug(string("Isp: ") + name + " released successfully");
}

void Isp::fromXML(const DOMElement *root) throw (XMLFormatException) {
    extractNameFromXML(root);
    extractDnsServersFromXML(root);
    extractConnectionMethodsFromXML(root);
}

void Isp::extractNameFromXML(const xercesc::DOMElement *root)
        throw (XMLFormatException) {
    vector<const DOMNode*> rootNameNodes;
    getElementsByTagName(rootNameNodes, root, "name", 1);

    // Warn, if more than one node found
    if (rootNameNodes.size() > 1) {
        Log::warning(string("More than one <name> tag found, using first."));
    }

    // Take the first
    const DOMNode *nameTag = rootNameNodes[0];
    if (nameTag == 0) {
        throw XMLFormatException("Couldn't get <name> tag element!");
    }

    // Extract and trim its text content.
    name = xts(nameTag->getTextContent(), true);
            
    Log::debug(string("Isp's name: ") + name);
}

void Isp::extractDnsServersFromXML(const xercesc::DOMElement *root)
        throw (XMLFormatException) {
    vector<const DOMNode*> dnsServerNodes;
    getElementsByTagName(dnsServerNodes, root, "dns", 1);

    // Warn, if more than one node found
    if (dnsServerNodes.size() > 1) {
        Log::warning(string("More than one <dns> tag found, using first."));
    }

    const DOMNode *dnsElement = dnsServerNodes[0];
    if (dnsElement == 0) {
        throw XMLFormatException("Couldn't get <dns> tag element!");
    }

    // Get a sorted list of servers
    vector<const DOMNode*> items;
    sortXMLList(items, dnsElement, "server");

    // And add them
    for (int i = 0 ; i < items.size() ; i++) {
        if (items[i] != 0) {
            Log::debug("Adding DNS Server: " +
                xts(items[i]->getTextContent(), true).asString());
            addDnsServer(IpAddress(xts(items[i]->getTextContent(), true)));
        }
    }
}

void Isp::extractConnectionMethodsFromXML(const xercesc::DOMElement *root)
        throw (XMLFormatException) {
    vector<const DOMNode*> methodNodes;
    getElementsByTagName(methodNodes, root, "methods", 1);

    // Warn, if more than one node found
    if (methodNodes.size() > 1) {
        Log::warning(string("More than one <method> tag found, using first."));
    }

    const DOMNode *methodsElement = methodNodes[0];
    if (methodsElement == 0) {
        throw XMLFormatException("Couldn't get <methods> tag element!");
    }

    // Get a sorted list of servers
    vector<const DOMNode*> items;
    sortXMLList(items, methodsElement, "method");

    // And add them
    for (int i = 0 ; i < items.size() ; i++) {
        if (items[i] != 0) {
            string methodType = getAttribute(items[i], "type");
            if (methodType == "Cables") {
                if (items[i]->getNodeType() == DOMNode::ELEMENT_NODE) {
                    const DOMElement *element =
                        dynamic_cast<const DOMElement*>(items[i]);

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

