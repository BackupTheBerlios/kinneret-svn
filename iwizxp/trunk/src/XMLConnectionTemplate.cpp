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

#include "XMLConnectionTemplate.h"

#include <fstream>

#include "Utils.h"
#include "Log.h"
#include "xts.h"
#include "GlobalRepository.h"

using namespace std;
using namespace xercesc;
using namespace Utils;
using namespace Utils::DOM;

void XMLConnectionTemplate::fromXML(DOMElement *root) {
    // Name
    NamedXMLReadable::fromXML(root);

    // Description
    // TODO: Refactor extract method
    vector<DOMElement*> elements;
    getElementsByTagName(elements, root, "description");
    if (elements.size() <= 0) {
        Log::warning("No description tag found!");
        setDescription("No description");
    } else {
        setDescription(xts(elements[0]->getTextContent(), true));
    }
    
    // File
    // TODO: Refactor extract method
    elements.clear();
    getElementsByTagName(elements, root, "file");
    if (elements.size() <= 0) {
        throw XMLSerializationException("No <file> tag found!");
    }
    
    // TODO: Don't hard-code it in.
    string templateFile = GlobalRepository::getInstance()->getDbBasePath() +
        string("/template/") +
        xts(elements[0]->getTextContent(), true).asString();

    ifstream scriptStream(templateFile.c_str(), ios::in);

    if (!scriptStream.is_open()) {
        throw XMLSerializationException("Unable to open " + templateFile +
            " for reading!");
    }

    loadTemplate(scriptStream);

    scriptStream.close();
}
