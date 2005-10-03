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

#ifndef __GLOBAL_REPOSITORY_H__
#define __GLOBAL_REPOSITORY_H__

#include <xercesc/dom/DOMBuilder.hpp>

#include "IspLoader.h"
#include "ModemLoader.h"
#include "ScriptLoader.h"
#include "DialerLoader.h"
#include "ArgumentsScript.h"

/**
 * The global repository is a singleton repository, that holds configuration
 * variables, and system-shared object.
 *
 * It differs from <code>Database</code> by that fact that it doesn't hold
 * anything concrete, except configuration variables.
 *
 * Things in the global repository never change at runtime.
 * 
 * @author duvduv
 */
class GlobalRepository {
private:

    /* --- Private Constructors --- */

    /**
     * Private constrcutor. Creates the loaders and sets up Xerces.
     */
    GlobalRepository() {
        Log::debug("Constructing GlobalRepository");
        setupLoaders();
        setupXerces();
    }

    /**
     * Destructor, deletes the loaders and releases Xerces.
     */
    ~GlobalRepository() {
        Log::debug("Destroying GlobalRepository");
        releaseXerces();
        releaseLoaders();
    }

public:

    /* --- Singleton Methods --- */

    /**
     * The singleton access method.
     *
     * @return Pointer to the single instance of <code>GlobalRepository</code>
     *         in the system.
     */
    static GlobalRepository *getInstance() {
        if (instance == 0) {
            instance = new GlobalRepository();
        }
        
        return instance;
    }

    /**
     * Releases the instance.
     */
    static void release() {
        if (instance != 0) {
            delete instance;
            instance = 0;
        }
    }

    /* --- Public Methods --- */

    /**
     * @return The ISP loader we should use with the current database.
     */
    IspLoader *getIspLoader() {
        return ispLoader;
    }

    /**
     * @return The modem loader we should use with the current database.
     */
    ModemLoader *getModemLoader() {
        return modemLoader;
    }

    /**
     * @return The script loader we shoulde use with the current database.
     */
    ScriptLoader *getScriptLoader() {
        return scriptLoader;
    }

    /**
     * @return The dialer loader we should use with the current database
     */
    DialerLoader *getDialerLoader() {
        return dialerLoader;
    }

    /**
     * @return The full path to the top directory of the current database.
     */
    std::string getDbBasePath() {
        // TODO: From configuration
        return "db";
    }

    /**
     * @return Name of default pre-dialer dialer. The pre-dialer dialer is a
     *         regular dialer, except that it doesn't connect to anywhere.
     *         It's simply there to setup defaults in the script (like
     *         calling the user arguments method and setting up default
     *         variables).
     */
    std::string getDefaultPreDialerName() {
        // TODO: From configuration
        return "pre";
    }

    /**
     * @return Name of default post-dialer dialer. The post-dialer dialer is a
     *         regular dialer, except that it doesn't disconnect anything.
     *         It's simply there to undo what's been done in the pre-dialer
     *         (like restoring /etc/resolv.conf).
     */
    std::string getDefaultPostDialerName() {
        // TODO: From configuration
        return "post";
    }

    /**
     * @return An initialized and ready to use <code>DOMBuilder</code>.
     */
    xercesc::DOMBuilder *getDOMBuilder() {
        return domBuilder;
    }

    /**
     * @return The global arguments script.
     * @see ArgumentsScript
     */
    ArgumentsScript *getArgumentsScript() {
        return argumentsScript;
    }

private:

    /* --- Utilities --- */

    /**
     * Instantiates the correct loaders that match the database.
     */
    void setupLoaders();

    /**
     * Releases all the loaders that were instantiated at
     * <code>setupLoaders</code>
     *
     * @see #setupLoaders
     */
    void releaseLoaders();

    /**
     * Initializes Xerces-C and creates the <code>DOMBuilder</code> returned
     * by <code>getDOMBuilder</code>.
     *
     * The <code>DOMBuilder</code> is set to ignore comment elements, and not
     * present them in the final tree.
     */
    void setupXerces();

    /**
     * Releases Xerces-C.
     */
    void releaseXerces();

    /* --- Data Members --- */

    /** Singleton instance */
    static GlobalRepository *instance;

    /** ISP loader */
    IspLoader *ispLoader;

    /** Modem loader */
    ModemLoader *modemLoader;

    /** Script loader */
    ScriptLoader *scriptLoader;

    /** Dialer Loader */
    DialerLoader *dialerLoader;

    /** Xerces' DOM Parser */
    xercesc::DOMBuilder *domBuilder;

    /** The arguments script of the system */
    ArgumentsScript *argumentsScript;
};

#endif
