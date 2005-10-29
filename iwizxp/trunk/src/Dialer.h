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

#include "Nameable.h"
#include "Script.h"
#include "Log.h"

/**
 * A dialer is an ordered set of scripts, that should be executed in the
 * given order to establish or terminate a connection. The dialer is
 * represented in the script as a bunch of method definitions, and two
 * methods, <code>connect</code> and <code>disconnect</code>, that call the
 * above method in the given order. This code block is placed inside the
 * <code>ConnectionTemplate</code>.
 * 
 * Note: At destruction time, the <code>Dialer</code> will
 * <code>delete</code> all the <code>Script</code>s it knows.
 *
 * @author duvduv
 * @see ConnectionTemplate
 */
class Dialer : public virtual Nameable {
public:

	/* --- Constructors --- */

	/**
	 * TODO: JavaDocs
	 */
	Dialer() : Nameable("") {
		// Left blank
	}

	/**
	 * Constructor, does nothing interesting.
	 *
	 * @param name Dialer's name
	 */
	Dialer(const std::string name) : Nameable(name) {
		this->name = name;

		Log::debug(LOG_LOCATION("Dialer", "Dialer"),
			"Constructing Dialer");
	}

	/**
	 * Destructor. Attempts to release all the <code>Script</code>s that
	 * this dialer knows.
	 */
	virtual ~Dialer() {
		releaseScripts();

		Log::debug(LOG_LOCATION("Dialer", "~Dialer"),
			"Destroying Dialer");
	}

	/* --- Public Methods --- */

	/**
	 * @return An ordered list of the <code>Script</code>s that has to be
	 *         executed in order to establish a new connection.
	 */
	virtual const std::vector<Script*> &getConnectionScripts() const {
		return connectionScripts;
	}

	/**
	 * @return An ordered list of the <code>Script</code>s that has to be
	 *         executed in order to terminate a connection.
	 */
	virtual const std::vector<Script*> &getDisconnectionScripts() const {
		return disconnectionScripts;
	}

	/**
	 * Adds a connection script to the dialer. Scripts are executed by the
	 * order they were added (FIFO).
	 *
	 * @param script Script to add to the dialer.
	 */
	virtual void addConnectionScript(Script *script) {
		connectionScripts.push_back(script);
	}

	/**
	 * Adds a disconnection script to the dialer. Scripts are executed by
	 * the order they were added (FIFO).
	 *
	 * @param script Script to add to the dialer.
	 */
	virtual void addDisconnectionScript(Script *script) {
		disconnectionScripts.push_back(script);
	}

private:

	/* --- Utility Methods --- */

	/**
	 * This method releases (<code>delete</code>s) all the scripts that are
	 * held by this dialer.
	 */
	void releaseScripts();

	/**
	 * This method releases (<code>delete</code>s) all the connection
	 * scripts that are held by this dialer.
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
