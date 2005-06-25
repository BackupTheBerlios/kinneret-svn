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

#include <vector>
#include <iostream>
// TODO: Remove
#include <fstream>

#include "Log.h"
#include "Isp.h"
#include "Database.h"
#include "GlobalRepository.h"
#include "ConnectionTemplate.h"
#include "ArgumentsScript.h"

using namespace std;

template<class T>
T selectFromList(vector<T> list, string prompt) {
    int selection, i;

    do {
        cout << prompt << endl;
        typename vector<T>::iterator iter;
        for (i = 0, iter = list.begin() ; iter != list.end() ; iter++, i++) {
            string option;

            // That's Java's instanceof in C++ :)
            Printable *obj = dynamic_cast<Printable*>(*iter);
            if (obj != 0) {
                option = obj->toString();
            } else {
                option = "null";
            }
            
            cout << (i + 1) << ") " << option << endl;
        }

        if (i > 1) {
            cout << "Selection [1-" << i << "]: ";
            cin >> selection;
        } else {
            selection = 1;
        }

        cout << endl;
    } while ((selection <= 0) || (selection > i));

    return list[selection - 1];
}

int main() {
    try {
        Log::create(Log::DEBUG);

        Isp *isp =
            selectFromList(Database::getInstance()->getIsps(),
            "Select ISP:");
        ArgumentsScript::getInstance()->setIsp(isp);

        ConnectionMethod *connectionMethod = 
            selectFromList(isp->getConnectionMethods(),
            "Select Connection Method:");
        ArgumentsScript::getInstance()->setConnectionMethod(connectionMethod);

        Modem *modem = 
            selectFromList(Database::getInstance()->getModems(),
            "Select a modem:");
        // TODO: resolv kernel and ask
        ArgumentsScript::getInstance()->setModem(modem,
            KernelModule::LINUX2_6);

        Dialer *dialer = modem->getDialer(isp);

        UserInput input;
        string str;
        cout << "Enter username: ";
        cin >> str;
        input.setUsername(str);

        cout << "Enter modem device: ";
        cin >> str;
        input.setModemEthernetDevice(str);

        ArgumentsScript::getInstance()->setUserInput(&input);

        ifstream initdFile("db/template/initd_service_template");
        ConnectionTemplate initd(initdFile);
        initdFile.close();
        initd.finializeScript(dialer);
        cout << initd.toString() << endl;
    } catch (Exception &ex) {
        Log::fatal(string("Aborting due to error: ") + ex.what());
    } catch (...) {
        Log::bug("Caught ... !");
    }

    ArgumentsScript::release();
    Database::release();
    GlobalRepository::release();
    Log::release();

    return 0;
}
