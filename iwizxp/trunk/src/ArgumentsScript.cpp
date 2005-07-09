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

#include "ArgumentsScript.h"

using namespace std;

// Instance
ArgumentsScript *ArgumentsScript::instance = 0;

void ArgumentsScript::setIsp(const Isp *isp) {
    ostringstream nameservers;
    
    vector<IpAddress>::const_iterator iter;
    for (iter = isp->getDnsServers().begin() ; 
            iter != isp->getDnsServers().end() ; 
            iter++) {
        // Space nameservers up
        if (iter != isp->getDnsServers().begin()) {
            nameservers << " ";
        }
        
        nameservers << (*iter).toString();
    }

    values["nameservers"] = nameservers.str();

    // TODO: search groups (setup to $searchGroups)
}

void ArgumentsScript::setModem(const Modem *modem) {
    ostringstream modules2_4;
    ostringstream modules2_6;
    
    vector<KernelModule*>::const_iterator iter;
    for (iter = modem->getKernelModules().begin() ;
            iter != modem->getKernelModules().end() ; 
            iter++) {
        try {
            // Space modules up
            if (iter != modem->getKernelModules().begin()) {
                modules2_4 << " ";
                modules2_6 << " ";
            }
            
            // Add module to the list
            try {
                modules2_4 << (*iter)->getName(KernelModule::LINUX2_4);
            } catch (KernelModule::FeatureNotSupportedException &ex) {
                // Nothing, leave blank
            }

            try {
                modules2_6 << (*iter)->getName(KernelModule::LINUX2_6);
            } catch (KernelModule::FeatureNotSupportedException &ex) {
                // Nothing, leave blank
            }
        } catch (KernelModule::FeatureNotSupportedException &ex) {
            Log::warning((*iter)->toString() + " is not supported under the "
                "selected kernel, skipping.");
        }
    }

    values["modules2_4"] = modules2_4.str();
    values["modules2_6"] = modules2_6.str();
}

void ArgumentsScript::setConnectionMethod(const ConnectionMethod *method) {
    values["dialingDestination"] = method->getDialingDestination();
    values["defaultGateway"] = method->getDefaultGateway();
}

void ArgumentsScript::setUserInput(const UserInput *input) {
    values["username"] = input->getUsername();

    if (input->hasEthernetDevice()) {
        values["modemEthernetDevice"] = input->getModemEthernetDevice();
    }
}
    
const string ArgumentsScript::getScriptBody() const {
    ostringstream result;

    result << getFunctionName() << "() {" << endl;

    map<string, string>::const_iterator iter;
    for (iter = values.begin() ; iter != values.end() ; iter++) {
        result << '\t' << (*iter).first << "=\"" <<
            (*iter).second << "\"" << endl;
    }

    // Close method
    result << "}" << endl;

    return result.str();
}
