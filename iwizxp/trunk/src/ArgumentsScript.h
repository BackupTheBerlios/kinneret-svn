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

#ifndef __ARGUMENTS_SCRIPT_H__
#define __ARGUMENTS_SCRIPT_H__

#include <map>

#include "Script.h"

#include "Isp.h"
#include "Modem.h"
#include "ConnectionMethod.h"
#include "UserInput.h"

/**
 * This class represents the script that sets all of the user arguments. This
 * is the first script called for every action, setting all the user defined
 * variables required for the other scripts to work.
 *
 * The script defines the variables:
 * <ul>
 * <li>$defaultGateway (from <code>ConnectionMethod</code>)</li>
 * <li>$dialingDestination (from <code>ConnectionMethod</code>)</li>
 * <li>$modules (from <code>Modem</code>)</li>
 * <li>$nameservers (from <code>Isp</code>)</li>
 * <li>$searchGroups (from <code>Isp</code>)</li>
 * <li>$modemEthernetDevice (from <code>UserInput</code>)</li>
 * <li>$username (from <code>UserInput</code>)</li>
 * <li>$password (at runtime, using <code>getPasswordFromUser</code>)</li>
 * </ul>
 *
 * A note regarding the usage of this class:
 * The <code>GlobalRepository</code> holds an instrance of this class. You
 * should use this instance, and not create one of your own. This is because
 * this script may be used in more than one dialer (usually, both pre-dialer and
 * post-dialer will call this script). If we held more than one instance of
 * this class, we had to make sure the instances were synchronized with each
 * other (e.g. changes in one script should reflect in the other), and there
 * was the possibility that they both were in the final script, rendering it
 * unusuable.  Therefore, every time a script is loaded, check that it's
 * not the <code>ArgumentsScript</code>, if it is, use the one that's in
 * the <code>GlobalRepository</code>. You can look at it as some sort of a
 * Singleton.
 *
 * @author duvduv
 */
class ArgumentsScript : public Script {
public:

	/* --- Constructors --- */

	/**
	 * Default Constructor. Does nothing but printing a pretty log message.
	 */
	ArgumentsScript() {
		Log::debug(LOG_LOCATION("ArgumentsScript", "ArgumentsScript"),
			"Constructing ArgumentsScript");
	}

	/**
	 * Destructor. Does nothing but printing a pretty log message.
	 */
	virtual ~ArgumentsScript() {
		Log::debug(LOG_LOCATION("ArgumentsScript", "~ArgumentsScript"),
			"Destroying ArgumentsScript");
	}

	/* --- Public Methods --- */

	/**
	 * Initializes ISP related variables according to the given ISP.
	 *
	 * @param isp ISP to get data from.
	 */
	void setIsp(const Isp *isp);

	/**
	 * Initializes modem related variables according to the given modem.
	 *
	 * @param modem The modem that the user wishes to connect with.
	 */
	void setModem(const Modem *modem);

	/**
	 * Sets connection method related variables.
	 *
	 * @param method The connection method the script is going to use.
	 */
	void setConnectionMethod(const ConnectionMethod *method);

	/**
	 * Sets variables that comes from the user (like username etc.).
	 *
	 * @param input The user's input to use.
	 */
	void setUserInput(const UserInput *input);

	/* --- Inherited from Script --- */

	/**
	 * @return The name of the function that has to be called in order to
	 *         execute this script.
	 */
	virtual const std::string getFunctionName() const {
		return "setupUserArguments";
	}

	/**
	 * @return A valid-syntax Bash script, that sets up all the user defined
	 *         variables.
	 */
	virtual const std::string getScriptBody() const;

	/**
	 * @return Short description of the script that will be placed in a
	 *         comment above it.
	 */
	virtual const std::string getScriptDescription() const {
		return
			"This script sets all of the user arguments.\n"
			"This is the first script called for every\n"
			"connection, setting all the user defined variables\n"
			"required for the other scripts to work.";
	}

private:

	/* --- Helpers --- */

	/**
	 * This method builds a list of space seperated names that can be
	 * assigned as the values for <code>modules2_4</code> or
	 * <code>modules2_6</code>. Modules that are not supported by the
	 * requested kernel class will be left out of the list.
	 *
	 * @param modem Modem, to get the list of modules from
	 * @param kernelClass Kernel class to get the module names for
	 * @return A space-seperated list of module names. Modules that are not
	 *         supported are left out. An empty string is returned if none
	 *         is.
	 */
	std::string buildKernelClassModulesList(const Modem *modem,
		KernelModule::KernelClass kernelClass);

	/* --- Data Members --- */

	/**
	 * Names -&gt; Values map.
	 *
	 * Maps between variables name and their values.
	 */
	std::map<std::string, std::string> values;
};

#endif
