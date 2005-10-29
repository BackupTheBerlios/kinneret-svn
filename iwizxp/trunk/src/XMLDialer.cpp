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

#include "XMLDialer.h"

#include "GlobalRepository.h"
#include "Utils.h"
#include "xts.h"

using namespace std;
using namespace xercesc;
using namespace Utils;
using namespace Utils::DOM;

void XMLDialer::fromXML(DOMElement *root) {
	NamedXMLReadable::fromXML(root);
	extractConnectionScriptsFromXML(root);
	extractDisconnectionScriptsFromXML(root);
}

void XMLDialer::extractConnectionScriptsFromXML(DOMElement *root) {
	DOMElement *connectionNode =
		getLoneElementByTagName(root, "connection");

	if (connectionNode == 0) {
		Log::debug(LOG_LOCATION("XMLDialer",
			"extractConnectionScriptsFromXML"),
			"Dialer containes no connection scripts.");
		return;
	}

	// Get a sorted list of servers
	vector<DOMElement*> items;
	elementsArrayFromXML(items, connectionNode, "script");

	// And add them
	for (int i = 0 ; i < items.size() ; i++) {
		if (items[i] != 0) {
			string scriptName =
				xts(items[i]->getTextContent(),
					true).asString();

			// The arguments script is a special case
			if (string(scriptName) ==
					GlobalRepository::getInstance()->
					getArgumentsScript()->
					getFunctionName()) {

				addConnectionScript(
					GlobalRepository::getInstance()->
					getArgumentsScript());

				continue;
			}

			// Load a fixed script
			addConnectionScript(loadScripByName(scriptName));
		}
	}
}

void XMLDialer::extractDisconnectionScriptsFromXML(DOMElement *root) {
	DOMElement *disconnectionNode =
		getLoneElementByTagName(root, "disconnection");

	if (disconnectionNode == 0) {
		Log::debug(LOG_LOCATION("XMLDialer",
			"extractDisconnectionScriptsFromXML"),
			"Dialer containes no disconnection scripts.");
		return;
	}

	// Get a sorted list of servers
	vector<DOMElement*> items;
	elementsArrayFromXML(items, disconnectionNode, "script");

	// And add them
	for (int i = 0 ; i < items.size() ; i++) {
		if (items[i] != 0) {
			string scriptName =
				xts(items[i]->getTextContent(),
					true).asString();

			// The arguments script is a special case
			if (string(scriptName) ==
					GlobalRepository::getInstance()->
					getArgumentsScript()->
					getFunctionName()) {

				addConnectionScript(
					GlobalRepository::getInstance()->
					getArgumentsScript());

				continue;
			}

			// Load a fixed script
			addDisconnectionScript(loadScripByName(scriptName));
		}
	}
}

Script *XMLDialer::loadScripByName(string scriptName) {
	// TODO: Don't hardcode path
	string fileName(GlobalRepository::getInstance()->getDbBasePath() +
		"/script/" + scriptName);

	Log::debug(LOG_LOCATION("XMLDialer", "loadScripByName"),
		string("Loading: ") + fileName);

	ifstream scriptStream(fileName.c_str());
	if (!scriptStream.is_open()) {
		throw XMLSerializationException(fileName +
			" cannot be opened.");
	}

	Script *result = 0;

	try {
		result = GlobalRepository::getInstance()->
			getScriptLoader()->loadScript(scriptStream);
	} catch (DialerLoader::LoadException &ex) {
		scriptStream.close();
		throw XMLSerializationException(
			string("Unable to load script: ") + ex.what());
	}

	scriptStream.close();
	return result;
}

