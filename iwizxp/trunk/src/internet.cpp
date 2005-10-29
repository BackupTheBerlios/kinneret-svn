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

#include <getopt.h>

#include "Wizard.h"
#include "TextUI.h"
#include "Log.h"

using namespace std;

void usage() {
	cout << 
"Usage: iwizxp [-l <level>] [-v] [-h]\n\n"
"Options:\n"
"        --log, -l               Log level. One of: all, debug, info,\n"
"                                warning, error, bug, fatal or none.\n"
"                                Default log level is info.\n"
"        --version, -v           Display version info and exit.\n"
"        --help, -h              This help screen\n" << endl;
	exit(0);
}

void version() {
	cout << "iwizxp testing build - not for release" << endl << endl;
	exit(0);
}

void handleLogOption(string level) {
	try {
		Log::release();
		Log::create(Log::levelFromString(level));
		Log::debug(LOG_LOCATION("<global>", "handleLogOption"),
			"Logger created successfully");
	} catch (Log::FormatException &ex) {
		cout << ex.what() << endl;
		usage();
	}
}

int getOptions(int argc, char *argv[]) {
	while (true) {
		static struct option long_options[] = {
			{"log",     1, 0, 'l'},
			{"version", 0, 0, 'v'},
			{"help",    0, 0, 'h'},
			{0, 0, 0, 0}
		};

		int option_index = 0;
		int c = getopt_long(argc, argv, "l:vh", long_options,
			&option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
		case 'l':
			handleLogOption(optarg);
			break;

		case 'v':
			version();
			break;

		case 'h':
			usage();
			break;

		default:
		case '?':
			usage();
			break;
		}
	}
}

int main(int argc, char *argv[]) {
	// Default log level is info
	Log::create(Log::INFO);

	// Get command line options
	getOptions(argc, argv);

	// Do the wizard
	Wizard wizard;
	TextUI ui;

	wizard.setListener(&ui);
	int result = wizard.go();

	Log::release();

	return result;
}

