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
#include <set>

#include "Printable.h"
#include "Exception.h"
#include "Dialer.h"
#include "Utils.h"

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
        script = Utils::readStreamAsString(inStream);

        Log::debug("ConnectionTemplate created successfully");
    }

    /**
     * Destructor, does nothing.
     */
    virtual ~ConnectionTemplate() {
        Log::debug("ConnectionTemplate released successfully");
    }

    /* --- Public Methods --- */

    /**
     * Creates the final script by placing the dialer inside the template.
     *
     * @param dialer <code>Dialer</code> to place in the template.
     */
    void finializeScript(Dialer *dialer);

    /* --- Inherited from Prinable --- */

    /**
     * @return The full script. Call this after finalization.
     */
    virtual const std::string toString() const {
        return script;
    }

private:

    /* --- Utility Methods --- */

    /**
     * Creates the test block that should replace the string
     * <code>{dialer}</code> found in the template.
     *
     * @param dialer <code>Dialer</code> to create code block from.
     * @return Code block to replace <code>{dialer}</code>
     */
    std::string prepareDialerCode(Dialer *dialer) const;
    
    /**
     * Creates a text-block with definitions of all the segments that are in
     * the given vector. The method adds headers with the description of the
     * method, if such is presented.
     *
     * @param scripts List of scripts to declare
     * @param alreadyWritten Set of function names of the function that were
     *        already written. This is used to prevent double definitions of
     *        the same method. The set will be modified by this method. Every
     *        <b>new</b> method that's written to the files will be added to
     *        the set, so it can be used incrementally with perceeding calls
     *        to this method.
     * @return Code block containing the definition of all the methods in the
     *         list.
     */
    std::string prepareScriptsSegment(std::vector<Script*> scripts,
        std::set<std::string> &alreadyWritten) const;

    /**
     * Creates a text-block with a single method that calls all the scripts
     * in the list by their order.
     *
     * @param methodName Method's name
     * @param scripts Ordered list of scripts to call
     * @return Text block with one method named <code>methodName</code> which
     *         calls the scripts in the vector by their order.
     */
    std::string prepareScriptCallingMethod(std::string methodName,
        std::vector<Script*> scripts) const;

    /* --- Data Members --- */

    /** The script */
    std::string script;
};

#endif
