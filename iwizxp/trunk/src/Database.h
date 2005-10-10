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

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "Isp.h"
#include "Modem.h"
#include "ConnectionTemplate.h"
#include "Log.h"
#include "Exception.h"
#include "Utils.h"

/**
 * TODO: Refactor extract class IspDatabase, ModemDatabase etc?
 *
 * This class represents the databse.
 *
 * The DB is the dude that handles and manages all the things you might find
 * in the DB (ISPs, modems, connection templates).
 *
 * The difference between the database and the global repository is that the
 * global repository holds things that are configuration constants, while the
 * database manages configuration-independent data (well, except from the
 * loaders).
 *
 * It is a singleton class that loads everything at construction time. It
 * uses the <code>GlobalRepository</code> to load the actual files - Which
 * means the database format is configureable (assuming one day we'll want an
 * SQL DB or something else).
 *
 * @author duvduv
 */
class Database {
private:

    /* --- Private Constructors --- */

    /**
     * Private constructor, initializes the database and loads every
     * available ISP and modem. This method allocates a few objects (namely
     * some <code>Isp</code>s and <code>Modem</code>s).
     *
     * These object will be released at destruction time, so you don't have
     * to release them by yourself.
     *
     * The constructor attempt to load every available XML file that's in the
     * appropriate directory. If a file is of incorrect format, it is
     * skipped. Database creation is announced if we couldn't load a single
     * instance of a certain class (e.g. There were not modems or ISPs).
     *
     * @throws DatabaseCreationException When the database could not be
     *         created (usually due to the lack of appropriate files and
     *         incorrect format of files).
     */
    Database();

    /**
     * Destructor. Releases all the <code>Isp</code>s and <code>Modem</code>s
     * that we allocated during construction.
     */
    virtual ~Database();

public:

    /* --- Singleton --- */

    /**
     * The singleton access method.
     *
     * @return Pointer to the single instance of this class.
     */
    static Database *getInstance() {
        if (instance == 0) {
            instance = new Database();
        }
        
        return instance;
    }

    /**
     * This method releases the database. Call it once you're done. It should
     * start the chain of releases of the stuff we loaded in the constructor.
     */
    static void release() {
        delete instance;
    }

    /* --- Public Methods --- */
    
    /**
     * @return List of all of the available ISPs.
     */
    const std::vector<Isp*> &getIsps() const {
        return isps;
    }

    /**
     * @return List of all the available modems.
     */
    const std::vector<Modem*> &getModems() const {
        return modems;
    }

    /**
     * @return List of all available connection templates.
     */
    const std::vector<ConnectionTemplate*> &getConnectionTemplates() const {
        return connectionTemplates;
    }

    /**
     * The default pre dialer is a regular dialer, with the exception that it
     * doesn't dial anywhere. It is a meta-dialer, common to all the dialers
     * we're about to create with this wizard, which defines some scripts
     * that should be ran before and after the actual connection or
     * disconnection code.
     *
     * The purpose of this dialer is to prepare the enviroment for the
     * connection code, usually setting some variables the scripts relies on,
     * and setting system data like ppp sercers.
     *
     * The pre-dialer holds a list of scripts that should be ran before
     * <i>every</i> connection or disconnection.
     * 
     * @return The default pre-dialer
     */
    Dialer *getDefaultPreDialer() {
        return defaultPreDialer;
    }

    /**
     * The post-dialer is similar to the pre-dialer, except it is executed
     * after the connection or disconnection code.
     * 
     * @return The default post-dialer
     * @see #getDefaultPreDialer
     */
    Dialer *getDefaultPostDialer() {
        return defaultPostDialer;
    }

    /* --- Exceptions --- */

    /**
     * Indicates that the database could be created.
     */
    NewException(DatabaseCreationException);

private:

    /* --- Utility Methods --- */

    /**
     * This utility method enumerates ISPs and return a list of files.
     * The method enumerated all the files in the <code>isp</code> directory
     * under the base database path, and fills a list with full path names.
     *
     * @return List of paths to all the files under the <code>isp</code>
     *         directory.
     * @throws DirectoryEnumerationException When the directory could not be
     *        enumerated.
     */
    std::vector<std::string> enumIsps() const;

    /**
     * This utility method loads an ISP from a file using the
     * <code>IspLoader</code> that's in the <code>GlobalRepository</code>.
     *
     * @param file Path (full or relative) to a valid ISP file.
     * @return Whether the ISP loaded successfully (<code>true</code> is
     *         success).
     */
    bool loadIspFromFile(std::string file);

    /**
     * This utility method enumerates all the files that's in the directory
     * <code>modem</code> directly under the databases' root path. It then
     * creates a list of all the full paths to the files.
     *
     * @return List of every file under <code>modem</code>.
     * @throws DirectoryEnumerationException When the directory could not be
     *        enumerated.
     * @see #enumIsps
     */
    std::vector<std::string> enumModems() const;

    /**
     * This utility method loads a modem from a file using the
     * <code>ModemLoader</code> that's inside the
     * <code>GlobalRepository</code>, and adds it to the database.
     *
     * @param file Path (relative or full) to a valid modem file.
     * @return Whether the loads succeeded, or not (<code>true</code> is
     *         success).
     * @see #loadIspFromFile
     */
    bool loadModemFromFile(std::string file);

    /**
     * This private method attempts to load every file that
     * <code>enumModems()</code> enumerated using
     * <code>loadModemFromFile()</code>. In case a load failes (due to
     * incorrect format, invalid path, whatever) the method skips the modem
     * and continues on. In case there were no successful loads, the method
     * notifies the caller with a <code>DatabaseCreationException</code>.
     *
     * @throws DatabaseCreationException Thrown when the loader wasn't able
     *         to load any modem successfully.
     * @see enumModems, loadModemFromFile
     */
    void loadModems();

    /**
     * This private method attempts to load every file that
     * <code>enumIsps()</code> enumerated using <code>loadIspFromFile()</code>.
     * In case a load failes (due to incorrect format, invalid path,
     * whatever) the method skips the isp and continues on. In case there
     * were no successful loads, the method notifies the caller with a
     * <code>DatabaseCreationException</code>.
     *
     * @throws DatabaseCreationException Thrown when the loader wasn't able
     *         to load any isp successfully.
     * @see enumIsps, loadIspFromFile
     */
    void loadIsps();

    /**
     * TODO: JavaDocs
     */
    std::vector<std::string> enumConnectionTemplates() const;

    /**
     * TODO: JavaDocs
     */
    bool loadConnectionTemplateFromFile(const std::string &file);

    /**
     * TODO: JavaDocs
     */
    void loadConnectionTemplates();

    /**
     * The method releases every ISP allocated using <code>loadIsps()</code>.
     */
    void releaseIsps();

    /**
     * The method releases every modem allocated using
     * <code>loadModems()</code>.
     */
    void releaseModems();

    /**
     * TODO: JavaDocs
     */
    void releaseConnectionTemplates();

    /**
     * Loads the default dialers.
     *
     * @throws DatabaseCreationException Thrown when the default diealers
     *        (pre and post) could not be loaded.
     * @see #getDefaultPreDialer
     */
    void loadDefaultDialers();

    /**
     * Releases the default dialers.
     *
     * @see #getDefaultPreDialer
     */
    void releaseDefaultDialers();

    /* --- Data Members --- */

    /** Singleton instance */
    static Database *instance;

    /** All the available ISPs */
    std::vector<Isp*> isps;

    /** All the available modems */
    std::vector<Modem*> modems;

    /** All the available connection templates */
    std::vector<ConnectionTemplate*> connectionTemplates;

    /** The default pre-dialer */
    Dialer *defaultPreDialer;

    /** The default post-dialer */
    Dialer *defaultPostDialer;
};

#endif
