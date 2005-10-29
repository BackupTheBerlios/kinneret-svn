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

#ifndef __XML_CONNECTION_TEMPLATE_LOADER_H__
#define __XML_CONNECTION_TEMPLATE_LOADER_H__

#include "ConnectionTemplateLoader.h"

/**
 * TODO: JavaDocs
 *
 * @author Itay 'z9u2k' Duvdevani
 */
class XMLConnectionTemplateLoader : public ConnectionTemplateLoader {
public:

	/* --- Constructors ---- */

	/**
	 * Constructor.
	 * TODO: JavaDocs
	 */
	XMLConnectionTemplateLoader() {
		// Nothing to do
	}

	/**
	 * Destructor.
	 * TODO: JavaDocs
	 */
	virtual ~XMLConnectionTemplateLoader() {
		// Nothing to do
	}

	/* --- Public Methods --- */

	/**
	 * TODO: JavaDocs
	 *
	 * @throws LoadException
	 */
	virtual ConnectionTemplate *loadConnectionTemplate(
		std::istream &inStream) const;
};

#endif
