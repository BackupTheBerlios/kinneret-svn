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

#ifndef __PSUDO_ETHERNET_USB_MODULE_H__
#define __PSUDO_ETHERNET_USB_MODULE_H__

#include "KernelModule.h"

/** 
 * TODO 
 */
class PsudoEthernetUsbModule : public KernelModule {
public:

    /* --- Constructors --- */

    /** 
     * TODO 
     */
    PsudoEthernetUsbModule() : KernelModule() {
    }

    /** 
     * TODO 
     */
    virtual ~PsudoEthernetUsbModule() {
    }

    /* --- Inherited from Printable --- */

    /** 
     * TODO 
     */
    virtual const std::string toString() const {
        return "Psudo ethernet USB modem";
    }

    /* --- Inherited from KernelModule --- */

    /** 
     * TODO 
     */
    virtual std::string getName(KernelClass kernelClass) const {
        switch (kernelClass) {
        case KernelModule::LINUX2_4:
            return "CDCEther";

        case KernelModule::LINUX2_6:
            return "usbnet";

        default:
            // TODO
            break;
        }
    }
};

#endif
