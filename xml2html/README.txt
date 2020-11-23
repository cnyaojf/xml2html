Name: xml2html package
Date: Nov 19, 2020
Author: Name1, Name2, COMPANY, name1@comany.com
License: BSD licenses

Description:
    The application converts elements under “CATALOG” of a .xml(ISO-8859-1) file to a.html file as a "table" element.
    We used tinyxml 2.6.2 libs(https://versaweb.dl.sourceforge.net) from 3rd party to finish xml parse functionality.
    The application only supports xml files in ASCII format.
    All elements under “CATALOG” will be retrieved and displayed one by one in html tables.

Revision History:
    1.0 The first version to convert a .xml file to a.html file as a "table" element.

Usage:
    xml2html.exe [input.xml] [output.html] e.g., “xml2html cd_catalog.xml cd_catalog.html”.
        Input: ifname: a .xml; ofname: a .html file that will be created or truncated.
        Return: 0 if succeed, otherwise return -1.

Design Description: 
  Added files: 
      ./main.cpp - The command line to input .xml file and output .html file.
      ./xml2html.cpp – The implement of a class which provides static functions to covert the files.
      ./xml2html.h – The header files.
  Included 3rd party files from tinyxml library are saved under ./tinyxml:
      tinystr.cpp         tinystr.h           tinyxml.cpp         tinyxml.h
      tinyxmlerror.cpp    tinyxmlparser.cpp   xmltest.cpp
1. Introduce a class to handle the convert functions, which will parse xml into internal data, then create a html file.
2. Only one public static function convert(ifname, ofname) is provided to callers. All other data and functions members in this class are private. Choosing static function is because it can be called without creating an instance.
3. Use hash table unordered_map to store <key, value> like “< ARTIST, Joe Cocker> and get O(1) in enquiry(e.g. value = map[key])
4. Will keep all the keys (TITLE, ARTIST, COMPANY, …) in the same sequence of they are parsed at the first time. A hash table unordered_set is introduced to make sure a key only is inserted once and keep its sequence in a vector.
5. Only ASCII characters are supported as the input xml file is encoded in ISO-8859-1.
6. 3rd party tinyxml lib is selected because its interface is simple and all the source code can be retrieved.
  
Build & Debug Environment:
    Windows 10
    Microsoft Visual Studio Community 2019
    Steps:
    1. Extract xml2html.zip file to local files.
    2. Open the project file xml2html.sln to Visual Studio.
    3. Compile and link.  
    Expected result: output file xml2html.exe is under ./Debug.
    
Test Environment:
    Windows 10
    Microsoft Visual Studio Community 2019
    Directory of test files and output files: ./test
    The following test cases has passed.
    Steps:
    1. cd ./Debug.
    2. Copy cd_catalog.xml to ./Debug directory.
    3. Edit cd_catalog.xml and delete some tags to make it inconsistent and save as cd_catalog_wrong.xml.
      TC-1. Try command “xml2html cd_catalog.xml cd_catalog.html”
      Expected result: cd_catalog.html can be shown and all items are display in table format.
      TC-2. Try command “xml2html cd_catalog_wrong.xml cd_catalog.html”
      Expected result: return -1. The html file cannot be parsed and report a wrong notice.
      TC-3. Try command “xml2html”
      Expected result: usage information will be displayed.
      TC-4. Try command “xml2html invalid output.html”
      Expected result: return -1 and reported the xml file is invalid.
      TC5-TCN: Try the xml files with 0 element, 1 element, 2, and 3 elements, and verify html table is correct.
          cd_catalog_0_element.xml
          cd_catalog_1_element.xml
          cd_catalog_1_element_blank_cd.xml
    cd_catalog_2_elements.xml
    cd_catalog_3_elements.xml
    cd_catalog_no_catalog.xml
------THE END------
