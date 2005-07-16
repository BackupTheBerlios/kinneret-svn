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

#include <iostream>
#include <cctype>
#include <algorithm>

#include "Log.h"

#include "Utils.h"

using namespace std;

// The instance
Log *Log::instance;
map<Log::LogLevel, string> Log::levelNames;

#define REGISTER_LOG_LEVEL(m, level) m[level] = #level
void Log::initLogLevels() {
    REGISTER_LOG_LEVEL(levelNames, ALL);
    REGISTER_LOG_LEVEL(levelNames, DEBUG);
    REGISTER_LOG_LEVEL(levelNames, INFO);
    REGISTER_LOG_LEVEL(levelNames, WARNING);
    REGISTER_LOG_LEVEL(levelNames, ERROR);
    REGISTER_LOG_LEVEL(levelNames, FATAL);
    REGISTER_LOG_LEVEL(levelNames, BUG);
    REGISTER_LOG_LEVEL(levelNames, NONE);
}

Log::Log(LogLevel level) {
    logLevel = level;

    if (levelNames.size() == 0) {
        initLogLevels();
    }
}

void Log::create(LogLevel level) {
    instance = new Log(level);
}

void Log::release() {
    delete instance;
}

void Log::log(LogLevel level, const std::string &msg) {
    if (level >= logLevel) {
        cerr << levelNames[level] << " > " << msg << endl;
    }
}

void Log::bug(const std::string &msg) {
    instance->log(BUG, msg);
}

void Log::fatal(const std::string &msg) {
    instance->log(FATAL, msg);
}

void Log::error(const std::string &msg) {
    instance->log(ERROR, msg);
}

void Log::warning(const std::string &msg) {
    instance->log(WARNING, msg);
}

void Log::info(const std::string &msg) {
    instance->log(INFO, msg);
}

void Log::debug(const std::string &msg) {
    instance->log(DEBUG, msg);
}
    
Log::LogLevel Log::levelFromString(string level) {
    if (levelNames.size() == 0) {
        initLogLevels();
    }

    // Transform string to uppercase
    transform(level.begin(), level.end(), level.begin(),
        Utils::safeStl<toupper>);

    map<LogLevel, string>::iterator iter;
    for (iter = levelNames.begin() ; iter != levelNames.end() ; iter++) {
        if (iter->second == level) {
            return iter->first;
        }
    }

    throw FormatException(level + " is an unknown log level");
}

