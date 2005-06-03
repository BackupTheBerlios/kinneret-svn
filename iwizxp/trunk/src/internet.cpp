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

#include "Log.h"
#include "Isp.h"
#include "Database.h"

using namespace std;

template<class T>
T selectFromList(vector<T> list, string prompt) {
    int selection, i;

    do {
        cout << prompt << endl;
        typename vector<T>::iterator iter;
        for (i = 0, iter = list.begin() ; iter != list.end() ; iter++, i++) {
            string option;

            // That's instanceof in C++ :)
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

/**
 * TODO: Refactor stuff.
 */
int main() {
    try {
        Log::create(Log::DEBUG);

        Isp *selectedIsp =
            selectFromList(Database::getInstance()->getIsps(),
            "Select ISP:");

        ConnectionMethod *connectionMethod = 
            selectFromList(selectedIsp->getConnectionMethods(),
            "Select Connection Method:");

        Modem *modem = 
            selectFromList(Database::getInstance()->getModems(),
            "Select a modem:");

    } catch (Exception &ex) {
        Log::fatal(string("Aborting due to error: ") + ex.what());
    }

    Log::release();

    return 0;
}
