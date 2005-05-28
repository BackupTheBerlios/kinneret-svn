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
#include "IspLoader.h"
#include "Modem.h"
#include "SimpleFormatIspLoader.h"
#include "SimpleFormatModemLoader.h"
#include "Log.h"
#include "Exception.h"

/**
 * This class represents the databse. It is a singleton class that loads
 * everything at construction time. It uses the <code>GlobalRepository</code>
 * to load the actual files.
 *
 * @author duvduv
 */
class Database {
private:

    /* --- Private Constructors --- */

    /**
     * Private constructor, initializes the database and loads every
     * available ISP and modem. This method allocates a few objects (namely
     * some <code>Isp</code>s and <code>Modem</code>s. They are released at
     * destruction time, so you don't have to release them for yourself.
     *
     * @throws DatabaseCreationException When the database could not be
     *         created successfully (usually due to the lack of appropriate
     *         files and incorrect format of files).
     */
    Database();

    /**
     * Destructor. Releases all of the allocated <code>Isp</code>s and
     * <code>Modem</code>s allocated at construction time.
     */
    virtual ~Database();

public:

    /* --- Singleton --- */

    /**
     * The singleton access method.
     *
     * @return Reference to the single instance of this class.
     */
    static Database *getInstance() {
        static Database instance;
        return &instance;
    }

    /* --- Public Methods --- */
    
    /**
     * @return List of all of the available ISPs.
     */
    std::vector<Isp*> getIsps() const {
        return isps;
    }

    /**
     * @return List of all the available modems.
     */
    std::vector<Modem*> getModems() const {
        return modems;
    }

    /* --- Exceptions --- */

    /**
     * Indicates that the database could not have been created successfully.
     */
    NewException(DatabaseCreationException);

private:

    /* --- Inner Types --- */

    /**
     * Indicates that an enumeration attempt of a directory has failed.
     */
    NewException(DirectoryEnumerationException);

    /**
     * TODO: Refactor this method out to a utility class.
     *
     * Enumerates the files that's in a specific directory, and returns a
     * vector of full paths.
     *
     * @param directory Path (absolute or relative) to the directory we wish
     *                  to enumerate.
     * @return A vector of strings full of all the files (not including '.',
     *         '..' and hidden files) in <code>directory</code>.
     * @throws DirectoryEnumerationException Thrown when the given directory
     *         could not be enumerated. The exception contains in
     *         <code>what()</code> the reason.
     */
    std::vector<std::string> enumDirectory(std::string directory) const
        throw (DirectoryEnumerationException);

    /**
     * This private method enumerates and attempts to load every file that's
     * under the modems directory in the database.
     */
    void loadModems();

    /**
     * This private method enumerates and attempts to load every file that's
     * under the ISPs directory in the database.
     */
    void loadIsps();

    /**
     * The method releases every ISP allocated in <code>loadIsps()</code>.
     */
    void releaseIsps();

    /**
     * The method releases every modem allocated in
     * <code>loadModems()</code>.
     */
    void releaseModems();

    /* --- Data Members --- */

    /** All the available ISPs */
    std::vector<Isp*> isps;

    /** All the available modems */
    std::vector<Modem*> modems;
};

#endif
