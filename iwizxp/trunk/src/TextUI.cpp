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

#include <iostream>

#include "TextUI.h"

using namespace std;

void TextUI::fatal(string what) {
	cerr << "---------- FATAL ----------" << endl <<
		what << endl;
}

int TextUI::selectFromList(string what, vector<string> choises) {
	int selection, i;

	do {
		cout << what << endl;
		for (i = 0 ; i < choises.size() ; i++) {
			cout << (i + 1) << ") " << choises[i] << endl;
		}

		if (i > 1) {
			cout << "Selection [1-" << i << "]: ";
			cin >> selection;
		} else {
			selection = 1;
			cout << "One-choise, auto-selected." << endl;
		}

		cout << endl;
	} while ((selection <= 0) || (selection > choises.size()));

	// Selection is one-based, but vetor's index is zero based.
	return (selection - 1);
}

string TextUI::requestString(string what) {
	string result;

	do {
		cout << what;
		cin >> result;
	} while (result.length() == 0);

	return result;
}

void TextUI::notify(string what) {
	cout << what << endl;
}

