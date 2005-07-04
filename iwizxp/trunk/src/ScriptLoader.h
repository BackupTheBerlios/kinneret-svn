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
#ifndef __SCRIPT_LOADER_H___
#define __SCRIPT_LOADER_H___

#include <istream>

#include "Script.h"
#include "Exception.h"

/**
 * This interface loads a script from a stream.
 *
 * @author duvduv
 */
class ScriptLoader {
public:

    /* --- Constructors --- */

    /**
     * Constructor.
     */
    ScriptLoader() {
        // Nothing to do
    }

    /**
     * Destructor.
     */
    virtual ~ScriptLoader() {
        // Nothing to do
    }

    /* --- Excpetions --- */

    /**
     * Thrown when the loader wasn't able to load the script from the stream.
     */
    NewException(LoadException);

    /* ---- Abstract Methods --- */

    /**
     * This function loads a script from a stream.
     *
     * @param inStream Stream to load script from.
     * @return A new and initialized <code>Script</code>. Note that the
     *        <code>Script</code> is allocated using <code>new</code>, and
     *        its up to the user to <code>delete</code> it.
     * @throw LoadException When the given stream is in the wrong format or
     *        any other problem occured during the loads process.
     */
    virtual Script *loadScript(std::istream &inStream) const = 0;
};

#endif
