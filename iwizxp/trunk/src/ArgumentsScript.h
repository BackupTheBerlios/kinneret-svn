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

#include <map>

#include "Script.h"

#include "Isp.h"
#include "Modem.h"
#include "ConnectionMethod.h"
#include "UserInput.h"

/**
 * TODO: Explain singleton
 *
 * This class represents the script that sets all of the user arguments. This
 * is the first script called for every connection, setting all the user
 * defined variables required for the other scripts to work.
 *
 * The script defines the variables:
 * <ul>
 * <li>$defaultGateway (from <code>ConnectionMethod</code>)</li>
 * <li>$dialingDestination (from <code>ConnectionMethod</code>)</li>
 * <li>$modules (from <code>Modem</code>)</li>
 * <li>$nameservers (from <code>Isp</code>)</li>
 * <li>$searchGroups (from <code>Isp</code>)</li>
 * <li>$modemEthernetDevice (from <code>UserInput</code>)</li>
 * <li>$username (from <code>UserInput</code>)</li>
 * <li>$password (at runtime, using <code>getPasswordFromUser</code>)</li>
 * </ul>
 *
 * @author duvduv
 */
class ArgumentsScript : public Script {
private:

    /* --- Constructors --- */

    /**
     * Constructor. Does nothing.
     */
    ArgumentsScript() : Script() {
        Log::debug("ArgumentsScript created successfully");
    }

    /**
     * Destructor, does nothing.
     */
    virtual ~ArgumentsScript() {
        instance = 0;
        Log::debug("ArgumentsScript released successfully");
    }

public:

    /* --- Singleton --- */

    /**
     * Singeton access point.
     *
     * @return A pointer to the single instance of
     *         <code>ArgumentsScript</code> in the system.
     */
    static ArgumentsScript *getInstance() {
        if (instance == 0) {
            instance = new ArgumentsScript();
        }

        return instance;
    }

    /**
     * Releases the instance. Call this when you don't need this script
     * anymore.
     */
    static void release() {
        if (instance != 0) {
            delete instance;
        }
    }

    /* --- Public Methods --- */

    /**
     * Initializes ISP related variables according to the given ISP.
     *
     * @param isp ISP to get data from.
     */
    void setIsp(const Isp *isp);

    /**
     * Initializes modem related variables according to the given modem and
     * kernel class.
     *
     * This is where the actual translation from the
     * <code>KernelModule</code> class to actual module name takes place.
     *
     * @param modem The modem that the user wishes to connect with.
     * @param kernelClass The target kernel this script is going to run on.
     */
    void setModem(const Modem *modem);

    /**
     * Sets connection method related variables.
     *
     * @param method The connection method the script is going to use.
     */
    void setConnectionMethod(const ConnectionMethod *method);

    /**
     * Sets variables that comes from the user (like username etc.).
     *
     * @param input The user's input to use.
     */
    void setUserInput(const UserInput *input);

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
    virtual const std::string getScriptBody() const;

    /**
     * @return Short description of the script that will be placed in a
     *         comment above it.
     */
    virtual const std::string getScriptDescription() const {
        return
            "This script sets all of the user arguments.\n"
            "This is the first script called for every connection,\n"
            "setting all the user defined variables required for the other\n"
            "scripts to work.";
    }

private:

    /* --- Helpers --- */

    /**
     * TODO: JavaDocs
     */
    std::string buildKernelClassModulesList(const Modem *modem,
        KernelModule::KernelClass kernelClass);

    /* --- Data Members --- */

    /** Names -&gt; Values map */
    std::map<std::string, std::string> values;

    /* --- Singleton --- */

    /** The instance */
    static ArgumentsScript *instance;
};

#endif
