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

#ifndef __PSUDO_ETHERNET_USB_CABLES_MODEM_H__
#define __PSUDO_ETHERNET_USB_CABLES_MODEM_H__

#include "Modem.h"
#include "PsudoEthernetUsbModule.h"

/**
 * This class represents a cables modem that's connected to the computer
 * using the USB interface. These sort of modems are usually treated with
 * loading a module wich provides a psudo-ethernet interface that represents
 * the connection to the modem.
 *
 * TODO: Refactor-rename: PsudoEthernetUsbCablesPPtPModem
 *
 * @author duvduv.
 */
class PsudoEthernetUsbCablesModem : public Modem {
public:

    /* --- Constructors --- */

    /**
     * Constructor. Initializes the list of modules required by this modem.
     *
     * @param name Modem's name.
     */
    PsudoEthernetUsbCablesModem(std::string name) : Modem(name) {
        // Released by ~Modem()
        addModule(new PsudoEthernetUsbModule());
    }

    /**
     * Destructor.
     */
    virtual ~PsudoEthernetUsbCablesModem() {
        // Nothing to do.
    }

    /* --- Inherited from Modem --- */

    /**
     * This modem requires some modules.
     */
    bool needModules() const {
        return true;
    }

    /**
     * @return The appropriate dialer.
     */
    const Dialer *getDialer(Isp *isp) const {
        // TODO
    }
};

#endif
