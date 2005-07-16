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

#ifndef __WIZARD_LISTENER_H__
#define __WIZARD_LISTENER_H__

#include <string>
#include <vector>

/**
 * This interface should be implemented by the UI. Once the
 * <code>Wizard</code> starts, methods of this interface will be called by
 * it, to get information from the user.
 *
 * @author duvduv
 */
class WizardListener {
public:

    /* --- Constructors ---- */

    /**
     * Constructor.
     */
    WizardListener() {
        // Nothing to do
    }

    /**
     * Destructor.
     */
    virtual ~WizardListener() {
        // Nothing to do
    }

    /* --- Public Methods --- */

    // TODO
    virtual void fatal(std::string what) = 0;
    
    // TODO
    virtual int selectFromList(std::string what,
        std::vector<std::string> choises) = 0;

    // TODO
    virtual std::string requestString(std::string what) = 0;

    // TODO
    virtual void notify(std::string what) = 0;
};

#endif
