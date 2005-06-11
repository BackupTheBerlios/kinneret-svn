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

using namespace std;

void ConnectionTemplate::finializeScript(Dialer *dialer) {
    string dialerCode = prepareDialerCode(dialer);

    string insertLocationString("{dialer}");
    string::size_type insertLocation = script.find(insertLocationString);
    script.replace(insertLocation, insertLocationString.length(), dialerCode);
}

string ConnectionTemplate::prepareDialerCode(Dialer *dialer) const {
    string connectionMethods =
        prepareScriptsSegment(dialer->getConnectionScripts());

    string disconnectionMethods =
        prepareScriptsSegment(dialer->getDisconnectionScripts());

    string connectMethod = prepareScriptCallingMethod("connect",
        dialer->getConnectionScripts());

    string disconnectMethod = prepareScriptCallingMethod("disconnect",
        dialer->getDisconnectionScripts());

    ostringstream result;

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

string ConnectionTemplate::prepareScriptsSegment(vector<Script*> scripts)
        const {
    ostringstream result;

    vector<Script*>::iterator iter;
    for (iter = scripts.begin() ; iter != scripts.end() ; iter++) {
        string desc = (*iter)->getScriptDescription();
        if (desc.length() > 0) {
            // Replace newlines with commented newlines
            string::size_type newline = desc.find('\n');
            while (newline != string::npos) {
                desc.replace(newline, 1, "\n# ");
                newline = desc.find('\n', newline + 1);
            }

            result <<
                "##" << endl <<
                "# " << desc << endl <<
                "##" << endl;
        }

        // TODO: Make sure there are no double definitions (name set?)
        result << (*iter)->getScriptBody() << endl;
    }

    return result.str();
}

string ConnectionTemplate::prepareScriptCallingMethod(string methodName,
        vector<Script*> scripts) const {
    ostringstream result;

    vector<Script*>::iterator iter;

    result << methodName << "() {" << endl;
    for (iter = scripts.begin() ; iter != scripts.end() ; iter++) {
        result << '\t' << (*iter)->getFunctionName() << "()" << endl;
    }
    result << "}" << endl;

    return result.str();
}

