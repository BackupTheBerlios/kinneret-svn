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
 * TODO
 */
class FixedScript : public Script {
public:

    /* --- Constructors --- */

    /**
     * TODO
     */
    FixedScript(std::string functionName,
                const std::istream &scriptStream) : Script() {
        this->functionName = functionName;
        loadScriptBody(scriptStream);
    }

    /**
     * TODO
     */
    virtual ~FixedScript() {
    }

    /* --- Inherited from Script --- */

    /**
     * TODO
     */
    virtual const std::string getFunctionName() const {
        return functionName;
    }

    /**
     * TODO
     */
    virtual const std::string getScriptBody() const {
        return scriptBody;
    }

private:

    /* --- Private Methods --- */

    /**
     * TODO
     */
    void loadScriptBody(const std::istream &scriptStream) {
        // TODO
    }

    /* --- Data Members --- */

    /** TODO */
    std::string functionName;

    /** TODO */
    const std::string scriptBody;
};

#endif
