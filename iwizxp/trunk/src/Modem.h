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

#ifndef __MODEM_H__
#define __MODEM_H__

#include <vector>
#include <map>

#include "NamedXMLReadable.h"
#include "KernelModule.h"
#include "Isp.h"
#include "Dialer.h"
#include "Exception.h"

/**
 * This class represents a modem. A modem knows whcih modules it needs in
 * order to work, and which dialer it should use.
 *
 * <b>About exceptions</b>:
 * Most modems work with a single dialer. There are some exceptional cases,
 * where a modem will require a different dialer when connectin to a certain
 * ISP (like Bezeqint, that might require an additional flag when dialing
 * with PPtP).
 *
 * @author duvduv
 */
class Modem : public NamedXMLReadable {
public:

    /* --- Constructors --- */

    /**
     * Constructor.
     *
     * @param name Modem's name.
     */
    Modem(const std::string name) : NamedXMLReadable(name) {
        // Nothing to do
    }

    /**
     * Constructor from XML.
     *
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    Modem(xercesc::DOMElement *root) : NamedXMLReadable() {
        fromXML(root);
    }

    /**
     * Destructor. Releases all allocated modules.
     */
    virtual ~Modem();

    /* --- Inner Types --- */

    NewException(DialerCreationException);

    /* --- Abstract Methods --- */

    /**
     * @param isp Selected ISP. Dialers my change due to the selected ISP
     *        (e.g. ADSL PPtP connection to Bezeq\@int is different than any
     *        other ISP).
     * @return The appropriate dialer. The dialer is allocated using
     *         <code>new</code> and it's up to the user to
     *         <code>delete</code> it.
     * @throws DialerCreationException When the desiered dialer could not have
     *        been created.
     */
    virtual Dialer *getDialer(Isp *isp);

    /* --- Public Methods --- */

    /**
     * @return List of modules that has to be probed.
     */
    virtual const std::vector<KernelModule*> &getKernelModules() const {
        return modulesVector;
    }

    /* --- Inherited from XMLReadable --- */

    /**
     * De-serializes from XML. Loads all the dialers and modules.
     *
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    void fromXML(xercesc::DOMElement *root);

protected:

    /* --- Protected Methods --- */

    /**
     * Helper method for adding required modules.
     *
     * @param module Required module. Note that this module should be
     *        allocated using <code>new</code> and will be released by this
     *        class.
     *
     * TODO: This is bad design, we might release something that was added
     * from the stack, e.g.:
     * <pre>
     * SomeFunkyModule module;
     * modem->addModule(&module);
     * </pre>.
     *
     * Making the user pass <code>new SomeFunkyModule()</code> is bad since
     * we can't enforce it.
     */
    void addModule(KernelModule *module) {
        modulesVector.push_back(module);
    }

    /**
     * Adds a dialer to the list of loaded dialers. This list will be
     * released during destruction.
     *
     * @param dialer A new dialer
     */
    void addDialer(Dialer *dialer) {
        loadedDialers.push_back(dialer);
    }

private:

    /* --- Utility Methods --- */

    /**
     * Loads the list of the required modules for the modem. Created a
     * <code>KernelModule</code> for every entry, and de-serializes from XML
     * using the item node as the root node of the module.
     *
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat or deserialization of the module failed.
     */
    void loadModulesFromXML(xercesc::DOMElement *root);
    
    /**
     * Loads the default dialer, and the exceptions, from XML.
     *
     * @param root Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    void loadDialersFromXML(xercesc::DOMElement *root);

    /**
     * Extracts the name of the default dialer from the tag, loads the dialer
     * and sets it as the default dialer for this modem.
     *
     * @param dialerNode node of the dialer we wish to load.
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    void loadDefaultDialer(xercesc::DOMElement *dialerNode);
    
    /**
     * Fills the exceptions map. Sorts the list, loads the dialers and puts
     * them in the map.
     *
     * @param dialerNode Root node of the object
     * @throws XMLSerializationException When the given XML is of incorrect
     *         fromat.
     */
    void loadExceptions(xercesc::DOMElement *dialerNode);

    /**
     * Loads a dialer by its name. <code>DialerLoader</code> takes the dialer
     * as a stream. This method creates the stream it requires, and invokes
     * to loading process.
     *
     * @param name Name of the dialer
     * @return An intizalizes dialer
     * @throws XMLSerializationException When the dialer failed to load.
     */
    Dialer *loadDialerByName(std::string name);

    /**
     * Releases kernel modules created by this modem.
     */
    void releaseKernelModules();

    /**
     * Releases dialers created by this modem.
     */
    void releaseDialers();

    /* --- Data Members --- */

    /** Default dialer to use, if the given ISP does not except */
    Dialer *defaultDialer;

    /** Map between exceptional ISPs and the matching dialers */
    std::map<std::string, Dialer*> exceptions;

    /** List of required modules */
    std::vector<KernelModule*> modulesVector;

    /** List of loaded dialers */
    std::vector<Dialer*> loadedDialers;
};

#endif
