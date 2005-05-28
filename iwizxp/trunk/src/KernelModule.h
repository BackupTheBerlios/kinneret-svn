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

#include "Printable.h"

/** 
 * TODO 
 */
class KernelModule : public Printable {
public:

    /* --- Inner Types --- */

    /** 
     * TODO 
     */
    enum KernelClass {
        /** Linux 2.4 */
        LINUX2_4,

        /** Linux 2.6 */
        LINUX2_6
    };

    /* --- Constructors --- */

    /** 
     * TODO 
     */
    KernelModule() : Printable() {
    }

    /** 
     * TODO 
     */
    virtual ~KernelModule() {
    }

    /* --- Abstract Methods --- */

    /** 
     * TODO 
     */
    virtual std::string getName(KernelClass kernelClass) const = 0;
};

#endif
