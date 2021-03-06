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

#include "BashSyntaxScriptLoader.h"
#include "Utils.h"
#include "Log.h"
#include "FixedScript.h"

using namespace std;
using namespace Utils;

Script *BashSyntaxScriptLoader::loadScript(istream &inStream) const {
	string body = readStreamAsString(inStream);
	string name = extractNameFromScript(body);

	Log::debug(LOG_LOCATION("BashSyntaxScriptLoader", "loadScript"),
		string("BashSyntaxScriptLoader successfully loaded: ") + name);

	return new FixedScript(name, body);
}

string BashSyntaxScriptLoader::extractNameFromScript(const string &body) const {
	// This will catch the definition line
	static const string regexString(
		"^[[:blank:]]*"
		"[[:alnum:]_]+"
		"[[:blank:]]*"
		"\\("
		"[[:blank:]]*"
		"\\)"
		"[[:blank:]]*"
		"\\{"
		"[[:blank:]]*"
	);

	// Execute regex
	vector<string> regexResult;
	try {
		regexResult = executeRegex(regexString, body, 1);
	} catch (RegexException &ex) {
		throw LoadException(string("Regex Exception: ") + ex.what());
	}

	if (regexResult.size() == 0) {
		throw LoadException("Invalid bash syntax, "
			"could not find definition line.");
	}

	return extractNameFromDefinitionLine(regexResult[0]);
}

string BashSyntaxScriptLoader::extractNameFromDefinitionLine(const string &body)
		const {
	// This will catch the title line
	static const string regexString("[[:alnum:]_]+");

	vector<string> regexResult;
	try {
		regexResult = executeRegex(regexString, body, 1);
	} catch (RegexException &ex) {
		throw LoadException(string("Regex Exception: ") + ex.what());
	}

	if (regexResult.size() == 0) {
		Log::bug(LOG_LOCATION("BashSyntaxScriptLoader",
			"extractNameFromDefinitionLine"),
			"Should have been called from extractNameFromScript, "
			"which made sure we would find this regex!");

		throw LoadException("Bug. Please report.");
	}

	return regexResult[0];
}

