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

#ifndef __XML_MODEM_LOADER_H__
#define __XML_MODEM_LOADER_H__

#include "ModemLoader.h"

/**
 * TODO: JavaDocs
 *
 * @author duvduv
 */
class XMLModemLoader : public ModemLoader {
public:

    /* --- Constructors ---- */

    /**
     * Constructor.
     * TODO: JavaDocs
     */
    XMLModemLoader() {
        Log::debug("XMLModemLoader created successfully");
    }

    /**
     * Destructor.
     * TODO: JavaDocs
     */
    virtual ~XMLModemLoader() {
        Log::debug("XMLModemLoader released successfully");
    }

    /* --- Public Methods --- */

    /**
     * TODO
     *
     * @throws LoadExcpetion TODO
     */
    virtual Modem *loadModem(std::istream &inStream) const;
};

#endif
