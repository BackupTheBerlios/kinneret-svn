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

#include <string>

#include "XMLConnectionMethodFactory.h"

using namespace std;

const string XMLConnectionMethodFactory::CABLES_NAME = "Cables";
const string XMLConnectionMethodFactory::ADSL_NAME   = "ADSL";
const string XMLConnectionMethodFactory::ISDN_NAME   = "ISDN";
const string XMLConnectionMethodFactory::DIALUP_NAME = "Dialup";

ConnectionMethod *XMLConnectionMethodFactory::create(const std::string name,
		xercesc::DOMElement *element) {
	XMLConnectionMethod *result = 0;

	if (name == CABLES_NAME) {
		result = new XMLCables();
	} /* else if (name == ADSL_NAME) {
	     result = new XMLAdsl();
	} ... */

	if (result != 0) {
		result->fromXML(element);
	} else {
		// TODO: Throw something?
		Log::debug(LOG_LOCATION("XMLConnectionMethodFactory", "create"),
			string("Unknown connection method: ") + name);
	}

	return result;
}

