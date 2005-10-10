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

#include "Database.h"
#include "GlobalRepository.h"
#include "Utils.h"

using namespace std;
using namespace Utils;

// Singleton instance
Database *Database::instance = 0;

Database::Database() {
    Log::debug("Creating Database...");

    loadIsps();
    loadModems();
    loadConnectionTemplates();
    loadDefaultDialers();

    Log::debug("Database created.");
}

Database::~Database() {
    Log::debug("Releasing Database...");
    
    releaseDefaultDialers();
    releaseIsps();
    releaseModems();
    releaseConnectionTemplates();

    Log::debug("Database released.");
}

vector<string> Database::enumIsps() const {
    return enumDirectory(GlobalRepository::getInstance()->
        getDbBasePath() + "/isp");
}

bool Database::loadIspFromFile(std::string file) {
    Log::debug("Loading " + file + "...");

    ifstream currentIspFile(file.c_str(), ios::in);
    if (!currentIspFile.is_open()) {
        Log::error("Unable to open " + file);
        return false;
    }

    Isp *tempIsp;
    try {
        tempIsp = GlobalRepository::getInstance()->
            getIspLoader()->loadIsp(currentIspFile);
    } catch (IspLoader::LoadException &ex) {
        Log::error(string("Failed: ") + ex.what());
        return false;
    }

    currentIspFile.close();
    isps.push_back(tempIsp);

    Log::debug("Loaded successfully.");

    return true;
}

void Database::loadIsps() {
    Log::debug("Loading ISPs...");

    // Enum files
    vector<string> ispFiles;
    try {
        ispFiles = enumIsps();
    } catch (DirectoryEnumerationException &ex) {
        throw DatabaseCreationException("Unable to enumerate ISP files.");
    }

    // And load
    vector<string>::iterator iter;
    for (iter = ispFiles.begin() ; iter != ispFiles.end() ; iter++) {
        // TODO: Load only XML files
        if (loadIspFromFile(*iter) == false) {
            Log::error("Skipping...");
        }
    }

    // Except when no ISPs were loaded (wrong format, corrupted DB etc).
    if (isps.size() == 0) {
        throw DatabaseCreationException("No ISPs found!");
    }
}

vector<string> Database::enumModems() const {
    return enumDirectory(GlobalRepository::getInstance()->
        getDbBasePath() + "/modem");
}

bool Database::loadModemFromFile(std::string file) {
    Log::debug("Loading " + file + "...");

    ifstream currentModemFile(file.c_str(), ios::in);
    if (!currentModemFile.is_open()) {
        Log::error("Unable to open " + file);
        return false;
    }

    Modem *tempModem;
    try {
        tempModem = GlobalRepository::getInstance()->
            getModemLoader()->loadModem(currentModemFile);
    } catch (ModemLoader::LoadException &ex) {
        Log::error(string("Failed: ") + ex.what());
        return false;
    }

    currentModemFile.close();
    modems.push_back(tempModem);

    Log::debug("Loaded successfully.");

    return true;
}

void Database::loadModems() {
    Log::debug("Loading Modems...");

    vector<string> modemFiles;
    try {
        modemFiles = enumModems();
    } catch (DirectoryEnumerationException &ex) {
        throw DatabaseCreationException("Unable to enumerate modem files.");
    }

    vector<string>::iterator iter;
    for (iter = modemFiles.begin() ; iter != modemFiles.end() ; iter++) {
        // TODO: Load only XML files
        if (loadModemFromFile(*iter) == false) {
            Log::error("Skipping...");
        }
    }

    // Except when no modems were loaded (wrong format, corrupted DB etc).
    if (modems.size() == 0) {
        throw DatabaseCreationException("No modems found!");
    }
}

vector<string> Database::enumConnectionTemplates() const {
    return enumDirectory(GlobalRepository::getInstance()->
        getDbBasePath() + "/template");
}

void Database::loadConnectionTemplates() {
    Log::debug("Loading connection templates...");

    vector<string> templateFiles;
    try {
        templateFiles = enumConnectionTemplates();
    } catch (DirectoryEnumerationException &ex) {
        throw DatabaseCreationException("Unable to enumerate connection "
            "template files.");
    }

    vector<string>::iterator iter;
    for (iter = templateFiles.begin() ; iter != templateFiles.end() ; iter++) {
        // TODO: Load only XML files
        if (loadConnectionTemplateFromFile(*iter) == false) {
            Log::error("Skipping...");
        }
    }

    // Except when no modems were loaded (wrong format, corrupted DB etc).
    if (connectionTemplates.size() == 0) {
        throw DatabaseCreationException("No connection templates found!");
    }
}

bool Database::loadConnectionTemplateFromFile(const std::string &file) {
    Log::debug("Loading " + file + "...");

    ifstream templateFile(file.c_str(), ios::in);
    if (!templateFile.is_open()) {
        Log::error("Unable to open " + file + " for reading!");
        return false;
    }

    ConnectionTemplate *tempTemplate;
    try {
        tempTemplate = GlobalRepository::getInstance()->
            getConnectionTemplateLoader()->
                loadConnectionTemplate(templateFile);
    } catch (ConnectionTemplateLoader::LoadException &ex) {
        Log::error(string("Failed: ") + ex.what());
        return false;
    }

    templateFile.close();
    connectionTemplates.push_back(tempTemplate);

    Log::debug("Loaded successfully.");

    return true;
}

void Database::releaseIsps() {
    // Release ISPs
    vector<Isp*>::iterator ispsIter;
    for (ispsIter = isps.begin() ; ispsIter != isps.end() ; ispsIter++) {
        Log::debug("Releasing " + (*ispsIter)->getName());
        delete (*ispsIter);
        (*ispsIter) = 0;
    }
}

void Database::releaseModems() {
    // Release modems
    vector<Modem*>::iterator modemsIter;
    for (modemsIter = modems.begin() ;
         modemsIter != modems.end() ;
         modemsIter++) {
        Log::debug("Releasing " + (*modemsIter)->getName());
        delete (*modemsIter);
        (*modemsIter) = 0;
    }
}

void Database::releaseConnectionTemplates() {
    // Release modems
    vector<ConnectionTemplate*>::iterator templatesIter;
    for (templatesIter = connectionTemplates.begin() ;
         templatesIter != connectionTemplates.end() ;
         templatesIter++) {
        Log::debug("Releasing " + (*templatesIter)->getName());
        delete (*templatesIter);
        (*templatesIter) = 0;
    }
}

void Database::loadDefaultDialers() {
    try {
        // TODO: Refactor extract method
        string path(GlobalRepository::getInstance()->
            getDbBasePath() + "/dialer/" +
            GlobalRepository::getInstance()->getDefaultPreDialerName());

        ifstream inFile(path.c_str());
        if (!inFile.is_open()) {
            throw DatabaseCreationException(string("Unable to open ") + path);
        }

        defaultPreDialer = GlobalRepository::getInstance()->
            getDialerLoader()->loadDialer(inFile);

        inFile.close();

        path = GlobalRepository::getInstance()->getDbBasePath() + "/dialer/" +
            GlobalRepository::getInstance()->getDefaultPostDialerName();

        inFile.open(path.c_str());
        if (!inFile.is_open()) {
            throw DatabaseCreationException(string("Unable to open ") + path);
        }

        defaultPostDialer = GlobalRepository::getInstance()->
            getDialerLoader()->loadDialer(inFile);

        inFile.close();
    } catch (DialerLoader::LoadException &ex) {
        throw DatabaseCreationException(
            string("Unable to create default dialers: ") + ex.what());
    }
}

void Database::releaseDefaultDialers() {
    if (defaultPreDialer != 0) {
        delete defaultPreDialer;
        defaultPreDialer = 0;
    }

    if (defaultPostDialer != 0) {
        delete defaultPostDialer;
        defaultPostDialer = 0;
    }
}

