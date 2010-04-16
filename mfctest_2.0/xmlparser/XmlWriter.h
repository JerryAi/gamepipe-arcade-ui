/*
This class is used to make modification to the gameconfiguration.xml
*/
#ifndef XMLWRITER_H
#define XMLWRITER_H

#include "ParserBase.h"

class XmlWriter: public ParserBase
	{
		public:
			XmlWriter(string str_File): ParserBase(str_File)
				{
				}
			void AddGame(string str_Id , string str_Na , map<string , string> map_Keys);
			bool RemoveGame(string str_Id);
			bool RemoveKey(string str_OriginalKey , string str_Id);
			bool ChangKeyMap(string str_Original , string str_Correl , string str_Id);
			bool ChangNaOrID(string str_Opt , string str_Obj , string str_Id);//str_Opt should be either "name" or "id"
			bool AddKey(string str_Original , string str_Correl , string str_Id);
		private:
			void CreateElement(TiXmlElement* tiXmlElem, string str_Name , string str_Content);
	};

#endif