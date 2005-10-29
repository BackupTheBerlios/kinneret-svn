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

#ifndef __WIZARD_LISTENER_H__
#define __WIZARD_LISTENER_H__

#include <string>
#include <vector>

/**
 * This interface should be implemented by the UI. Once the
 * <code>Wizard</code> starts, methods of this interface will be called by
 * it, to get information from the user.
 *
 * @author duvduv
 */
class WizardListener {
public:

	/* --- Constructors ---- */

	/**
	 * Constructor.
	 */
	WizardListener() {
		// Nothing to do
	}

	/**
	 * Destructor.
	 */
	virtual ~WizardListener() {
		// Nothing to do
	}

	/* --- Public Methods --- */

	/**
	 * Called when there was a fatal error in the <code>Wizard</code> and it
	 * is about to shut down.
	 *
	 * @param what What happened.
	 */
	virtual void fatal(std::string what) = 0;

	/**
	 * Fired from the <code>Wizard</code> when the user has to select an
	 * option from a list.
	 *
	 * @param what The prompt, explaining to the user what his selection
	 *        affects.
	 * @param choises List of strings, naming the choises the user has.
	 * @return The index of the selected choise (zero-based).
	 */
	virtual int selectFromList(std::string what,
			std::vector<std::string> choises) = 0;

	/**
	 * Fired by the <code>Wizard</code> when a string input is required
	 * (like when requesting a username).
	 *
	 * @param what The prompt, specifing what is to be entered.
	 * @return The string the user entered.
	 */
	virtual std::string requestString(std::string what) = 0;

	/**
	 * Fired by the <code>Wizard</code> when a certain notification is to be
	 * displayed to the user (like bad input, specifing what is to be
	 * entered).
	 *
	 * @param what The message to display to the user.
	 */
	virtual void notify(std::string what) = 0;
};

#endif
