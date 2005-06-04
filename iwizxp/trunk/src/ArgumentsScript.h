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

#ifndef __ARGUMENTS_SCRIPT_H__
#define __ARGUMENTS_SCRIPT_H__

#include "Script.h"
#include "Isp.h"
#include "ConnectionMethod.h"
#include "Modem.h"

/**
 * This class represents the script that sets all of the user arguments. This
 * is the first script called for every connection, setting all the user
 * defined variables required for the other scripts to work.
 *
 * @author duvduv
 */
class ArgumentsScript : public Script {
public:

    /* --- Constructors --- */

    /**
     * Constructor.
     *
     * @param isp Selected ISP.
     * @param method Selected connection method.
     * @param modem Selected modem.
     */
    ArgumentsScript(const Isp *isp,
                    const ConnectionMethod *method,
                    const Modem *modem) : Script() {
        this->isp = isp;
        this->method = method;
        this->modem = modem;
    }

    /**
     * Destructor, does nothing.
     */
    virtual ~ArgumentsScript() {
        // Nothing to do.
    }

    /* --- Inherited from Script --- */

    /**
     * @return The name of the function that has to be called in order to
     *         execute this script.
     */
    virtual const std::string getFunctionName() const {
        return "setupUserArguments";
    }

    /**
     * @return A valid-syntax Bash script, that sets up all the user defined
     *         variables.
     */
    virtual const std::string getScriptBody() const {
        // TODO
    }

private:

    /* --- Data Members --- */

    /** Selected ISP */
    const Isp *isp;

    /** Selected connection method */
    const ConnectionMethod *method;

    /** Selected modem */
    const Modem *modem;
};

#endif
