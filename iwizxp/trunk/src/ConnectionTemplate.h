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

#ifndef __CONNECTION_TEMPLATE_H__
#define __CONNECTION_TEMPLATE_H__

#include <istream>

#include "Printable.h"
#include "Exception.h"
#include "Dialer.h"

/**
 * This class represents a connection template. Connection templates are,
 * well, templates for the calls of the dialer. The template decides if the
 * produced scripts will be standalone, an init.d script or what ever. It
 * supplies the user an interface to put the dialer's code into the template,
 * and get the final script.
 *
 * @author duvduv
 */
class ConnectionTemplate : public Printable {
public:

    /* --- Constructors --- */

    /**
     * Constructor. Reads the template from the stream.
     *
     * @param inStream Stream to read the script from.
     */
    ConnectionTemplate(std::istream &inStream) : Printable() {
        readScript(inStream);
    }

    /**
     * Destructor, does nothing.
     */
    virtual ~ConnectionTemplate() {
        // Nothing to do
    }

    /* --- Public Methods --- */

    /**
     * TODO: Implement.
     *
     * Creates the final script by placing the dialer inside the template.
     *
     * @param dialer <code>Dialer</code> to place in the template.
     */
    void finializeScript(Dialer *dialer);

    /* --- Inherited from Prinable --- */

    /**
     * @return The full script
     */
    virtual const std::string toString() const {
        return script;
    }

private:

    /* --- Private Methods --- */

    /**
     * Reads untill EOF from the stream, and stores it in
     * <code>script</code>.
     *
     * TODO: Implement
     */
    void readScript(std::istream &inStream);

    /* --- Data Members --- */

    /** The script */
    std::string script;
};

#endif
