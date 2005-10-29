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

#ifndef __WIZARD_H__
#define __WIZARD_H__

#include "WizardListener.h"

/**
 * The wizard is the class that puts it all together. It's the main manager,
 * deciding which information it needs when, the class that does it all.
 *
 * You never touch it. You register as a listener to it (by implementing
 * <code>WizardListener</code>) and supply it with information when it
 * requests you.
 * 
 * @author duvduv
 */
class Wizard {
public:

	/* --- Constructors ---- */

	/**
	 * Constructor.
	 */
	Wizard() {
		listener = 0;
	}

	/**
	 * Destructor.
	 */
	virtual ~Wizard() {
		// Nothing to do
	}

	/* --- Public Methods --- */

	/**
	 * Starts the wizard. After calling this method, several events will be
	 * fired from the wizard to its listener.
	 *
	 * @return 0 on success, non-zero otherwize.
	 */
	int go();

	/**
	 * Sets the listener to this wizard.
	 *
	 * @param listener The listener
	 */
	void setListener(WizardListener *listener) {
		this->listener = listener;
	}

private:

	/* --- Utilities --- */

	/**
	 * This method translates the <code>Printable</code>s in the list to
	 * strings, and fires an event to the listener, requesting him to choose
	 * one.
	 *
	 * This is basically a helper method which allows direct selection over
	 * an objects array, rathar than translating to strings and figuring out
	 * which object the user chose.
	 *
	 * @param what The prompt that will be displayed to the user, specifing
	 *        what his selection affects.
	 * @param list List of items to choose from. Container should contain
	 *        <code>Printable</code>s - every non-<code>Printable</code>
	 *        object in it will be displayed to the user as
	 *        <code>"null"</code>.
	 * @return The selected object
	 */
	template<class T> T selectFromList(
		std::string what, std::vector<T> list);

	/**
	 * Safely selects an element from a list. By "safely" we mean that we
	 * can't trust the listener to supply us with a valid index when firing
	 * a <code>selectFromList</code> request. This method makes sure the
	 * value that returned from the listener is valid. If it's not, the user
	 * is notified about his bad selection, and the question is re-asked.
	 *
	 * @param what The prompt
	 * @param list List of choises
	 * @return The index of the selected choise, known to be valid.
	 */
	int safeSelectFromList(std::string what, std::vector<std::string> list);

	/* --- Data Members --- */

	/** The listener that supplies us with all the data we request */
	WizardListener *listener;
};

#endif
