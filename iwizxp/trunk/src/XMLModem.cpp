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

#include "XMLModem.h"

#include "Utils.h"
#include "xts.h"
#include "XMLKernelModule.h"

using namespace std;
using namespace xercesc;
using namespace Utils;
using namespace Utils::DOM;

void XMLModem::fromXML(DOMElement *root) {
	NamedXMLReadable::fromXML(root);
	loadModulesFromXML(root);
	loadDialersFromXML(root);
}

void XMLModem::loadModulesFromXML(DOMElement *root) {
	DOMElement *modulesNode = getLoneElementByTagName(root, "modules");

	if (modulesNode == 0) {
		throw XMLSerializationException("No <modules> tag found!");
	}

	// Get a sorted list of servers
	vector<DOMElement*> items;
	elementsArrayFromXML(items, modulesNode, "module");

	for (int i = 0 ; i < items.size() ; i++) {
		XMLKernelModule *module = new XMLKernelModule();
		module->fromXML(items[i]);
		addModule(module);
	}
}

void XMLModem::loadDialersFromXML(DOMElement *root) {
	DOMElement *dialerNode = getLoneElementByTagName(root, "dialer");
	if (dialerNode == 0) {
		throw XMLSerializationException("No <dialer> element!");
	}

	loadDefaultDialer(dialerNode);
	loadExceptions(dialerNode);
}

void XMLModem::loadDefaultDialer(DOMElement *dialerNode) {
	DOMElement *defaultDialerNode =
		getLoneElementByTagName(dialerNode, "default");

	if (defaultDialerNode == 0) {
		throw XMLSerializationException("No <default> element!");
	}

	string dialerName = xts(defaultDialerNode->getTextContent(), true);
	if (dialerName.length() == 0) {
		throw XMLSerializationException("Empty dialer name!");
	}

	try {
		setDefaultDialer(loadDialerByName(dialerName));
	} catch (DialerCreationException &ex) {
		throw XMLSerializationException(string("LoadException: ") +
			ex.what());
	}
}

void XMLModem::loadExceptions(DOMElement *dialerNode) {
	DOMElement *exceptionsNode =
		getLoneElementByTagName(dialerNode, "exceptions");
	if (exceptionsNode != 0) {
		vector<DOMElement*> exceptionElements;
		elementsArrayFromXML(exceptionElements, exceptionsNode,
			"exception");

		for (int i = 0 ; i < exceptionElements.size() ; i++) {
			if (exceptionElements[i] == 0) {
				Log::warning(LOG_LOCATION("XMLModem",
					"loadExceptions"),
					"Incorrect item entry, skipping...");
				continue;
			}

			string isp =
				getAttributeValue(exceptionElements[i], "isp");
			
			if (isp.length() == 0) {
				throw XMLSerializationException("No 'isp' "
					"attribute found in exception!");
			}

			string dialer =
				xts(exceptionElements[i]->getTextContent(),
					true);
			
			if (dialer.length() == 0) {
				throw XMLSerializationException("Empty dialer "
					"found in exception!");
			}

			try {
				addException(isp, loadDialerByName(dialer));
			} catch (DialerCreationException &ex) {
				throw XMLSerializationException(
					string("LoadException: ") + ex.what());
			}
		}
	} else {
		Log::debug(LOG_LOCATION("XMLModem", "loadExceptions"),
			"No exceptions");
	}
}

