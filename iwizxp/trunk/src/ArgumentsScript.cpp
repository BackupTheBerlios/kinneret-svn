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
	values["modules2_4"] =
		buildKernelClassModulesList(modem, KernelModule::LINUX2_4);

	values["modules2_6"] =
		buildKernelClassModulesList(modem, KernelModule::LINUX2_6);
}


void ArgumentsScript::setConnectionMethod(const ConnectionMethod *method) {
	values["dialingDestination"] = method->getDialingDestination();
	values["defaultGateway"] = method->getDefaultGateway();
}

void ArgumentsScript::setUserInput(const UserInput *input) {
	values["username"] = input->getUsername();

	if (input->useInterfaceAutodetection()) {
		values["autodetectInterface"] = "yes";
	}

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

string ArgumentsScript::buildKernelClassModulesList(const Modem *modem,
		KernelModule::KernelClass kernelClass) {
	vector<string> supportedModules;

	// First pass, see which modules are good for us
	for (int i = 0 ; i < modem->getKernelModules().size() ; i++) {
		KernelModule *current = modem->getKernelModules()[i];
		try {
			supportedModules.push_back(
				current->getName(kernelClass));
		} catch (KernelModule::FeatureNotSupportedException &ex) {
			// Leave outside
		}
	}

	// Second pass, make the string
	ostringstream result;

	for (int i = 0 ; i < supportedModules.size() ; i++) {
		result << supportedModules[i];

		// Add a space if this modules isn't the last
		if (i < (supportedModules.size() - 1)) {
			result << " ";
		}
	}

	return result.str();
}

