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

#include <fstream>

#include "PsudoEthernetUsbCablesModem.h"
#include "GlobalRepository.h"

using namespace std;

Dialer *PsudoEthernetUsbCablesModem::createDialer() const
        throw (DialerCreationException) {
    try {
        // Get path to dialer
        // TODO: From configuration:
        // <modem>
        // ...
        //     <dialer>
        //         <default>some_dialer</default>
        //         <exception isp="someIsp">other_dialer</exception>
        //     </dialer>
        // </modem>
        string path(GlobalRepository::getInstance()->
            getDbBasePath() + "/dialer/pptp_cables_dialer");

        Log::debug(string("Loading ") + path + "...");

        ifstream dialer(path.c_str());
        if (!dialer.is_open()) {
            throw DialerCreationException("Unable to open dialer file!");
        }

        // Load dialer
        Dialer *result = GlobalRepository::getInstance()->getDialerLoader()->
            loadDialer(dialer);

        // Close file
        dialer.close();

        return result;
    } catch (DialerLoader::LoadException &ex) {
        throw DialerCreationException(string("Unable to load dialer: ") +
            ex.what());
    }
}

