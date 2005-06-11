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

#include "Printable.h"
#include "KernelModule.h"
#include "Isp.h"
#include "Dialer.h"
#include "Exception.h"

/**
 * This abstact class represents a modem class, that knows which modules it
 * needes and hot to set it appropriately.
 *
 * @author duvduv
 */
class Modem : public Printable {
public:

    /* --- Constructors --- */

    /**
     * Constructor.
     *
     * @param name Modem's name.
     */
    Modem(std::string name) : Printable() {
        this->name = name;
    }

    /**
     * Destructor. Releases all allocated modules.
     */
    virtual ~Modem();

    /* --- Inner Types --- */

    NewException(DialerCreationException);

    /* --- Abstract Methods --- */

    /**
     * @return <code>true</code> if the current modem requires special
     *         modules to be loaded to the kernel, or <code>false</code>
     *         otherwise.
     */
    virtual bool needModules() const = 0;

    /**
     * @param isp Selected ISP. Dialers my change due to the selected ISP
     *        (e.g. ADSL PPtP connection to Bezeq\@int is different than any
     *        other ISP).
     * @return The appropriate dialer. The dialer is allocated using
     *         <code>new</code> and it's up to the user to
     *         <code>delete</code> it.
     * @throw DialerCreationException When the desiered dialer could not have
     *        been created.
     */
    virtual Dialer *getDialer(Isp *isp) throw (DialerCreationException) = 0;

    /* --- Public Methods --- */

    /**
     * @return List of modules that has to be probed.
     */
    virtual std::vector<KernelModule*> getKernelModules() const {
        return modulesVector;
    }

    /**
     * @return Modem's name.
     */
    virtual const std::string getName() const {
        return name;
    }

    /* --- Inherited from Printable --- */

    /**
     * @return Modem's name.
     */
    virtual const std::string toString() const {
        return getName();
    }

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
     * Releases kernel modules created by this modem.
     */
    void releaseKernelModules();

    /**
     * Releases dialers created by this modem.
     */
    void releaseDialers();

    /* --- Data Members --- */

    /** Modem's name */
    std::string name;

    /** List of required modules */
    std::vector<KernelModule*> modulesVector;

    /** List of loaded dialers */
    std::vector<Dialer*> loadedDialers;
};

#endif
