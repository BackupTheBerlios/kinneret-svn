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
 * This is a fiex script. This script is simply loaded from an input stream,
 * and printed to the template as it was read.
 *
 * @author duvduv
 */
class FixedScript : public Script {
public:

    /* --- Constructors --- */

    /**
     * Constructor. Loads the script from the input stream.
     *
     * @param functionName The name of the funtion this script's body will be
     *        placed in.
     * @param scriptStream The input stream we'll read the script from.
     */
    FixedScript(std::string functionName,
                const std::istream &scriptStream) : Script() {
        this->functionName = functionName;
        loadScriptBody(scriptStream);
    }

    /**
     * Destructor, does nothing.
     */
    virtual ~FixedScript() {
        // Nothing to do
    }

    /* --- Inherited from Script --- */

    /**
     * @return The function name
     */
    virtual const std::string getFunctionName() const {
        return functionName;
    }

    /**
     * @return The body, as it was read from the input stream.
     */
    virtual const std::string getScriptBody() const {
        return scriptBody;
    }

private:

    /* --- Private Methods --- */

    /**
     * TODO: Refactor-move method to a utility class. The same method is used
     * in ConnectionTemplate.
     *
     * Loads everything from the stream (up until EOF) to the string.
     *
     * @param scriptStream Stream to read
     */
    void loadScriptBody(const std::istream &scriptStream) {
        // TODO: Implement
    }

    /* --- Data Members --- */

    /** The function's name */
    std::string functionName;

    /** The function's body */
    const std::string scriptBody;
};

#endif
