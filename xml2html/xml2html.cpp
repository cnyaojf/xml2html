/*
 * Name: xml2html.cpp
 * Date: Nov 19, 2020
 * Author: Name1, Name2, COMPANY, name1@company.com
 * License: BSD licenses
 * Description:
 *     The class provides a static function which uses tinyxml libararies to convert an input .xml
 *     into a .html file.
 *     We used tinyxml libs from 3rd party to finish xml parse functionality.
 *     The xml file should be encoded in ISO-8859-1.
 * Revision History:
 *     1.0 Draft the class implement to convert the input .xml file to an HTML file.
 * Usage:
 *     Xml2Html::convert(const string& ifname, const string& ofname);
 *         Input: ifname: a .xml; ofname: a .html file that will be created or truncated.
 *         Return: true if succeed, otherwise return false.
 */

#include <iostream>
#include <string>
#include <fstream>
#include "xml2html.h"
#include "./tinyxml/tinyxml.h"
#include "./tinyxml/tinystr.h"
#include <time.h>
#include <sstream>

using namespace std;

// Definition of static data members
unordered_set<string> Xml2Html::skeys;
vector<string> Xml2Html::keys;
vector<pair<string, unordered_map<string, string>>> Xml2Html::items;
string Xml2Html::catalog;

// Do nothing because no any data need be initialized
Xml2Html::Xml2Html() {	
}

// Do nothing because no any data need be released
Xml2Html::~Xml2Html() {
}

// convert(const string& ifname, const string& ofname)
// Input : ifname : a.xml; ofname: a.html file that will be created or truncated.
// Return: true if it succeeds, otherwise return false.
bool Xml2Html::convert(const string& ifname, const string& ofname)
{
	// If the interface is called twice, all the data should be cleared first.
	clear();

	// To parse the data from .xml and store them into internal data members
	if (parseXml(ifname) == false) {
		cout << "Failed to parse input file " << ifname << ".\n";
		return false;
	}

	// Use parsed data to create a .html file
	if (createHtml(ofname) == false) {
		cout << "Failed to generate output file " << ofname << ".\n";
		return false;
	}
	return true;
}

// To parse the data from .xml and store them into internal data members
// Input : ifname - a.xml to be parsed.
// Return: true if it succeeds, otherwise return false.
bool Xml2Html::parseXml(const string& ifname ) {
     TiXmlDocument doc(ifname.c_str());
     bool loadOkay = doc.LoadFile();

	 // Return false if parsing the xml file is failed.
     if (!loadOkay)
     {
         return false;
     }

     TiXmlNode* node = 0;
     TiXmlElement* datumElement = 0;

	 // For this case, we only care "CATALOG" parts and store it into catalog.
     node = doc.FirstChild("CATALOG");
	 catalog = node->Value();

	 // Get all elements one by one.  We stores the sequence of element types(TITLE, ARTIST, ...) 
	 // so that we can show them in sequence in the HTML file.
     for (node = node->FirstChildElement(); node != nullptr; node = node->NextSibling())
     {
		 pair<string, unordered_map<string, string>> cd;
		 cd.first = node->Value();
         for (auto p = node->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
			 if( skeys.find(p->Value()) == skeys.end() ) {
				 skeys.insert(p->Value());
				 keys.push_back(p->Value());
			 }             
             cd.second[p->Value()] = p->FirstChild()->Value();
         }
         items.push_back(cd);
     }
     return true;

}

// 
// To creat the html file with parsed data from the xml file.
// Input : ofname - a.html to be created.
// Return: true if it succeeds, otherwise return false.
bool Xml2Html::createHtml(const string& ofname) {
	const int headgap = 2;
	const int bodygap = 2;
	const int indentgap = 2;
	const int h1gap = bodygap + indentgap;
	const int h2gap = bodygap + indentgap;
	const int tablegap = bodygap + indentgap;
	const int tableitemgap = tablegap + indentgap;

	string tabletext{ "<!doctype html>\n<html>\n" };
	tabletext += string(headgap, ' ') + "<head>\n";
	tabletext += string(headgap, ' ') + "<meta charset = \"ISO-8859-1\">";
	tabletext += string(headgap, ' ') + "<style>\n";
	tabletext += string(headgap + indentgap, ' ') + "table, th, td{\n";
	tabletext += string(headgap + indentgap * 2, ' ') + "border: 1px solid black;\n";
	tabletext += string(headgap + indentgap * 2, ' ') + "border - collapse: collapse;}\n";
	tabletext += string(headgap, ' ') + "</style>\n";
	tabletext += string(headgap, ' ') + "</head>\n";
	tabletext += string(bodygap, ' ') + "<body>\n";
	tabletext += string(h1gap, ' ') + "<h1>\n" + string(h1gap + indentgap, ' ') + catalog + '\n' + string(h1gap, ' ') + "</h1>\n";
    
	if (items.size() != 0) {
		tabletext += string(tablegap, ' ' ) + "<table>\n";
		tabletext += string(tablegap + indentgap, ' ') + "<thead>\n";
		tabletext += string(tablegap + indentgap * 2, ' ') + "<tr><th></th>";
		for (auto& x : keys) {
			tabletext += "<th>";
			tabletext += x;
			tabletext += "</th>";
		}

		tabletext += "</tr>\n";

		tabletext += string(tablegap + indentgap, ' ') + "</thead>\n";
		tabletext += string(tablegap + indentgap, ' ') + "<tbody align=\"center\">\n";
		for (auto& x : items) {
			tabletext += string(tableitemgap + indentgap, ' ') + "<tr>";
			tabletext += "<td>" + x.first + "</td>";
			for (auto& y : keys) {
				tabletext += "<td>";
				if (x.second.find(y) != x.second.end()) {
					tabletext += x.second[y];
				}
				tabletext += "</td>";
			}
			tabletext += "</tr>\n";
		}

	    tabletext += string(tablegap + indentgap, ' ' ) + "</tbody>\n";
	    tabletext += string(tablegap, ' ') + "</table>\n";
	}
	tabletext += string(bodygap, ' ') + "</body>\n";
	tabletext += "</html>\n";
	try {
		std::ofstream htmltable(ofname, std::ios::out | std::ios::trunc);
		htmltable << tabletext;
		htmltable.close();
	}
	catch (...) {
		return false;
	}
    return true;
}


// Reset all data members.
void Xml2Html::clear() {
	skeys.clear();
	keys.clear();
	items.clear();
	catalog.clear();
}
