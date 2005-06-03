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

#ifndef __SIMPLE_FORMAT_MODEM_LOADER_H__
#define __SIMPLE_FORMAT_MODEM_LOADER_H__

#include <istream>

#include "ModemLoader.h"
#include "Exception.h"
#include "PsudoEthernetUsbCablesModem.h"

#define MAX_LINE 1024

/**
 * Test class. Do not use in production code.
 */
class SimpleFormatModemLoader : public ModemLoader {
public:

    /* --- Constructors --- */

    SimpleFormatModemLoader() : ModemLoader() {
    }
    
    virtual ~SimpleFormatModemLoader() {
    }

    /* --- Abstract Methods --- */

    virtual Modem *loadModem(std::istream &inStream) const
            throw (LoadExcpetion) {
        Modem *result = 0;

        // Load name
        char name[MAX_LINE];
        inStream.getline(name, MAX_LINE, '\n');

        // Load class
        char modemClass[MAX_LINE];
        inStream.getline(modemClass, MAX_LINE, '\n');

        std::string mc(modemClass);
        if (mc == "PsudoEthernetUsbCablesModem") {
            result = new PsudoEthernetUsbCablesModem(std::string(name));
        } else {
            throw LoadExcpetion(std::string("Unknown modem: ") + name);
        }

        return result;
    }
};

#endif
