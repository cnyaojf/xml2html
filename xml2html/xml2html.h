/*
 * Name: xml2html.h
 * Date: Nov 19, 2020
 * Author: Name1, Name2, COMPANY, name1@company.com
 * License: BSD licenses
 * Description:
 *     The class provides a static function which uses tinyxml libararies to convert an input .xml into a .html file.
 *     The xml file should be encoded in ISO-8859-1.
 *     We used tinyxml libs from 3rd party to finish xml parse functionality.
 * Revision History:
 *     1.0 Draft the class header file to convert the input .xml file to an HTML file.
 * Usage:
 *     Xml2Html::convert(const string& ifname, const string& ofname);
 *         Input: ifname: a .xml; ofname: a .html file that will be created or truncated.
 *         Return: true if succeed, otherwise return false.
 */

#ifndef XML_2_HTML_H
#define XML_2_HTML_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Xml2Html {
public:
    // convert(const string& ifname, const string& ofname)
    // Input : ifname : a.xml; ofname: a.html file that will be created or truncated.
    // Return : true if it succeeds, otherwise return false.
    static bool convert(const string& ifname, const string& ofname);
    
private:
    // Both construction and ~Xml2Html are private becaues the use can call static convert() directly
    Xml2Html();  //  Do nothing
    ~Xml2Html(); //  Do nothing

    // A function to parse xml using tinyxml. Return true if it succeeds, otherwise return false.
    static bool parseXml(const string& ifname );  

    // to create the .html file with xml contents. Return true if it succeeds, otherwise return false.
    static bool createHtml(const string& ofname); 
    
    // If the generate function is called twice, the former data will be cleared and new data will be used.
    static void clear(); 
   
    // An unordered set to store properties(TITLE, ARTIST, etc.) so that unique property will be stored.
    // The searching complexity is O(1) for each find(value) call.
    static unordered_set<string> skeys; 

    // To store keys(TITLE, ARTIST, etc.) uniquely and in sequence.
    static vector<string> keys;

    // To store all CD informations.  First is "CD", and the map stores its key pairs.
    // Using unordered_map to O(1) in searching(call item[TITLE] complexity.
    static vector<pair<string,unordered_map<string, string>>> items;

    // To store the catalog for html file.  For cd_catalog.xml it is value is "CATALOG".
    static string catalog;
};

#endif // XML_2_HTML_H
