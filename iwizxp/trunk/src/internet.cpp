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

/**
 * TODO
 */
int main() {
    try {
        Log::create(Log::DEBUG);

        vector<Isp*> isps = Database::getInstance()->getIsps();

        int selection, i;

        // Select an ISP
        do {
            cout << "Select an ISP:\n";
            vector<Isp*>::iterator iter;
            for (i = 0, iter = isps.begin() ;
                    iter != isps.end() ;
                    iter++, i++) {
                cout << (i + 1) << ") " << (*iter)->getName() << endl;
            }

            if (i > 1) {
                cout << "Selection [1-" << i << "]: ";
                cin >> selection;
            } else {
                selection = 1;
            }
                
            cout << endl;
        } while ((selection <= 0) || (selection > i));

        Isp *selectedIsp = isps[selection - 1];

        // Select a connection method
        vector<ConnectionMethod*> connectionMethods =
            selectedIsp->getConnectionMethods();

        do {
            cout << "Select a connection method:\n";
            vector<ConnectionMethod*>::iterator iter;
            for (i = 0, iter = connectionMethods.begin() ;
                    iter != connectionMethods.end() ;
                    iter++, i++) {
                cout << (i + 1) << ") " << (*iter)->toString() << endl;
            }

            if (i > 1) {
                cout << "Selection [1-" << i << "]: ";
                cin >> selection;
            } else {
                selection = 1;
            }
            
            cout << endl;
        } while ((selection <= 0) || (selection > i));

        // Select modem
        vector<Modem*> modems = Database::getInstance()->getModems();
        do {
            cout << "Select a modem:\n";
            vector<Modem*>::iterator iter;
            for (i = 0, iter = modems.begin() ;
                    iter != modems.end() ;
                    iter++, i++) {
                cout << (i + 1) << ") " << (*iter)->toString() << endl;
            }

            if (i > 1) {
                cout << "Selection [1-" << i << "]: ";
                cin >> selection;
            } else {
                selection = 1;
            }
            
            cout << endl;
        } while ((selection <= 0) || (selection > i));
    } catch (Exception &ex) {
        Log::fatal(string("Aborting due to error: ") + ex.what());
    }

    Log::release();

    return 0;
}
