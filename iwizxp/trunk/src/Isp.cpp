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

#include <sstream>

#include "Isp.h"

using namespace std;

Isp::~Isp() {
    std::vector<ConnectionMethod*>::iterator iter;
    for (iter = methods.begin() ; iter != methods.end() ; iter++) {
        delete (*iter);
        (*iter) = 0;
    }
}

const string Isp::toString() const {
    ostringstream result;
    result << name << ":\n" << "DNS Servers:\n";

    vector<IpAddress> dns = getDnsServers();
    vector<IpAddress>::iterator dnsIter;
    for (dnsIter = dns.begin() ; dnsIter != dns.end() ; dnsIter++) {
        result << "\t- " << (*dnsIter).toString() << "\n";
    }

    result << "Available connection methods:" << endl;
    vector<ConnectionMethod*> methods = getConnectionMethods();
    vector<ConnectionMethod*>::iterator methodsIter;
    for (methodsIter = methods.begin() ;
            methodsIter != methods.end() ;
            methodsIter++) {
        result << "- " << (*methodsIter)->toString() << endl;

        if ((*methodsIter)->hasDefaultGateway()) {
            result << "\tDefault gateway: " <<
                (*methodsIter)->getDefaultGateway() << endl;
        }

        result << "\tDialing destination: " <<
            (*methodsIter)->getDialingDestination() << endl;
    }

    result << endl;

    return result.str();
}
