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

#include "Dialer.h"
#include "ArgumentsScript.h"
#include "GlobalRepository.h"

using namespace std;

void Dialer::releaseScripts() {
    releaseConnectionScripts();
    releaseDisconnectionScripts();
}

void Dialer::releaseConnectionScripts() {
    Log::debug("Releasing connection scripts...");
    vector<Script*>::iterator iter;

    for (iter = connectionScripts.begin() ;
            iter != connectionScripts.end() ; 
                iter++) {
        // Don't release ArgumentsScript - it's a singleton that has to be
        // released individually AND ONLY ONCE!
        if (((*iter) != 0) && ((*iter) != GlobalRepository::getInstance()->
                getArgumentsScript())) {
            Log::debug(string("Releasing ") +
                (*iter)->getFunctionName() + "...");
            delete (*iter);
            (*iter) = 0;
        }
    }
    Log::debug("Connection scripts released successfully");
}

void Dialer::releaseDisconnectionScripts() {
    Log::debug("Releasing disconnection scripts...");
    vector<Script*>::iterator iter;

    for (iter = disconnectionScripts.begin() ;
            iter != disconnectionScripts.end() ; 
                iter++) {
        if ((*iter) != 0) {
            Log::debug(string("Releasing ") +
                (*iter)->getFunctionName() + "...");
            delete (*iter);
            (*iter) = 0;
        }
    }
    Log::debug("Disconnection scripts released successfully");
}

