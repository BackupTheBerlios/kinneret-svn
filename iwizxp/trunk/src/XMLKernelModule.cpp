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

#include "XMLKernelModule.h"

#include "Utils.h"
#include "xts.h"
#include "Log.h"

using namespace std;
using namespace xercesc;
using namespace Utils;
using namespace Utils::DOM;

void XMLKernelModule::fromXML(DOMElement *root) {
    NamedXMLReadable::fromXML(root);

    vector<DOMElement*> modprobeNodes;
    getElementsByTagName(modprobeNodes, root, "modprobe");

    if (modprobeNodes.size() <= 0) {
        throw XMLSerializationException("No <modprobe> elements found!");
    }

    for (int i = 0 ; i < modprobeNodes.size() ; i++) {
        if (modprobeNodes[i] == 0) {
            Log::warning("Empty entry in list, skipping...");
            continue;
        }

        KernelClass kernel = kernelClassFromXML(modprobeNodes[i]);
        addName(kernel, xts(modprobeNodes[i]->getTextContent(), true));
    }
}

KernelModule::KernelClass XMLKernelModule::kernelClassFromXML(
        DOMElement *element) const {
    string classString = getAttributeValue(element, "kernel");

    if (classString == "2.4") {
        return LINUX2_4;
    } else if (classString == "2.6") {
        return LINUX2_6;
    } else {
        throw XMLSerializationException(string("Unknown kernel class: ") +
            classString);
    }
}

