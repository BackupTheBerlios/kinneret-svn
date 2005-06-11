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

#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include "Printable.h"

/**
 * <code>Script</code>s are the building blocks of the <code>Dialer</code>.
 * Scripts are small, usually generic, pieces of code, that are combined
 * together to create a complete dialer. Scripts are translated to Bash
 * functions in the final script, which are called in order by the dialer.
 *
 * TODO: DnsScript, PppSecretsScript.
 * 
 * @author duvduv.
 */
class Script {
public:

    /* --- Constructors --- */

    /**
     * Constructor.
     */
    Script() {
        // Nothing to do
    }

    /**
     * Destructor.
     */
    virtual ~Script() {
        // Nothing to do.
    }

    /* --- Abstract Methods --- */

    /**
     * @return The function's name. Every script's body is places inside a
     *         unique function.
     */
    virtual const std::string getFunctionName() const = 0;

    /**
     * @return The function's body (What's inside the function).
     */
    virtual const std::string getScriptBody() const = 0;

    /**
     * @return Short description of the script that will be placed in a
     *         comment above it.
     */
    virtual const std::string getScriptDescription() const = 0;
};

#endif
