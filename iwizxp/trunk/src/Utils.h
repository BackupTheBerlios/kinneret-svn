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

#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <istream>
#include <vector>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/dom/DOMDocument.hpp>

#include "Exception.h"

/**
 * This namespace holds generic utility methods.
 */
namespace Utils {

    /**
     * This method reads a whole stream into a string.
     *
     * @param inStream Stream to read (untill EOF).
     * @return Stream's content, as <code>std::string</code>.
     */
    std::string readStreamAsString(std::istream &inStream);

    /**
     * Indicates that an enumeration attempt of a directory has failed.
     */
    NewException(DirectoryEnumerationException);

    /**
     * Enumerates the files that's in a specific directory, and returns a
     * vector of full paths.
     *
     * @param directory Path (absolute or relative) to the directory we wish
     *                  to enumerate.
     * @return A vector of strings full of all the files (not including '.',
     *         '..' and hidden files) in <code>directory</code>.
     * @throws DirectoryEnumerationException Thrown when the given directory
     *         could not be enumerated. The exception contains in
     *         <code>what()</code> the reason.
     */
    std::vector<std::string> enumDirectory(std::string directory);

    /**
     * This exception is thorwn when regex operation failes
     */
    NewException(RegexException);

    /**
     * This method compiles and executes a regex expression over a string.
     *
     * @param regexString Extended regular expression to execute
     * @param matchString String to execute the regex upon
     * @param maxResults Maximum number of matches
     * @return Vector of sub-strings of <code>string</code> that matched
     *         <code>regex</code>. If there was not match, the returned
     *         vector will be empty.
     * @throw RegexException When the regex couldnot bo compiled or executed.
     */
    std::vector<std::string> executeRegex(const std::string &regexString,
        const std::string &matchString, int maxResults);

    /**
     * TODO
     */
    xercesc::DOMDocument *documentFromStream(std::istream &inStream);

    /**
     * TODO
     */
    void getElementsByTagName(
        std::vector<const xercesc::DOMNode*> &result,
        const xercesc::DOMNode *root,
        std::string tagName,
        int depth = 1,
        int level = 0);
    
    /**
     * TODO
     */
    void xmlExceptionOccured(const xercesc::XMLException &ex);

    /**
     * TODO
     */
    void xmlExceptionOccured(const xercesc::SAXException &ex);
    
    /**
     * TODO
     */
    void xmlExceptionOccured(const xercesc::DOMException &ex);

    /**
     * TODO
     */
    std::string getAttribute(const xercesc::DOMNode *node,
        std::string attribute);

    /**
     * TODO
     */
    void sortXMLList(std::vector<const xercesc::DOMNode*> &result,
        const xercesc::DOMNode *listNode,
        std::string itemTag,
        std::string countAttribute = "count",
        std::string itemAttribute = "item");
}

#endif
