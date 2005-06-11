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

#include "SimpleFormatIspLoader.h"
#include "SimpleFormatModemLoader.h"
#include "BashSyntaxScriptLoader.h"
#include "SimpleFormatDialerLoader.h"

/**
 * This singleton class holds everything's that's global and configureable in
 * the system.
 * 
 * @author duvduv
 */
class GlobalRepository {
private:

    /* --- Private Constructors --- */

    /**
     * Private constrcutor. Creates the loaders.
     */
    GlobalRepository() {
        ispLoader = new SimpleFormatIspLoader();
        modemLoader = new SimpleFormatModemLoader();
        scriptLoader = new BashSyntaxScriptLoader();
        dialerLoader = new SimpleFormatDialerLoader();

        Log::debug("GlobalRepository created successfully");
    }

    /**
     * Destructor.
     */
    ~GlobalRepository() {
        delete dialerLoader;
        delete scriptLoader;
        delete modemLoader;
        delete ispLoader;

        Log::debug("GlobalRepository released successfully");
    }

public:

    /* --- Singleton Methods --- */

    /**
     * The singleton access method.
     *
     * @return Pointer to the single instance of <code>GlobalRepository</code>
     * in the system.
     */
    static GlobalRepository *getInstance() {
        if (instance == 0) {
            instance = new GlobalRepository();
        }
        
        return instance;
    }

    /**
     * This methos releases the global repositoy.
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
        // TODO: Load from configuration
        return "db";
    }

private:

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
};

#endif
