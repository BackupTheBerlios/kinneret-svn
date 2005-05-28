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

/**
 * TODO
 */
class Modem : public Printable {
public:

    /* --- Constructors --- */

    /**
     * TODO
     */
    Modem(std::string name) : Printable() {
        this->name = name;
    }

    /**
     * TODO
     */
    virtual ~Modem();

    /* --- Abstract Methods --- */

    /**
     * TODO
     */
    virtual bool needModules() const = 0;

    /**
     * TODO
     */
    virtual const Dialer *getDialer(Isp *isp) const = 0;

    /* --- Public Methods --- */

    /**
     * TODO
     */
    virtual void getKernelModules(std::vector<KernelModule*> &targetVector)
            const {
        targetVector.clear();
        targetVector.assign(modulesVector.begin(), modulesVector.end());
    }

    /**
     * TODO
     */
    virtual const std::string getName() const {
        return name;
    }

    /* --- Inherited from Printable --- */

    /**
     * TODO
     */
    virtual const std::string toString() const {
        return getName();
    }

protected:

    /* --- Protected Methods --- */

    /**
     * TODO
     */
    void addModule(KernelModule *module) {
        modulesVector.push_back(module);
    }

private:

    /* --- Data Members --- */

    /** TODO */
    std::string name;

    /** TODO */
    std::vector<KernelModule *> modulesVector;
};

#endif
