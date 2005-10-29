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

#ifndef __USER_INPUT_H__
#define __USER_INPUT_H__

#include <string>

/**
 * The "user input" is the part of the user arguments that cannot be obtained
 * in any other way except asking the user directly (thigs like username, and
 * all sort of preferences).
 *
 * @author: duvduv
 */
class UserInput {
public:

	/* --- Constructors ---- */

	/**
	 * Constructor.
	 *
	 * Sets autodetection of ethernet interfaces to false.
	 */
	UserInput() {
		autodetectInterface = false;
	}

	/**
	 * Destructor. Does nothing interesting.
	 */
	virtual ~UserInput() {
		// Nothing to do
	}

	/* --- Public Methods --- */

	/**
	 * @return Username
	 */
	virtual std::string getUsername() const {
		return username;
	}

	/**
	 * The ethernet device is the device (virtual or real) we use to
	 * establich the connection with the ISP.
	 * 
	 * @return <code>true</code>, if the user specified a device.
	 *         <code>false</code> otherwise.
	 */
	virtual bool hasEthernetDevice() const {
		return modemEthernetDevice.length() > 0;
	}

	/**
	 * The modem device is the device (virtual or real) we use to establish
	 * connection with the ISP. Usually, it is an ethernet device of the
	 * form eth<i>n</i> - where <i>n</i> is the interface index.
	 * 
	 * @return Name of the modem device (e.g. <code>eth0, eth1</code> etc.)
	 */
	virtual std::string getModemEthernetDevice() const {
		return modemEthernetDevice;
	}

	/**
	 * Interface autodetection attempt auto-detection of the interface that
	 * <code>modprobe</code> created.  Since the device might be different
	 * at some times (like, when installing a new ethernet card), this
	 * feature might be useful for USB modems.
	 * 
	 * @return <code>true</code>, if the user wishes that final script will
	 *         attempt to auto-detect the ethernet device (usually created
	 *         using <code>usbnet</code> and modules of this sort).
	 *         <code>false</code> otherwise.
	 */
	virtual bool useInterfaceAutodetection() const {
		return autodetectInterface;
	}

	/**
	 * Sets the username.
	 * 
	 * @param username Username
	 */
	virtual void setUsername(const std::string username) {
		this->username = username;
	}

	/**
	 * Sets the modem device.
	 *
	 * @param device Device's string.
	 */ 
	virtual void setModemEthernetDevice(const std::string device) {
		this->modemEthernetDevice = device;
	}

	/**
	 * @param autodetect Whether to auto-detect or not.
	 *
	 * TODO: Prevent the case where auto-detection is disabled and there's
	 * no default device.
	 */ 
	virtual void setInterfaceAutodetection(bool autodetect) {
		autodetectInterface = autodetect;
	}

private:

	/* --- Data Members --- */

	/** Username */
	std::string username;

	/** Device (e.g eth0, eth1, etc.) */
	std::string modemEthernetDevice;

	/**
	 * Should we attempt newtork interface auto-detection? No, by default.
	 */
	bool autodetectInterface;
};

#endif
