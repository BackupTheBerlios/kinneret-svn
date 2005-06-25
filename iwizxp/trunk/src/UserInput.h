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
 * TODO: JavaDocs
 *
 * @author: duvduv
 */
class UserInput {
public:

    /* --- Constructors ---- */

    /**
     * Constructor.
     * TODO: JavaDocs
     */
    UserInput() {
        // Nothing to do
    }

    /**
     * Destructor.
     * TODO: JavaDocs
     */
    virtual ~UserInput() {
        // Nothing to do
    }

    /* --- Public Methods --- */

    /**
     * TODO: JavaDocs
     */
    virtual std::string getUsername() const {
        return username;
    }

    /**
     * TODO: JavaDocs
     */
    virtual bool hasEthernetDevice() const {
        return modemEthernetDevice.size() > 0;
    }

    /**
     * TODO: JavaDocs
     */
    virtual std::string getModemEthernetDevice() const {
        return modemEthernetDevice;
    }

    /**
     * TODO: JavaDocs
     */
    virtual void setUsername(const std::string username) {
        this->username = username;
    }

    /**
     * TODO: JavaDocs
     */ 
    virtual void setModemEthernetDevice(const std::string device) {
        this->modemEthernetDevice = device;
    }

private:

    /* --- Data Members --- */

    /** Username */
    std::string username;

    /** Device (e.g eth0, eth1, etc.) */
    std::string modemEthernetDevice;
};

#endif
