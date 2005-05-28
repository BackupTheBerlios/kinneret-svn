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

#include <sys/types.h>
#include <dirent.h>

#include <fstream>

#include "Database.h"
#include "GlobalRepository.h"

using namespace std;

Database::Database() {
    Log::debug("Creating database.");

    loadIsps();
    loadModems();
}

Database::~Database() {
    releaseIsps();
    releaseModems();
}

void Database::loadIsps() {
    Log::debug("Loading ISPs...");

    vector<string> ispFiles;
    try {
        enumDirectory(GlobalRepository::getInstance()->getDbBasePath() +
            "/isp", ispFiles);
    } catch (DirectoryEnumerationException &ex) {
        throw DatabaseCreationException("Unable to enumerate ISP files.");
    }

    vector<string>::iterator ispFilesIter;
    for (ispFilesIter = ispFiles.begin() ; 
         ispFilesIter != ispFiles.end() ;
         ispFilesIter++) {
        Log::debug("Loading " + (*ispFilesIter) + "...");

        ifstream currentIspFile((*ispFilesIter).c_str(), ios::in);
        if (!currentIspFile.is_open()) {
            Log::error("Unable to open " + (*ispFilesIter) + ", skipping...");
            continue;
        }
        
        Isp *tempIsp;
        try {
            tempIsp = GlobalRepository::getInstance()->
                getIspLoader()->loadIsp(currentIspFile);
        } catch (IspLoader::LoadExcpetion &ex) {
            Log::error(string("Failed: ") + ex.what() + " Skipping...");
            continue;
        }

        currentIspFile.close();
        isps.push_back(tempIsp);
    }

    if (isps.size() == 0) {
        throw DatabaseCreationException("No ISPs found!");
    }
}

void Database::loadModems() {
    Log::debug("Loading Modems...");

    vector<string> modemFiles;
    try {
        enumDirectory(GlobalRepository::getInstance()->getDbBasePath() +
            "/modem", modemFiles);
    } catch (DirectoryEnumerationException &ex) {
        throw DatabaseCreationException("Unable to enumerate modem files.");
    }

    vector<string>::iterator modemFilesIter;
    for (modemFilesIter = modemFiles.begin() ; 
         modemFilesIter != modemFiles.end() ;
         modemFilesIter++) {
        Log::debug("Loading " + (*modemFilesIter) + "...");

        ifstream currentModemFile((*modemFilesIter).c_str(), ios::in);
        if (!currentModemFile.is_open()) {
            Log::error("Unable to open " + (*modemFilesIter) +
                ", skipping...");
            continue;
        }
        
        Modem *tempModem;
        try {
            tempModem = GlobalRepository::getInstance()->
                getModemLoader()->loadModem(currentModemFile);
        } catch (ModemLoader::LoadExcpetion &ex) {
            Log::error(string("Failed: ") + ex.what() + " Skipping...");
            continue;
        }

        currentModemFile.close();
        modems.push_back(tempModem);
    }

    if (modems.size() == 0) {
        throw DatabaseCreationException("No modems found!");
    }
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

void Database::enumDirectory(string directory, vector<string> &files)
        const throw (DirectoryEnumerationException) {
    files.clear();

    Log::debug(string("Enumerating ") + directory + string("..."));
    DIR *dir = opendir(directory.c_str());
    if (dir == 0) {
        string reason(strerror(errno));

        Log::error("Unable to enumerate " + directory + ": " + reason);
        throw DirectoryEnumerationException(reason);
    }

    // Browse...
    dirent *entry = 0;
    while ((entry = readdir(dir)) != 0) {
        string entryName(entry->d_name);

        // Skip hidden files, . and ..
        if (entryName.find(".") == 0) {
            continue;
        }

        files.push_back(directory + "/" + entryName);
    }

    // Close file descriptor
    if (closedir(dir) != 0) {
        // Ignore the error, we're done.
    }
    
    if (files.size() == 0) {
        throw DirectoryEnumerationException(string("No files in ") +
            directory);
    }
}

