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

#include <sstream>

#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#include "Utils.h"

#include "xts.h"
#include "GlobalRepository.h"

using namespace std;
using namespace xercesc;
using namespace Utils;
using namespace Utils::DOM;

DOMDocument *Utils::DOM::parseDocumentFromStream(istream &inStream) {
    // Calculate stream length
    istream::pos_type location = inStream.tellg();
    inStream.seekg(0, ios::end);
    istream::pos_type streamLength = inStream.tellg() - location;
    inStream.seekg(location, ios::beg);

    // Allocate buffer and read stream
    char *xmlBuffer = new char[streamLength];
    inStream.read(xmlBuffer, streamLength);

    // Parse from memory
    try {
        DOMBuilder *builder = GlobalRepository::getInstance()->getDOMBuilder();
        if (builder == 0) {
            throw DOMParseException("Unable to get DOMBuilder from global "
                "repository");
        }

        // MemBufInputSource adopts xmlBuffer
        MemBufInputSource *memBuf = new MemBufInputSource(
            reinterpret_cast<XMLByte*>(xmlBuffer), streamLength,
                "StreamDocument", true);
        
        // Wrapper4InputSource adopts the MemBufInputSource
        return builder->parse(Wrapper4InputSource(memBuf));
    } catch (const XMLException &ex) {
        xmlExceptionOccured(ex);
        throw DOMParseException("Unable to parse, message should have "
            "been supplied");
    } catch (const DOMException &ex) {
        xmlExceptionOccured(ex);
        throw DOMParseException("Unable to parse, message should have "
            "been supplied");
    } catch (const SAXException &ex) {
        xmlExceptionOccured(ex);
        throw DOMParseException("Unable to parse, message should have "
            "been supplied");
    }
}

void Utils::DOM::removeWhitespaceTextNodes(DOMNode *node) {
    if (node != 0) {
        removeWhitespaceTextNodes(node->getFirstChild());
        removeWhitespaceTextNodes(node->getNextSibling());

        if (node->getNodeType() == DOMNode::TEXT_NODE) {
            if (isIgnoreable(node)) {
                node->getParentNode()->removeChild(node);
            }
        }
    }
}

bool Utils::DOM::isIgnoreable(DOMNode *node) {
    string content = xts(node->getTextContent());
    for (int i = 0 ; i < content.length() ; i++) {
        if (!isspace(content[i])) {
            return false;
        }
    }

    return true;
}

void Utils::DOM::getElementsByTagName(vector<const DOMElement*> &result,
        const DOMElement *root, string tagName, int depth, int level) {
    if (root == 0) {
        return;
    }

    // Check match
    if (xts(root->getTagName()).asString() == tagName) {
        result.push_back(root);
    }

    // Get inside
    if (root->hasChildNodes() && (level < depth)) {
        DOMNode *child = root->getFirstChild();
        if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
            getElementsByTagName(result, dynamic_cast<DOMElement*>(child),
                tagName, depth, level + 1);
        }
    }

    // Next, pnly under root, not alongside it.
    if (level > 0) {
        DOMNode *child = root->getNextSibling();
        if (child != 0) {
            if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
                getElementsByTagName(result, dynamic_cast<DOMElement*>(child),
                    tagName, depth, level);
            }
        }
    }
}

string Utils::DOM::getAttributeValue(const DOMElement *node,
        string attribute) {
    DOMNamedNodeMap *nodeAttributes = node->getAttributes();

    if (nodeAttributes == 0) {
        Log::debug("No attributes");
        return "";
    }
    
    DOMNode *attributeNode = nodeAttributes->getNamedItem(xts(attribute));
    if (attributeNode == 0) {
        Log::debug("Couldn't find '" + attribute + "' attribute.");
        return "";
    } else {
        return xts(attributeNode->getTextContent());
    }
}

void Utils::DOM::elementsArrayFromXML(
        vector<const DOMElement*> &result,
        const DOMElement *arrayNode,
        string itemTag,
        string countAttribute,
        string itemAttribute) {
    // Empty vector
    result.empty();

    // How much elements?
    string countAttributeValue = getAttributeValue(arrayNode, countAttribute);
    if (countAttributeValue.length() == 0) {
        Log::debug(xts(arrayNode->getNodeName()).asString() + " has no '" +
            countAttribute + "' attribute!");
        return;
    }

    const int count = atoi(countAttributeValue.c_str());

    if (!arrayNode->hasChildNodes() || count <= 0) {
        Log::debug("Empty list");
        return;
    }

    // Resize vector and set to null
    result.resize(count);
    for (int i = 0 ; i < count ; i++) {
        result[i] = 0;
    }
    
    DOMElement *child = 0;
    DOMNode *childNode = arrayNode->getFirstChild();
    if (childNode == 0) {
        Log::error("No item elements at all!");
        return;
    }
    
    if (childNode->getNodeType() == DOMNode::ELEMENT_NODE) {
        child = dynamic_cast<DOMElement*>(childNode);
    }

    while (child != 0) {
        if (xts(child->getNodeName()).asString() != itemTag) {
            // Wrong tag name, skip
        } else {
            // Get location in the vector
            string itemNumber = getAttributeValue(child, itemAttribute);
            
            // Check attribute
            if (itemNumber.length() == 0) {
                // No item attribute, skip
                Log::debug("No '" + itemAttribute + "' attribute, ignoring.");
            } else {
                // Get item and add node
                result[atoi(itemNumber.c_str()) - 1] = child;
            }
        }

        childNode = child->getNextSibling();
        if (childNode != 0) {
            if (childNode->getNodeType() == DOMNode::ELEMENT_NODE) {
                child = dynamic_cast<DOMElement*>(childNode);
            } else {
                child = 0;
            }
        } else {
            child = 0;
        }
    }
}

void Utils::DOM::xmlExceptionOccured(const XMLException &ex) {
    ostringstream message;
    message << "XMLException Occured:\n" <<
        "\tfile: " << ex.getSrcFile() << "\n" <<
        "\tline: " << ex.getSrcLine() << "\n";

    char *errorMessage = XMLString::transcode(ex.getMessage());
    message << "Message is:\n" << errorMessage;

    Log::error(message.str());
    
    XMLString::release(&errorMessage);
}

void Utils::DOM::xmlExceptionOccured(const SAXException &ex) {
    char *message = XMLString::transcode(ex.getMessage());
    Log::error(string("SAXException Occured, Message is:\n") +
            message);
    XMLString::release(&message);
}

void Utils::DOM::xmlExceptionOccured(const DOMException &ex) {
    char *message = XMLString::transcode(ex.msg);
    Log::error(string("DOMException Occured, Message is:\n") +
            message);
    XMLString::release(&message);
}
