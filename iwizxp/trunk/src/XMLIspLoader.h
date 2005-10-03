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

#ifndef __XML_ISP_LOADER_H__
#define __XML_ISP_LOADER_H__

#include "IspLoader.h"

/**
 * Loads ISPs from XML.
 *
 * @author duvduv
 */
class XMLIspLoader : public IspLoader {
public:

    /* --- Constructors ---- */

    /**
     * Constructor.
     *
     * Does nothing.
     */
    XMLIspLoader() {
        Log::debug("Creating XMLIspLoader");
    }

    /**
     * Destructor.
     *
     * Does nothing.
     */
    virtual ~XMLIspLoader() {
        Log::debug("Destroying XMLIspLoader");
    }

    /* --- Public Methods --- */

    /**
     * Loads an ISP from a stream. <code>stream</code> should contain valid
     * XML. This method parses the stream to a DOM document, then
     * de-serialize an ISP from the top-level <code>&lt;isp&gt;</code> tag.
     *
     * @param inStream The stream to build a DOM tree from.
     * @return A new and initialized <code>Isp</code>.
     * @throws LoadExcpetion Thrown when the loads wasn't able to parse the
     *         stream, or an <code>XMLSerializationException</code> was
     *         thrown from <code>Isp</code>'s <code>fromXML()</code>.
     */
    virtual Isp *loadIsp(std::istream &inStream) const;
};

#endif
