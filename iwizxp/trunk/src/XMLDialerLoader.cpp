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

#include <xercesc/dom/DOMDocument.hpp>

#include "XMLDialerLoader.h"
#include "XMLDialer.h"

#include "Utils.h"

using namespace std;
using namespace xercesc;
using namespace Utils;
using namespace Utils::DOM;

Dialer *XMLDialerLoader::loadDialer(istream &inStream) const {
    DOMDocument *document;
    try {
        document = Utils::DOM::parseDocumentFromStream(inStream);
        document->normalizeDocument();
        removeWhitespaceTextNodes(document->getDocumentElement());
    } catch (const DOMParseException &ex) {
        throw LoadException("XMLException, see above");
    }

    try {
        XMLDialer *result = new XMLDialer();
        result->fromXML(document->getDocumentElement());
        return result;
    } catch (const XMLReadable::XMLSerializationException &ex) {
        Log::error(LOG_LOCATION("XMLDialerLoader", "loadDialer"),
            "Got XMLSerializationException while creating dialer...");
        throw LoadException(ex.what());
    }
}

