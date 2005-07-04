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

#ifndef __BASH_SYNTAX_SCRIPT_LOADER_H__
#define __BASH_SYNTAX_SCRIPT_LOADER_H__

#include "ScriptLoader.h"
#include "Log.h"

/**
 * This class reads a Bash script from the input stream, and creates
 * {@link FixedScript}s out of it. Note that the input given must contain a
 * single method alone.
 *
 * @author duvduv
 */
class BashSyntaxScriptLoader : public ScriptLoader {
public:

    /* --- Constructors ---- */

    /**
     * Constructor.
     */
    BashSyntaxScriptLoader() {
        Log::debug("BashSyntaxScriptLoader created successfully");
    }

    /**
     * Destructor.
     */
    virtual ~BashSyntaxScriptLoader() {
        Log::debug("BashSyntaxScriptLoader released successfully");
    }

    /* --- Inherited from ScriptLoader --- */

    /**
     * This function loads a script from a bash-syntaxed stream. The stream
     * must be in to form of a single Bash function. The loader extracts the
     * name of the methods from the stream, and loads the body into a new
     * {@link FixedScript}.
     *
     * Example script:
     * <pre>
     * myScriptName() {
     *     echo "Here's the body"
     * }
     * </pre>
     *
     * <b>Note</b>: The <code>Script</code> is dynamically allocated using
     * <code>new</code>. It is up to the caller to <code>delete</code> it.
     *
     * @param inStream Stream to load script from.
     * @return A new and initialized <code>FixedScript</code>. Note that the
     *        <code>Script</code> is allocated using <code>new</code>, and
     *        its up to the user to <code>delete</code> it.
     * @throws LoadException When the given stream is in the wrong format or
     *        any other problem occured during the loads process.
     */
    virtual Script *loadScript(std::istream &inStream) const;

private:

    /* --- Private Methods --- */

    /**
     * This method extracts the method's name out of the script using regex.
     *
     * @param body The entire script
     * @return The function's name
     * @throws LoadException When the name could not have been extracted from
     *         the given body.
     */
    virtual std::string extractNameFromScript(const std::string &body) const;

    /**
     * This method extracts the method's name out of it's definition line.
     *
     * @param body The definition line (leading and trailing spaces are
     *        allowed).
     * @return The function's name
     * @throws LoadException When the name could not have been extracted from
     *         the given definition.
     */
    virtual std::string extractNameFromDefinitionLine(const std::string &body)
        const;
};

#endif
