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
 * This psudo-module is the module that has to be loaded in order to obtain
 * the psudo-ethernet interface that bridges between the USB-connected modem
 * and the ethernet device required by pppd.
 *
 * This modules is supported by 2.4 and 2.6 kernels.
 *
 * @author duvduv.
 */
class PsudoEthernetUsbModule : public KernelModule {
public:

    /* --- Constructors --- */

    /** 
     * Constructor.
     */
    PsudoEthernetUsbModule() : KernelModule() {
        Log::debug("PsudoEthernetUsbModule created successfully");
    }

    /** 
     * Destructor.
     */
    virtual ~PsudoEthernetUsbModule() {
        Log::debug("PsudoEthernetUsbModule released successfully");
    }

    /* --- Inherited from Printable --- */

    /** 
     * @returns Descriptive name of this psudo-module.
     */
    virtual const std::string toString() const {
        return "Psudo ethernet USB modem";
    }

    /* --- Inherited from KernelModule --- */

    /** 
     * @return the module that has to be <i>modprobe</i>d in the selected
     *         kernel class. <code>CDCEther</code> for 2.4, and
     *         <code>usbnet</code> for 2.6.
     */
    virtual std::string getName(KernelClass kernelClass) const
            throw (FeatureNotSupportedException) {
        switch (kernelClass) {
        case KernelModule::LINUX2_4:
            return "CDCEther";

        case KernelModule::LINUX2_6:
            return "usbnet";

        default:
            throw FeatureNotSupportedException(
                "Module is supported by Linux 2.4 and 2.6.");
        }
    }
};

#endif
