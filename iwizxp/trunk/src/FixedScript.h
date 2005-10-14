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

#ifndef __FIXED_SCRIPT_H__
#define __FIXED_SCRIPT_H__

#include <istream>

#include "Script.h"

/**
 * This is a fixed script. This script is simply loaded from an input stream,
 * and printed to the dialer as it was read.
 *
 * Most of the scripts are fixed scripts. Do not confuse fixed scripts with
 * static scripts, fixed scripts might behave in a dynamic manner (most of
 * the scripts in the database act according to the environment variables).
 *
 * A fixes scripts usually does something very specific, and might be treated
 * as a "method that was refactored out".
 *
 * @author duvduv
 */
class FixedScript : public Script {
public:

    /* --- Constructors --- */

    /**
     * Constructor. Loads the script from the input stream.
     *
     * @param functionName The name of the funtion.
     * @param scriptBody The script as a srting.
     */
    FixedScript(const std::string &functionName,
                const std::string &scriptBody) : Script() {
        this->functionName = functionName;
        this->scriptBody = scriptBody;

        Log::debug(LOG_LOCATION("FixedScript", "FixedScript"),
            std::string("Constructing FixedScript (") +
                functionName + ")");
    }

    /**
     * Destructor, does nothing.
     */
    virtual ~FixedScript() {
        Log::debug(LOG_LOCATION("FixedScript", "~FixedScript"),
            std::string("Destroying FixedScript (") +
                functionName + ")");
    }

    /* --- Inherited from Script --- */

    /**
     * @return The function name.
     */
    virtual const std::string getFunctionName() const {
        return functionName;
    }

    /**
     * @return The body.
     */
    virtual const std::string getScriptBody() const {
        return scriptBody;
    }

    /**
     * In this case, we leave the description empty. We trust the body itself
     * already containes a comment that describes it.
     * 
     * @return An empty string.
     */
    virtual const std::string getScriptDescription() const {
        return "";
    }

private:

    /* --- Data Members --- */

    /** The function's name */
    std::string functionName;

    /** The function's body */
    std::string scriptBody;
};

#endif
