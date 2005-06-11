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

#include "SimpleFormatDialerLoader.h"
#include "GlobalRepository.h"

#include "Log.h"

using namespace std;

Dialer *SimpleFormatDialerLoader::loadDialer(istream &inStream) const
        throw (LoadException) {
    Dialer *result;
    
    // Load name
    char name[MAX_LINE];
    inStream.getline(name, MAX_LINE, '\n');

    Log::debug(string("Dialer's name: ") + name);

    result = new Dialer(name);

    int count;
    inStream >> count;
    inStream.ignore(MAX_LINE, '\n');

    for (int i = 0 ; i < count ; i++) {
        inStream.getline(name, MAX_LINE, '\n');
        Script *script;

        string fileName(GlobalRepository::getInstance()->
                getDbBasePath() + "/script/" + name);

        Log::debug(string("Loading: ") + fileName);

        ifstream file(fileName.c_str());

        try {
            script = GlobalRepository::getInstance()->
                getScriptLoader()->loadScript(file);
        } catch (DialerLoader::LoadException &ex) {
            file.close();
            throw LoadException(string("Unable to load script: ") +
                    ex.what());
        }

        file.close();
        result->addConnectionScript(script);
    }

    inStream >> count;
    inStream.ignore(MAX_LINE, '\n');

    for (int i = 0 ; i < count ; i++) {
        inStream.getline(name, MAX_LINE, '\n');
        Script *script;

        string fileName(GlobalRepository::getInstance()->
                getDbBasePath() + "/script/" + name);

        Log::debug(string("Loading: ") + fileName);

        ifstream file(fileName.c_str());

        try {
            script = GlobalRepository::getInstance()->
                getScriptLoader()->loadScript(file);
        } catch (DialerLoader::LoadException &ex) {
            file.close();
            throw LoadException(
                string("Unable to load script: ") + ex.what());
        }

        file.close();
        result->addDisconnectionScript(script);
    }

    return result;
}

