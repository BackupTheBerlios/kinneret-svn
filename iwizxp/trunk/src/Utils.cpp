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
#include <regex.h>

#include <sstream>

#include "Utils.h"
#include "Log.h"

// For regex error reporting
#define ERROR_BUFFER_SIZE 1024

using namespace std;

string Utils::readStreamAsString(istream &inStream) {
    ostringstream result;

    while (!inStream.eof()) {
        result << inStream.get();
    }

    return result.str();
}

vector<string> Utils::enumDirectory(string directory)
        throw (Utils::DirectoryEnumerationException) {
    vector<string> files;

    Log::debug(string("Enumerating ") + directory + string("..."));

    // Open file descriptor
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

        // Skip hidden files, '.' and '..'
        if (entryName.find(".") == 0) {
            continue;
        }

        // Add the file to the list
        files.push_back(directory + "/" + entryName);
    }

    // Close file descriptor
    if (closedir(dir) != 0) {
        // Ignore the error, we're done.
    }

    return files;
}

vector<string> Utils::executeRegex(const string &regexString,
        const string &matchString, int maxResults) throw (RegexException) {
    vector<string> result;
    
    // Buffer for regex error strings
    char errorBuffer[ERROR_BUFFER_SIZE];

    // Compile RegEx
    regex_t compiledRegex;
    int ret = regcomp(&compiledRegex, regexString.c_str(), REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &compiledRegex, errorBuffer, ERROR_BUFFER_SIZE);
        throw RegexException(
            string("Unable to compile regex: ") + errorBuffer);
    }

    // Execute Regex to find title
    regmatch_t *regexMatches = new regmatch_t[maxResults];
    if (regexMatches == 0) {
        regfree(&compiledRegex);
        throw RegexException("Unable to allocate resuls array!");
    }
    
    ret = regexec(&compiledRegex, matchString.c_str(),
        maxResults, regexMatches, 0);

    // Collect results
    if (ret != REG_NOMATCH) {
        int i;
        regmatch_t *current;
        for (current = regexMatches, i = 0 ;
                i < maxResults ; i++, current++) {

            if ((current->rm_so != -1) && (current->rm_eo != -1)) {
                // Valid match
                result.push_back(
                    matchString.substr(current->rm_so, current->rm_eo));
            }
        }
    }
    
    delete[] regexMatches;
    regfree(&compiledRegex);

    return result;
}

