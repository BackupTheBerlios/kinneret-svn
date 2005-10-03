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

#ifndef __TEXT_UI_H__
#define __TEXT_UI_H__

#include "WizardListener.h"

/**
 * This class makes the wizard a "text-mode" wizard by implementing a text
 * interface. By registering an instance of this class to a
 * <code>Wizard</code>, you will get a text-based application.
 * 
 * @author Itay 'z9u2k' Duvdevani
 */
class TextUI : public WizardListener {
public:

    /* --- Constructors ---- */

    /**
     * Constructor. Does nothing interesting.
     */
    TextUI() {
        // Nothing to do
    }

    /**
     * Destructor. Does nothing interesting.
     */
    virtual ~TextUI() {
        // Nothing to do
    }

    /* --- Public Methods --- */

    /**
     * Displayes a nasty string to <code>STDERR</code>.
     *
     * @param what The error message, supplied by the wizard.
     */
    void fatal(std::string what);
    
    /**
     * Displayes the list of options on the screen and asks the user for one.
     *
     * @param what Prompt, diplayed above the list.
     * @param choises List of choises.
     * @return Index of the selected option.
     */
    int selectFromList(std::string what,
        std::vector<std::string> choises);
    
    /**
     * Displayes a prompt to the screen and gets a string from the user from
     * <code>STDIN</code>.
     *
     * @param what The prompt
     * @return String from <code>STDIN</code>.
     */
    std::string requestString(std::string what);
    
    /**
     * Prints a message to <code>STDOUT</code>.
     *
     * @param what The message
     */ 
    void notify(std::string what);
};

#endif
