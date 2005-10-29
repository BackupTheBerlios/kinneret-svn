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

#include "Modem.h"

#include "Log.h"
#include "Utils.h"
#include "GlobalRepository.h"

using namespace std;
using namespace Utils;

Dialer *Modem::loadDialerByName(string name) {
	string dialerName =
		GlobalRepository::getInstance()->getDbBasePath() +
		"/dialer/" + name + ".xml";

	ifstream dialerStream(dialerName.c_str(), ios::in);

	if (!dialerStream.is_open()) {
		throw DialerCreationException("Unable to load dialer!");
	}

	Dialer *dialer = 0;

	try {
		dialer =
			GlobalRepository::getInstance()->getDialerLoader()->
			loadDialer(dialerStream);
	} catch (DialerLoader::LoadException &ex) {
		// Close stream an re-throw
		dialerStream.close();
		throw DialerCreationException(
			string("LoadException: ") + ex.what());
	}

	dialerStream.close();

	if (dialer != 0) {
		addDialer(dialer);
	}

	return dialer;
}

Modem::~Modem() {
	releaseKernelModules();
	releaseDialers();
}

void Modem::releaseKernelModules() {
	vector<KernelModule*>::iterator iter;
	for (iter = modulesVector.begin() ; iter != modulesVector.end() ; iter++) {
		Log::debug(LOG_LOCATION("Modem", "releaseKernelModules"),
			string("Releasing ") + (*iter)->toString() + "...");
		delete (*iter);
		(*iter) = 0;
	} 
}

void Modem::releaseDialers() {
	vector<Dialer*>::iterator iter;
	for (iter = loadedDialers.begin() ;
			iter != loadedDialers.end() ;
			iter++) {
		Log::debug(LOG_LOCATION("Modem", "releaseDialers"),
			string("Releasing ") + (*iter)->toString() + "...");
		delete (*iter);
		(*iter) = 0;
	} 
}
    
Dialer *Modem::getDialer(Isp *isp) {
	map<string, Dialer*>::iterator exception =
		exceptions.find(isp->getName());

	if (exception == exceptions.end()) {
		return defaultDialer;
	} else {
		return exception->second;
	}
}

