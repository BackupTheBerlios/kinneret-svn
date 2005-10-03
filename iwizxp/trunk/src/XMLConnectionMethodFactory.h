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

#ifndef __XML_CONNECTION_METHOD_FACTORY_H__
#define __XML_CONNECTION_METHOD_FACTORY_H__

#include <string>

#include "XMLConnectionMethod.h"
#include "Log.h"
#include "XMLCables.h"

/**
 * This class serves as a factory for creating connection methods out of
 * theis names.
 *
 * @author Itay 'z9u2k' Duvdevani
 */
class XMLConnectionMethodFactory {
public:

    /* --- Constructors ---- */

    /**
     * Destructor.
     *
     * Does nothing.
     */
    virtual ~XMLConnectionMethodFactory() {
        // Nothing to do
    }

    /* --- Public Methods --- */

    /**
     * The method creates a <code>ConnectionMethod</code> according to the
     * given name. After the instantiation, the created
     * <code>XMLConnectionMethod</code> is de-serialized from the given
     * element.
     *
     * @param name Name of the connection method.
     * @param element Element to de-serialize the method from.
     * @return An initialized <code>ConnectionMethod</code> on success, or
     *         <code>null</code> on failure.
     */
    static ConnectionMethod *create(const std::string name,
            xercesc::DOMElement *element);

private:

    /* --- Constants --- */

    /** Attribute value for cables method */
    static const std::string CABLES_NAME;
    
    /** Attribute value for ADSL method */
    static const std::string ADSL_NAME;
    
    /** Attribute value for ISDN method */
    static const std::string ISDN_NAME;
    
    /** Attribute value for dialup method */
    static const std::string DIALUP_NAME;
};

#endif
