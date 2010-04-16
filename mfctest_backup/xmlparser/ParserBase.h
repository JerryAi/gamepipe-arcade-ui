/*
These xml parser tools are all based on tinyxml library. All the necessary files are uploaded on to the google code
This class is the base class. It helps the subclassess load the xml files
*/
#ifndef PARSERBASE_H
#define PARSERBASE_H

#include "tinyxml.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

class ParserBase
{
	public:
		ParserBase(string);
		
	protected:
		TiXmlDocument tiXmlDoc;
};

#endif