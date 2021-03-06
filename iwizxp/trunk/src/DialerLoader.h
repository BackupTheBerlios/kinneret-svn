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

#ifndef __DIALER_LOADER_H__
#define __DIALER_LOADER_H__

#include <istream>

#include "Dialer.h"
#include "Exception.h"

/**
 * This interface represents a class that is able to load a dialer from a
 * stream.
 *
 * @author duvduv
 */
class DialerLoader {
public:

	/* --- Constructors ---- */

	/**
	 * Constructor, does nothing.
	 */
	DialerLoader() {
		// Nothing to do
	}

	/**
	 * Destructor, does nothing.
	 */
	virtual ~DialerLoader() {
		// Nothing to do
	}

	/* --- Inner Types --- */

	/**
	 * Thrown when load fails.
	 */
	NewException(LoadException);

	/* --- Abstract Methods --- */

	/**
	 * This method allocates and initializes a new dialer from a given
	 * stream.
	 *
	 * @param inStream Stream to read dialer info from. Format determined by
	 *        the implementing loader.
	 * @return A new and allocated dialer. The dialer is allocated using
	 *         <code>new</code> and it's up to the caller to
	 *         <code>delete</code> it.
	 * @throws LoadException When a new dialer cannot be created from the
	 *         given stream.
	 */
	virtual Dialer *loadDialer(std::istream &inStream) const = 0;
};

#endif
