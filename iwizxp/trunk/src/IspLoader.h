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

#ifndef __ISP_LOADER_H__
#define __ISP_LOADER_H__

#include <istream>

#include "Isp.h"
#include "Exception.h"

/**
 * This interface can load an ISP from a stream.
 *
 * @author duvduv
 */
class IspLoader {
public:

	/* --- Constructors --- */

	/**
	 * Constructor.
	 */
	IspLoader() {
		// Nothing to do
	}

	/**
	 * Desctructor.
	 */
	virtual ~IspLoader() {
		// Nothing to do
	}

	/* --- Exceptions --- */

	/**
	 * Thrown when the loader wasn't able to load the ISP.
	 */
	NewException(LoadException);

	/* --- Abstract Methods --- */

	/**
	 * Pure-virtual method which allocates and initializes a new ISP from a
	 * given stream. Note that the ISP is allocated with <code>new</code>,
	 * and it's up to the user to <code>delete</code> it.
	 *
	 * @param inStream Stream to read ISP's info from.
	 * @return A new and initialized <code>Isp</code> (or one of its
	 *         subclasses).
	 * @throws LoadException When the loades could not have initialized a
	 *         new ISP from the given stream (serialization error, stream
	 *         error, memory error, etc.)
	 */
	virtual Isp *loadIsp(std::istream &inStream) const = 0;
};

#endif
