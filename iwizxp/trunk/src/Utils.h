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
     *
     * TODO: Support name pattern-match using regex :)
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
     * @throws RegexException When the regex couldnot bo compiled or executed.
     */
    std::vector<std::string> executeRegex(const std::string &regexString,
        const std::string &matchString, int maxResults);

    /**
     * The DOM namespace holds all kind of helper methods for handling DOM
     * trees.
     */
    namespace DOM {
        /**
         * Thrown by parsing method that cannot parse.
         */
        NewException(DOMParseException);
        
        /**
         * This method reads the entire given stream, and attempts to parse
         * it as an XML document.
         *
         * Note that the stream is read entirely, and not rewinded. This
         * means that information in the stream will not be available to
         * anyone after this method, unless the stream is rewinded using
         * <code>seekg()</code> or something similar.
         * 
         * @param inStream The input stream to read the XML document from.
         * @return The DOM representation of the documents that was in the
         *         stream.
         * @throws DOMParseException Thrown when the parser isn't available
         *         from the global repository, or when the parser could not
         *         parse the given stream.
         */
        xercesc::DOMDocument *parseDocumentFromStream(std::istream &inStream);

        /**
         * Recursively goes over the tree that <code>node</code> is its root,
         * and removes any text node that cotains whitespaces alone (should
         * be done by the normalization, but doesn't for some reason).
         *
         * TODO: If someone could tell me how to make Xerces' DOMBuilder to
         * act as it should, please tell me. This method is not a method I
         * like...
         *
         * @param node Any node that's under this node will be removed, if
         *        its an ignoreable text node.
         */
        void removeWhitespaceTextNodes(xercesc::DOMNode *node);

        /**
         * Used by <code>removeWhitespaceTextNodes</code>.
         *
         * @param node Node to test
         * @return <code>true</code> if the given node is a text node that
         *         holds nothing but whitespaces.
         */
        bool isIgnoreable(xercesc::DOMNode *node);

        /**
         * This method traverses the given tree up to a certain depth, and looks
         * for elements with the given name.
         *
         * @param result Result vector to store the elements found. Note that
         *        the vector will not be emptied upon calling this method.
         *        Elements are appended at the end of the vector (using
         *        <code>push_back()</code>).
         * @param root The root node, with represents level 0.
         * @param tagName The name of the tag that is looked for
         * @param depth Maximum depth to get into. Default is one level.
         * @param level Recursion counter (should not be set manually!)
         */
        void getElementsByTagName(
            std::vector<xercesc::DOMElement*> &result,
            xercesc::DOMElement *root,
            std::string tagName,
            int depth = 1,
            int level = 0);

        /**
         * This method looks for a single elements that matches the given
         * name up to the given depth from the root. In case it find more
         * than on mtching element, a warning message is issued, and the
         * first element found is returned.
         *
         * @param root The root node of the search
         * @param tagName Name of the tag we're looking
         * @param depth Maximum depth for the search, default is one.
         * @return The first element that's found (in case we found more than
         *         one, or <code>null</code>, in case nothing was found.
         */
        xercesc::DOMElement *getLoneElementByTagName(
            xercesc::DOMElement *root,
            std::string tagName,
            int depth = 1);

        /**
         * This method extracts the value of an attribute from the given
         * element.
         *
         * @param node Element with atrribute(s).
         * @param attribute Requested attribute's name
         * @return Attribute's value (or an empty string if the attribute
         *         doesn't exists).
         */
        std::string getAttributeValue(xercesc::DOMElement *node,
            std::string attribute);

        /**
         * This method builds a sorted array of <code>DOMElement</code>s from
         * the special structure defined in the XML for an array.
         *
         * Example:
         * The XML document:
         * <pre>
         * &lt;?xml version="1.0" encoding="UTF-8"?&gt;
         * &lt;document&gt;
         * &nbsp;&lt;someArray count="3"&gt;
         * &nbsp;&nbsp;&lt;someItem item="1"&gt;someValue1&lt;/someItem&gt;
         * &nbsp;&nbsp;&lt;someItem item="3"&gt;someValue3&lt;/someItem&gt;
         * &nbsp;&nbsp;&lt;foo&gt;bar&lt;/foo&gt;
         * &nbsp;&nbsp;&lt;someItem item="2"&gt;someValue2&lt;/someItem&gt;
         * &nbsp;&lt;/someArray&gt;
         * &lt;/document&gt;
         * </pre>
         * When passed to this method, with:
         * <pre>
         * arrayNode == someArray's DOMElement
         * itemTag == "someItem"
         * countAttribute == "count"
         * itemAttribute == "item"
         * </pre>
         * Results in:
         * <pre>
         * result.size() == 3
         * result[0]-&gt;getTextContent() == "someValue1"
         * result[1]-&gt;getTextContent() == "someValue2"
         * result[2]-&gt;getTextContent() == "someValue3"
         * </pre>
         * Even though the elements are not sorted correctly in the document
         * and there were unrelated elements in the middle of the list (they
         * are simply ignored).
         *
         * <b>Note</b>: The count in the XML is one-based, while zero-based in
         * the result vector.
         *
         * In case of format failure in the array element, <code>result</code>
         * will hold an empty vector of unknown length.
         *
         * In case of format failure in one of the elements, its entry in the
         * vector will hold <code>null</code>.
         *
         * @param result Vector to store the results in. <b>Note</b>: The
         *        given <code>vector</code> will be emptied and resized - Data
         *        in the vector will be lost!
         * @param arrayNode The node that begin the array (someArray's
         *        element in the example). This elements must have the
         *        attribute <code>countAttribute</code> that holds a valid
         *        decimal number representation that could be parsed using
         *        <code>atoi()</code> to an integer. Value of this attribute
         *        must match exactly the number of <code>itemTag</code>s
         *        under <code>arrayNode</code>.
         * @param itemTag The name of the tag of the elements that's under
         *        <code>arrayNode</code> that are list elements
         *        (<code>someItem</code> in the example).
         * @param countAttribute The name of the attribute found in
         *        <code>arrayNode</code> that holds the decimal
         *        representation of the number of elements in this array
         *        (<code>count</code> by default, and in the example).
         * @param itemAttribute The name of the attribute found under each
         *        <code>itemTag</code> that holds the representation of the
         *        index of the elements in the array. This value should be
         *        <i>one-based</i> (<code>item</code> by default, and in the
         *        example).
         */
        void elementsArrayFromXML(
                std::vector<xercesc::DOMElement*> &result,
                xercesc::DOMElement *arrayNode,
                std::string itemTag,
                std::string countAttribute = "count",
                std::string itemAttribute = "item");

        /**
         * Logs a nice error message to the logger.
         *
         * @param ex Exception to log.
         */
        void xmlExceptionOccured(const xercesc::XMLException &ex);

        /**
         * Logs a nice error message to the logger.
         *
         * @param ex Exception to log.
         */
        void xmlExceptionOccured(const xercesc::SAXException &ex);

        /**
         * Logs a nice error message to the logger.
         *
         * @param ex Exception to log.
         */
        void xmlExceptionOccured(const xercesc::DOMException &ex);
    }
}

#endif
