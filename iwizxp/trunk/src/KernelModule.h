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

#ifndef __KERNEL_MODULE_H__
#define __KERNEL_MODULE_H__

#include <map>

#include "Nameable.h"
#include "Exception.h"

/** 
 * This abstract class represents a kernel modules which should be loaded for
 * the connection to succeede.
 *
 * The class provides abstractation above the module name. Implementaing
 * classes should provide the module name for the 2.4 and 2.6 kernels.
 *
 * TODO: Add support for arguments.
 * TODO: Explain why Nameable is a virtual base.
 *
 * @author duvduv
 */
class KernelModule : public virtual Nameable {
public:

    /* --- Inner Types --- */

    /** 
     * Enumerates supported kernels.
     */
    enum KernelClass {
        /** Linux 2.4 */
        LINUX2_4,

        /** Linux 2.6 */
        LINUX2_6
    };

    /* --- Constructors --- */

    /** 
     * Destructor.
     */
    virtual ~KernelModule() {
        // Nothing to do.
    }

    /* --- Exceptions --- */

    /**
     * Thrown if this module is unsupported by the selected kernel.
     */
    NewException(FeatureNotSupportedException);

    /* --- Getters --- */

    /** 
     * Decides what's the module name the given kernel class supports.
     * 
     * @param kernelClass The kernel class we're interested in.
     * @return The name of the modules that has to be <i>modprobe</i>d with
     *         the given kernel.
     * @throws FeatureNotSupportedException When the given kernel class does
     *         not support this module.
     */
    virtual std::string getName(KernelClass kernelClass) const;

protected:

    /* --- Access Methods --- */

    /**
     * Adds a new name for a specific kernel class.
     *
     * @param kernelClass Class
     * @param name Name of the module in that class
     */
    void addName(KernelClass kernelClass, const std::string name) {
        names[kernelClass] = name;
    }

private:

    /* --- Data Members --- */

    /** Maps between kernel class and the name of the module in that class  */
    std::map<KernelClass, std::string> names;
};

#endif
