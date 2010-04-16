/*
This class is used to read xml from gameconfiguration.xml
*/
#ifndef XMLREADER_H
#define XMLREADER_H

#include "ParserBase.h"

class XmlReader: public ParserBase
	{
		public:
			XmlReader(string str_File): ParserBase(str_File)
				{
					tiXmlElem_Root = tiXmlDoc.RootElement();
					Init();
				}
			~XmlReader();
			map<string , string> FindConfByID(string);
		private:
			void Init();
			map< string , map<string , string> > map_ElemVal;
			TiXmlElement* tiXmlElem_Root;
			
	};

#endif