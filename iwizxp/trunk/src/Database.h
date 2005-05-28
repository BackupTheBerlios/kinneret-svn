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
 * TODO
 */
class Database {
private:

    /* --- Private Constructors --- */

    /**
     * TODO
     */
    Database();

    /**
     * TODO
     */
    virtual ~Database();

public:

    /* --- Singleton --- */

    /**
     * TODO
     */
    static Database *getInstance() {
        static Database instance;
        return &instance;
    }

    /* --- Public Methods --- */
    
    /**
     * TODO
     */
    std::vector<Isp*> getIsps() const {
        return isps;
    }

    /**
     * TODO
     */
    std::vector<Modem*> getModems() const {
        return modems;
    }

    /* --- Exceptions --- */

    NewException(DatabaseCreationException);

private:

    /* --- Inner Types --- */

    NewException(DirectoryEnumerationException);

    /**
     * Enumerates the files that's in a specific directory, and returns a
     * vector of full paths.
     *
     * @param directory Path (absolute or relative) to the directory we wish
     *                  to enumerate.
     * @param file Vector to fill. <b>NOTE</b>: The vector will be truncated!
     *             After the method finished this vector will be full of all
     *             the files that was in the given directory.
     */
    void enumDirectory(std::string directory,
                       std::vector<std::string> &files) const
        throw (DirectoryEnumerationException);

    /**
     * TODO
     */
    void loadModems();

    /**
     * TODO
     */
    void loadIsps();

    /**
     * TODO
     */
    void releaseIsps();

    /**
     * TODO
     */
    void releaseModems();

    /* --- Data Members --- */

    /** TODO */
    std::vector<Isp*> isps;

    /** TODO */
    std::vector<Modem*> modems;
};

#endif
