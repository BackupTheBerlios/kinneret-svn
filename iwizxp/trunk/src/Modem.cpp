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

#include <fstream>

#include "Modem.h"

#include "Log.h"
#include "Utils.h"
#include "xts.h"
#include "GlobalRepository.h"

using namespace std;
using namespace xercesc;
using namespace Utils;
using namespace Utils::DOM;

void Modem::fromXML(DOMElement *root) {
    NamedXMLReadable::fromXML(root);
    loadModulesFromXML(root);
    loadDialersFromXML(root);
}

void Modem::loadModulesFromXML(DOMElement *root) {
    DOMElement *modulesNode = getLoneElementByTagName(root, "modules");

    if (modulesNode == 0) {
        throw XMLSerializationException("No <modules> tag found!");
    }

    // Get a sorted list of servers
    vector<DOMElement*> items;
    elementsArrayFromXML(items, modulesNode, "module");

    for (int i = 0 ; i < items.size() ; i++) {
        addModule(new KernelModule(items[i]));
    }
}

void Modem::loadDialersFromXML(DOMElement *root) {
    DOMElement *dialerNode = getLoneElementByTagName(root, "dialer");
    if (dialerNode == 0) {
        throw XMLSerializationException("No <dialer> element!");
    }

    loadDefaultDialer(dialerNode);
    loadExceptions(dialerNode);
}

void Modem::loadDefaultDialer(DOMElement *dialerNode) {
    DOMElement *defaultDialerNode =
        getLoneElementByTagName(dialerNode, "default");

    if (defaultDialerNode == 0) {
        throw XMLSerializationException("No <default> element!");
    }

    string dialerName = xts(defaultDialerNode->getTextContent(), true);
    if (dialerName.length() == 0) {
        throw XMLSerializationException("Empty dialer name!");
    }

    defaultDialer = loadDialerByName(dialerName);
}

void Modem::loadExceptions(DOMElement *dialerNode) {
    DOMElement *exceptionsNode =
        getLoneElementByTagName(dialerNode, "exceptions");
    if (exceptionsNode == 0) {
        throw XMLSerializationException("No <exceptions> element!");
    }

    vector<DOMElement*> exceptionElements;
    elementsArrayFromXML(exceptionElements, dialerNode, "exception");

    if (exceptionElements.size() <= 0) {
        Log::debug("No Exceptions");
    } else {
        for (int i = 0 ; i < exceptionElements.size() ; i++) {
            if (exceptionElements[i] == 0) {
                Log::warning("Incorrect item entry, skipping...");
                continue;
            }
            
            string isp = getAttributeValue(exceptionElements[i], "isp");
            if (isp.length() == 0) {
                throw XMLSerializationException("No 'isp' attribute found in"
                    " exception!");
            }

            string dialer = xts(exceptionElements[i]->getTextContent(), true);
            if (dialer.length() == 0) {
                throw XMLSerializationException("Empty dialer found in "
                    "exception!");
            }

            exceptions[isp] = loadDialerByName(dialer);
        }
    }
}

Dialer *Modem::loadDialerByName(string name) {
    string dialerName =
        GlobalRepository::getInstance()->getDbBasePath() + "/dialer/" + name;

    ifstream dialerStream(dialerName.c_str(), ios::in);

    if (!dialerStream.is_open()) {
        throw XMLSerializationException("Unable to load default dialer!");
    }

    Dialer *dialer = 0;

    try {
        dialer =
            GlobalRepository::getInstance()->getDialerLoader()->
                loadDialer(dialerStream);
    } catch (DialerLoader::LoadException &ex) {
        throw XMLSerializationException(string("LoadException: ") + ex.what());
    }

    dialerStream.close();

    if (dialer != 0) {
        addDialer(dialer);
    }

    return dialer;
}

Modem::~Modem() {
    releaseKernelModules();
    releaseDialers();
}

void Modem::releaseKernelModules() {
    vector<KernelModule*>::iterator iter;
    for (iter = modulesVector.begin() ; iter != modulesVector.end() ; iter++) {
        Log::debug(string("Releasing ") + (*iter)->toString() + "...");
        delete (*iter);
        (*iter) = 0;
    } 
}

void Modem::releaseDialers() {
    vector<Dialer*>::iterator iter;
    for (iter = loadedDialers.begin() ; iter != loadedDialers.end() ; iter++) {
        Log::debug(string("Releasing ") + (*iter)->toString() + "...");
        delete (*iter);
        (*iter) = 0;
    } 
}
    
Dialer *Modem::getDialer(Isp *isp) {
    map<string, Dialer *>::iterator exception = exceptions.find(isp->getName());
    if (exception == exceptions.end()) {
        return defaultDialer;
    } else {
        return exception->second;
    }
}

