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

#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/util/XMLUniDefs.hpp>

#include "GlobalRepository.h"

#include "Utils.h"
#include "xts.h"
#include "XMLIspLoader.h"
#include "XMLModemLoader.h"
#include "BashSyntaxScriptLoader.h"
#include "SimpleFormatDialerLoader.h"

using namespace std;
using namespace xercesc;

// Singleton instance
GlobalRepository *GlobalRepository::instance = 0;

void GlobalRepository::setupLoaders() {
    ispLoader = new XMLIspLoader();
    modemLoader = new XMLModemLoader();
    scriptLoader = new BashSyntaxScriptLoader();
    dialerLoader = new SimpleFormatDialerLoader();
}

void GlobalRepository::releaseLoaders() {
    delete dialerLoader;
    delete scriptLoader;
    delete modemLoader;
    delete ispLoader;
}

void GlobalRepository::setupXerces() {
    // Initialize Xerces
    try {
        XMLPlatformUtils::Initialize();
    } catch (const XMLException &ex) {
        Utils::DOM::xmlExceptionOccured(ex);
        // TODO: Something smart
    }

    // LS
    static const XMLCh ls[] = { chLatin_L, chLatin_S, chNull };
    DOMImplementationLS *domImplementation =
        dynamic_cast<DOMImplementationLS*>
            (DOMImplementationRegistry::getDOMImplementation(ls));

    if (domImplementation == 0) {
        // TODO: Somethind smart
    }

    domBuilder = domImplementation->createDOMBuilder(
        DOMImplementationLS::MODE_SYNCHRONOUS, 0);

    domBuilder->setFeature(Utils::xts("comments"), false);
    domBuilder->setFeature(Utils::xts("whitespace-in-element-content"), false);
}

void GlobalRepository::releaseXerces() {
    domBuilder->release();
    XMLPlatformUtils::Terminate();
}

