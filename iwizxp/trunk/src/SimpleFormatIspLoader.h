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

#ifndef __SIMPLE_FORMAT_ISP_LOADER_H__
#define __SIMPLE_FORMAT_ISP_LOADER_H__

#include <istream>

#include "IspLoader.h"
#include "Cables.h"

#define MAX_LINE 1024

/**
 * TODO
 */
class SimpleFormatIspLoader : public IspLoader {
public:

    /* --- Constructors --- */

    /**
     * TODO
     */
    SimpleFormatIspLoader() : IspLoader() {
    }
    
    /**
     * TODO
     */
    virtual ~SimpleFormatIspLoader() {
    }

    /* --- Abstract Methods --- */

    /**
     * TODO
     */
    virtual Isp *loadIsp(std::istream &inStream) const throw (LoadExcpetion) {
        // Load name
        char name[MAX_LINE];
        inStream.getline(name, MAX_LINE, '\n');
        Isp *result = new Isp(std::string(name));
        
        // DNS
        int dnsCount;
        inStream >> dnsCount;
        inStream.ignore(MAX_LINE, '\n');
        for (int i = 0 ; i < dnsCount ; i++) {
            char dns[MAX_LINE];
            inStream.getline(dns, MAX_LINE, '\n');
            result->addDnsServer(IpAddress(dns));
        }

        // Connection method
        int methodCount;
        inStream >> methodCount;
        inStream.ignore(MAX_LINE, '\n');
        for (int i = 0 ; i < methodCount ; i++) {
            char method[MAX_LINE];
            inStream.getline(method, MAX_LINE, '\n');
            std::string methodString(method);
            if (methodString == "Cables") {
                std::string gw, destination;
                inStream >> gw >> destination;
                result->addConnectionMethod(new Cables(gw, destination));
            }
        }
        
        // Result
        return result;
    }
};

#endif
