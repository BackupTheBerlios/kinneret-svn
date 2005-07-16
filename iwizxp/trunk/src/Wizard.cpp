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

#include "Wizard.h"

#include "Printable.h"
#include "Isp.h"
#include "GlobalRepository.h"
#include "Database.h"
#include "ArgumentsScript.h"
#include "ConnectionMethod.h"
#include "ConnectionTemplate.h"
#include "UserInput.h"

using namespace std;

template<class T> T Wizard::selectFromList(vector<T> list, string what) {
    vector<string> toListener;
    int selection;

    typename vector<T>::iterator iter;
    for (iter = list.begin() ; iter != list.end() ; iter++) {
        string itemString;
        Printable *printable = dynamic_cast<Printable*>(*iter);
        if (printable != 0) {
            itemString = printable->toString();
        } else {  
            itemString = "null";
        }

        toListener.push_back(itemString);
    }

    selection = listener->selectFromList(what, toListener);
    return list[selection];
}

int Wizard::go() {
    try {
        Isp *isp = selectFromList(Database::getInstance()->getIsps(),
            "Select ISP:");

        ConnectionMethod *connectionMethod = 
            selectFromList(isp->getConnectionMethods(),
            "Select Connection Method:");


        Modem *modem = selectFromList(Database::getInstance()->getModems(),
            "Select a modem:");

        Dialer *dialer = modem->getDialer(isp);

        UserInput input;
        string username;
        do {
            username = listener->requestString("Enter username: ");
        } while (username.length() <= 0);
        input.setUsername(username);

        bool enableAutodetect = false;
        vector<string> autodetectionChoses;
        autodetectionChoses.push_back("yes");
        autodetectionChoses.push_back("no");
        if (listener->selectFromList("Do you wish to enable modem "
                "device autodetection?", autodetectionChoses) == 0) {
            enableAutodetect = true;
        }
        input.setInterfaceAutodetection(enableAutodetect);
        
        vector<string> modemDevice = Utils::enumNetworkInterfaces();
        if (enableAutodetect == true) {
            modemDevice.push_back("Auto-detect");
        }

        int selection = listener->selectFromList("Select modem device:",
            modemDevice);
        if (modemDevice[selection] != "Auto-detect") {
            input.setModemEthernetDevice(modemDevice[selection]);
        }

        ArgumentsScript::getInstance()->setIsp(isp);
        ArgumentsScript::getInstance()->setConnectionMethod(connectionMethod);
        ArgumentsScript::getInstance()->setModem(modem);
        ArgumentsScript::getInstance()->setUserInput(&input);

        // TODO: This is TEST CODE!
        ifstream initdFile("db/template/initd_service_template");
        ConnectionTemplate initd(initdFile);
        initdFile.close();
        initd.finializeScript(dialer);
        ofstream outFile("internet.sh", ios::trunc);
        outFile << initd.toString() << endl;
        outFile.close();
    } catch (Exception &ex) {
        string message = string("Aborting due to error: ") + ex.what();
        Log::fatal(message);
        listener->fatal(message + "\nSee console for details.");
        return -1;
    } catch (...) {
        Log::bug("Caught ... !");
        listener->fatal("Bug! See console for details");
        return -1;
    }

    ArgumentsScript::release();
    Database::release();
    GlobalRepository::release();

    return 0;
}

