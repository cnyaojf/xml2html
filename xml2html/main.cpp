/*
 * Name: main.cpp
 * Date: Nov 19, 2020
 * Author: Name1, Name2, COMPANY, name1@company.com
 * License: BSD licenses
 * Description:
 *     The main function to convert a .xml(ISO-8859-1) file to a.html file.
 *     We used tinyxml libs from 3rd party to finish xml parse functionality.
 * Revision History:
 *     1.0 Draft the main function.
 * Usage:
 *     Xml2Html [input.xml] [output.html]
 *         Input: ifname: a .xml; ofname: a .html file that will be created or truncated.
 *         Return: 0 if succeed, otherwise return -1.
 */

#include "xml2html.h"
#include <iostream>

using namespace std;

// The main function. For windows, the command is "Xml2Html [input.xml] [output.html]"
int main(int argc, char* argv[])
{
	// strings to store input and output file names.
    string ifname, ofname;

	// If the use does not intpu 3 parameters, display the usage.
	if (argc != 3) {
		cout << "Usage: Xml2Html [input.xml] [output.html] \n\n";
		cout << "Please input the .xml file name and output .html file name. The .html file \
                 will be created or truncated.\n";

		cout << "Input parameters: ";
		for (int i = 0; i < argc; ++i) {
			cout << argv[i] << ' ';
		}
		cout << endl;
		//	For test usage.  By default we can test cd_catalog.xml without input any parameters.
		// ifname = "cd_catalog.xml";
		// ofname = "cd_catalog.html";
		return 0;
	}
	else {
		ifname = argv[1];
		ofname = argv[2];
	}

	// If the input file is not .xml, return -1.
	if (ifname.size() < 4 || ifname.substr(ifname.size() - 4) != ".xml") {
		cout << "The input file name should be ended with .xml\n";
		return -1;
	}

	// If the output file is not .html, return -1.
	if (ofname.size() < 5 || ofname.substr(ofname.size() - 5) != ".html") {
		cout << "The out file name should be ended with .html\n";
		return -1;
	}

	// Convert the .xml to the .html file.  Return -1 if there is any issue.
	if (!Xml2Html::convert(ifname, ofname)) {
		cout << "The output file " << ofname << " failed to be generated.\n";
		return -1;
	}

	// Display the successful message to user.
	cout << "The output file " << ofname << " has been generated.\n";
	return 0;
}
