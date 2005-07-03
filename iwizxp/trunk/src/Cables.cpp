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

#include "Cables.h"

#include "Utils.h"
#include "xts.h"

using namespace std;
using namespace xercesc;
using namespace Utils;

void Cables::fromXML(const DOMElement *root) throw (XMLFormatException) {
    extractGatewayFromXML(root);
    extractDialingDestinationFromXML(root);
}

void Cables::extractGatewayFromXML(const DOMElement *root)
        throw (XMLFormatException) {
    vector<const DOMNode*> gatewayNodes;
    getElementsByTagName(gatewayNodes, root, "gateway");

    if (gatewayNodes.size() == 0) {
        throw XMLFormatException("No <gateway> element!");
    } else if (gatewayNodes.size() > 1) {
        Log::warning("More than one <gateway> element found, using first.");
    }

    defaultGateway = xts(gatewayNodes[0]->getTextContent(), true);
    Log::debug("Default Gateway: " + defaultGateway);
}

void Cables::extractDialingDestinationFromXML(const DOMElement *root)
        throw (XMLFormatException) {
    vector<const DOMNode*> destinationNodes;
    getElementsByTagName(destinationNodes, root, "destination");

    if (destinationNodes.size() == 0) {
        throw XMLFormatException("No <destination> element!");
    } else if (destinationNodes.size() > 1) {
        Log::warning("More than one <destination> element found, using first.");
    }

    dialingDestination = xts(destinationNodes[0]->getTextContent(), true);
    Log::debug("Dialing Destination: " + dialingDestination);
}
