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

#ifndef __DIALER_H__
#define __DIALER_H__

#include <vector>

#include "Printable.h"
#include "Script.h"
#include "Log.h"

/**
 * A dialer knows which scripts a required in order to establish a
 * connection, and in which order they should be executed. It is placed
 * inside a <code>ConnectionTemplate</code> to create a final script.
 *
 * Note: Since the <code>Dialer</code> is the class that holds all the
 * <code>Script</code>s, it will release all the scripts it holds during
 * destruction.
 *
 * @author duvduv
 */
class Dialer : public Printable {
public:

    /* --- Constructors --- */

    /**
     * Constructor.
     */
    Dialer(const std::string name) : Printable() {
        this->name = name;

        Log::debug("Dialer created successfully");
    }

    /**
     * Destructor, does nothing.
     */
    virtual ~Dialer() {
        releaseScripts();

        Log::debug("Dialer released successfully");
    }

    /* --- Public Methods --- */

    /**
     * @return Name of the dialer
     */
    virtual const std::string getName() const {
        return name;
    }

    /**
     * @return An ordered list of the <code>Script</code>s that has to be
     *         executed in order to establish a new connection.
     */
    virtual std::vector<Script*> getConnectionScripts() const {
        return connectionScripts;
    }

    /**
     * @return An ordered list of the <code>Script</code>s that has to be
     *         executed in order to terminate a connection.
     */
    virtual std::vector<Script*> getDisconnectionScripts() const {
        return disconnectionScripts;
    }

    /**
     * Adds a connection script to the dialer. Scripts are ordered by the
     * order they are added.
     *
     * @param script Script to add to the dialer.
     */
    virtual void addConnectionScript(Script *script) {
        connectionScripts.push_back(script);
    }

    /**
     * Adds a disconnection script to the dialer. Scripts are ordered by the
     * order they are added.
     *
     * @param script Script to add to the dialer.
     */
    virtual void addDisconnectionScript(Script *script) {
        disconnectionScripts.push_back(script);
    }
    
    /* --- Inherited from Printable --- */

    /**
     * @return The name of the dialer.
     */
    virtual const std::string toString() const {
        return getName();
    }

private:

    /* --- Utility Methods --- */

    /**
     * This method releases (<code>delete</code>s) all the scripts that are
     * held by this dialer.
     */
    void releaseScripts();

    /**
     * This method releases (<code>delete</code>s) all the connection scripts
     * that are held by this dialer.
     */
    void releaseConnectionScripts();
    
    /**
     * This method releases (<code>delete</code>s) all the disconnection
     * scripts that are held by this dialer.
     */
    void releaseDisconnectionScripts();

    /* --- Data Members --- */

    /** Dialer's name */
    std::string name;

    /** Ordered list of connection scripts */
    std::vector<Script*> connectionScripts;

    /** Ordered list of disconnection scripts */
    std::vector<Script*> disconnectionScripts;
};

#endif
