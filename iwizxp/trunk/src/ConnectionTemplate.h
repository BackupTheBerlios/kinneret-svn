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
 * well, templates for the dialer. The template decides if the produced
 * scripts will be standalone, an init.d script or whatever. It supplies the
 * user an interface to put the dialer's code into the template, and to get
 * the final script.
 *
 * A typical template supplies the wrapping code for calling
 * <code>connect</code> and <code>disconnect</code>, and a place for the
 * dialer itself (noted in the template as <code>{dialer}</code>).
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
        Log::debug("Constructing ConnectionTemplate");

        Log::debug("Converting istream to string");
        script = Utils::readStreamAsString(inStream);
    }

    /**
     * Destructor. Does nothing but printing a pretty log message.
     */
    virtual ~ConnectionTemplate() {
        Log::debug("Destroying ConnectionTemplate");
    }

    /* --- Public Methods --- */

    /**
     * Creates the final script by placing the dialer inside the template.
     * The method replaces the string <code>{dialer}</code> with the code
     * from the dialer, which should create the methods <code>connect</code>
     * and <code>disconnect</code> the template calls.
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
     * Creates the block that should replace the string <code>{dialer}</code>
     * found in the template.
     *
     * This is the core of the <code>ConnectionTemplate</code> - It renders a
     * <code>Dialer</code> to actual Bash code.
     *
     * @param dialer <code>Dialer</code> to create code from.
     * @return Code to replace <code>{dialer}</code>
     */
    std::string prepareDialerCode(Dialer *dialer) const;
    
    /**
     * Creates a text-block with definitions of all the segments that are in
     * the given vector. A segment is the code of the scripts supplied
     * (definitions alone, no calls).
     *
     * The method adds headers with the description of the
     * method, if such is presented.
     *
     * This method also ensures that the same script won't be defined twice
     * in a template, using a set of already written scripts. If a script
     * appears twice (or more) in the final template, a commet is left where
     * the actual body should have been after the first time the script is
     * written.
     *
     * @param scripts List of scripts to define.
     * @param alreadyWritten Set of function names of the function that were
     *        already written to the final script. This is used to prevent
     *        double definitions of the same method. The set will be modified by
     *        this method. Every <b>new</b> method that's written to the file
     *        will be added to the set, so it can be used incrementally with
     *        perceeding calls to this method.
     * @return Code containing the definition of all the methods in the list.
     */
    std::string prepareScriptsSegment(std::vector<Script*> scripts,
        std::set<std::string> &alreadyWritten) const;

    /**
     * Creates a code-block with a single method that calls all the scripts
     * in the list by their order.
     *
     * This method is used to create <code>connect</code> and
     * <code>disconnect</code>.
     *
     * @param methodName The name of the method that will call all the
     *        scripts.
     * @param description Methods description (will be placed in a comment
     *        above the method)
     * @param scripts Ordered list of scripts.
     * @return Text block with one method named <code>methodName</code> which
     *         calls the scripts in the vector by their order.
     */
    std::string prepareScriptCallingMethod(std::string methodName,
        std::string description, std::vector<Script*> scripts) const;

    /**
     * This method formats a decription string to be of the format:
     * <pre>
     * ##
     * # description
     * ##
     * </pre>
     * By appending an prepending '##', and replacing every newline with a
     * commented newline (e.g. '#\n ').
     *
     * The method <i>does not</i> align the comments to the 80-chars border.
     *
     * @param description A regular description string, with (or without)
     *        newlines.
     * @return Formated comment that can be placed above a method (80-chars
     *         boundry <i>not</i> guarenteed).
     */
    std::string formatDescription(std::string description) const;

    /**
     * Prepends and appends default dialers to the given scripts.
     *
     * The default dialers are a list of scripts that should be ran before
     * and after the dialer. They are regular dialers, that prepares the
     * groud for the actual connection code.
     *
     * These dialers usually define user variables and sets configuration
     * such as ppp sercets and DNS.
     *
     * @param connectionScripts List of connection scripts. The list will be
     *        altered to contain the original list between the scripts of the
     *        default connection pre-dialer, and the scripts of the default
     *        connection post-dialer.
     * @param disconnectionScripts List of disconnection scripts. The list
     *        will be altered as <code>connectionScripts</code>.
     */
    void addDefaults(std::vector<Script*> &connectionScripts,
        std::vector<Script*> &disconnectionScripts) const;

    /* --- Data Members --- */

    /** The script */
    std::string script;
};

#endif
