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

template<class T> T Wizard::selectFromList(string what, vector<T> list) {
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

	selection = safeSelectFromList(what, toListener);
	return list[selection];
}

int Wizard::safeSelectFromList(string what, vector<string> list) {
	int selection;

	while (1) {
		selection = listener->selectFromList(what, list);
		if ((selection < 0) || (selection >= list.size())) {
			listener->notify("Selected choise is out-of-range. "
				"Please retry.");
		} else {
			break;
		}
	}

	return selection;
}

int Wizard::go() {
	// TODO: Refactor-extract methods
	try {
		Isp *isp = selectFromList("Select ISP",
			Database::getInstance()->getIsps());

		ConnectionMethod *connectionMethod = 
			selectFromList("Select Connection Method",
				isp->getConnectionMethods());


		Modem *modem = selectFromList("Select modem", 
			Database::getInstance()->getModems());

		Dialer *dialer = modem->getDialer(isp);

		UserInput input;
		string username;
		while (1) {
			username = listener->requestString("Enter username: ");
			if (username.length() <= 0) {
				listener->notify(
					"Username cannot be an empty string.");
			} else {
				break;
			}
		};
		input.setUsername(username);

		bool enableAutodetect = false;
		vector<string> autodetectionChoses;
		autodetectionChoses.push_back("yes");
		autodetectionChoses.push_back("no");
		if (safeSelectFromList("Do you wish to enable modem "
			"device autodetection?", autodetectionChoses) == 0) {
			enableAutodetect = true;
		}
		input.setInterfaceAutodetection(enableAutodetect);

		vector<string> modemDevice = Utils::enumNetworkInterfaces();
		if (enableAutodetect == true) {
			modemDevice.push_back("Auto-detect");
		}

		int selection = safeSelectFromList(
			"Select modem device:", modemDevice);
		if (modemDevice[selection] != "Auto-detect") {
			input.setModemEthernetDevice(modemDevice[selection]);
		}

		ArgumentsScript *argumentsScript =
			GlobalRepository::getInstance()->getArgumentsScript();

		argumentsScript->setIsp(isp);
		argumentsScript->setConnectionMethod(connectionMethod);
		argumentsScript->setModem(modem);
		argumentsScript->setUserInput(&input);

		ConnectionTemplate *connectionTempate = selectFromList(
			"Select connection template",
			Database::getInstance()->getConnectionTemplates());

		string outputFile;
		while (1) {
			outputFile = listener->requestString("Output file: ");
			if (outputFile.length() <= 0) {
				listener->notify(
					"Output file cannot be an "
					"empty string.");
			} else {
				break;
			}
		};

		ofstream outputFileStream(outputFile.c_str(), ios::trunc);
		outputFileStream <<
			connectionTempate->getFinalScript(dialer) << endl;
		outputFileStream.close();
	} catch (Exception &ex) {
		string message = string("Aborting due to error: ") + ex.what();
		Log::fatal(LOG_LOCATION("Wizard", "go"), message);
		listener->fatal(message + "\nSee console for details.");
		return -1;
	} catch (...) {
		Log::bug(LOG_LOCATION("Wizard", "go"), "Caught ... !");
		listener->fatal("Bug! See console for details");
		return -1;
	}

	Database::release();
	GlobalRepository::release();

	return 0;
}

