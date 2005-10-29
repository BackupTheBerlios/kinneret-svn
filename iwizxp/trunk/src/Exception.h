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

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>
#include <exception>

/**
 * A Macro for creating new exceptions.
 * 
 * All the exceptions inherit from Exception, which inherits from
 * std::exception.
 */
#define NewException(name) \
class name : public Exception { \
public: \
	name(const std::string &what) throw () : Exception(what) { \
	} \
\
	name() throw () : Exception() { \
	} \
\
	virtual ~name() throw () { \
	} \
};

/**
 * Generic excpetion.
 *
 * @author duvduv
 */
class Exception : public std::exception {
public:

	/* --- Constructors --- */

	/**
	 * Constructor. Sets the reason for this exception.
	 *
	 * @param what The reason for the exception.
	 */
	Exception(const std::string &what) throw () : exception() {
		reason = what;
	}

	/**
	 * Empty constructor. Constructs an excpetion with an unknown reason.
	 */
	Exception() throw () : exception() {
		reason = std::string("Unknown reason");
	}

	/**
	 * Destructor, does nothing.
	 */
	virtual ~Exception() throw () {
		// Nothing to do
	}

	/* --- Public Methods --- */

	/**
	 * @return Reson for the exception
	 */
	virtual const char *what() const throw() {
		return reason.c_str();
	}

private:

	/* --- Data Members --- */

	/** The reason this exception was thrown */
	std::string reason;
};

// Some useful exceptions
NewException(IOException)

#endif
