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

#include "ConnectionTemplate.h"
#include "Database.h"

using namespace std;

string ConnectionTemplate::getFinalScript(Dialer *dialer) {
	if (finalized == false) {
		string dialerCode = prepareDialerCode(dialer);

		string insertLocationString("{dialer}");
		
		string::size_type insertLocation =
			script.find(insertLocationString);

		script.replace(insertLocation,
			insertLocationString.length(), dialerCode);

		finalized = true;
	}

	return script;
}

string ConnectionTemplate::prepareDialerCode(Dialer *dialer) const {
	// All the scripts, including the default pre- and post- scripts.
	vector<Script*> allConnectionScripts = dialer->getConnectionScripts();
	vector<Script*> allDisconnectionScripts =
		dialer->getDisconnectionScripts();

	// Add default dialers settings
	addDefaults(allConnectionScripts, allDisconnectionScripts);

	// Set to prevent doubles
	set<string> alreadyWritten;

	// Method definitions
	string connectionMethods = prepareScriptsSegment(allConnectionScripts,
		alreadyWritten);

	string disconnectionMethods =
		prepareScriptsSegment(allDisconnectionScripts, alreadyWritten);

	// Calling methods
	string connectMethod = prepareScriptCallingMethod("connect",
		"This method calls the methods above in the correct order.\n"
		"Call this method when you wish to create a new connection.",
		allConnectionScripts);

	string disconnectMethod = prepareScriptCallingMethod("disconnect",
		"This method calls the methods above in the correct order.\n"
		"Call this method when you wish to eliminate a current "
		"connection.", allDisconnectionScripts);

	ostringstream result;

	// Result
	result <<
		"# --- Connection Methods --- #" << endl << endl <<
		connectionMethods << endl << endl <<
		"# --- Disconnection Methods --- #" << endl << endl <<
		disconnectionMethods << endl << endl <<
		"# --- Connect --- #" << endl << endl <<
		connectMethod << endl << endl <<
		"# --- Disconnect --- #" << endl << endl <<
		disconnectMethod << endl;

	return result.str();
}

string ConnectionTemplate::prepareScriptsSegment(vector<Script*> scripts,
		set<string> &alreadyWritten) const {
	ostringstream result;

	vector<Script*>::iterator iter;
	for (iter = scripts.begin() ; iter != scripts.end() ; iter++) {
		// Write the body only of it wasn't written before
		if (alreadyWritten.find((*iter)->getFunctionName()) ==
				alreadyWritten.end()) {

			// Add it to the set
			alreadyWritten.insert((*iter)->getFunctionName());

			// If there is a description, add it as a header
			string desc = (*iter)->getScriptDescription();
			if (desc.length() > 0) {
				result << formatDescription(desc) << endl;
			}

			// Write script body
			result << (*iter)->getScriptBody() << endl;
		} else {
			// The method already defined. Leave a comment that
			// we've notcied that.
			result << "# " << (*iter)->getFunctionName() <<
				" already found in script." << endl << endl;
		}
	}

	return result.str();
}

string ConnectionTemplate::prepareScriptCallingMethod(string methodName,
		string description, vector<Script*> scripts) const {
	ostringstream result;

	// Add description
	if (description.length() > 0) {
		result << formatDescription(description) << endl;
	}

	// Method decleration
	result << methodName << "() {" << endl;

	// Methods body
	vector<Script*>::iterator iter;
	for (iter = scripts.begin() ; iter != scripts.end() ; iter++) {
		result << '\t' << (*iter)->getFunctionName() << endl;
	}

	// Close
	result << "}" << endl;

	return result.str();
}

string ConnectionTemplate::formatDescription(string description) const {
	ostringstream result;

	// Replace newlines with commented newlines
	string::size_type newline = description.find('\n');
	while (newline != string::npos) {
		description.replace(newline, 1, "\n# ");
		newline = description.find('\n', newline + 1);
	}

	// Write header
	result <<
		"##" << endl <<
		"# " << description << endl <<
		"##";

	return result.str();
}

void ConnectionTemplate::addDefaults(vector<Script*> &connectionScripts,
		vector<Script*> &disconnectionScripts) const {
	Dialer *preDialer = Database::getInstance()->getDefaultPreDialer();
	Dialer *postDialer = Database::getInstance()->getDefaultPostDialer();

	// Prepend
	connectionScripts.insert(connectionScripts.begin(),
		preDialer->getConnectionScripts().begin(),
		preDialer->getConnectionScripts().end());

	disconnectionScripts.insert(disconnectionScripts.begin(),
		preDialer->getDisconnectionScripts().begin(),
		preDialer->getDisconnectionScripts().end());

	// Append
	connectionScripts.insert(connectionScripts.end(),
		postDialer->getConnectionScripts().begin(),
		postDialer->getConnectionScripts().end());

	disconnectionScripts.insert(disconnectionScripts.end(),
		postDialer->getDisconnectionScripts().begin(),
		postDialer->getDisconnectionScripts().end());
}

