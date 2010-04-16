#include "XmlReader.h"




XmlReader::~XmlReader()
{
	delete tiXmlElem_Root;
}
//Name:Init
//Parameter:void
//Return:void
//Description: Load the keys configuration from the xml file and store them into map_ElemVal
void XmlReader::Init()
	{
		TiXmlElement* tiXmlEle_GaConf = tiXmlElem_Root->FirstChildElement();
		while(NULL != tiXmlEle_GaConf)
		{
			TiXmlElement* tiXmlEle_Id = tiXmlEle_GaConf->FirstChildElement();
			TiXmlElement* tiXmlEle_Name = tiXmlEle_Id->NextSiblingElement();
			TiXmlElement* tiXmlEle_Keys = tiXmlEle_Name->NextSiblingElement();
			TiXmlElement* tiXmlEle_Key = tiXmlEle_Keys->FirstChildElement();
			TiXmlElement* tiXmlEle_Ori;
			TiXmlElement* tiXmlEle_Cor;
		
			string str_Id = string(tiXmlEle_Id->FirstChild()->Value());
			string str_Name = string(tiXmlEle_Name->FirstChild()->Value());
			map<string , string> map_Keys;
		
			while(NULL != tiXmlEle_Key)
			{
				tiXmlEle_Ori = tiXmlEle_Key->FirstChildElement();
				tiXmlEle_Cor = tiXmlEle_Ori->NextSiblingElement();
				map_Keys.insert(pair<string , string>(string(tiXmlEle_Ori->FirstChild()->Value()) , string(tiXmlEle_Cor->FirstChild()->Value())));
				tiXmlEle_Key = tiXmlEle_Key->NextSiblingElement();
			}
		
			map_ElemVal.insert(pair< string , map<string , string> >(str_Id , map_Keys));
			
			tiXmlEle_GaConf = tiXmlEle_GaConf->NextSiblingElement();
		}
		delete tiXmlEle_GaConf;
	}
//Name:FindConfByID
//Paramter:string str_Id
//Return:map<string , string>,this a map of key pairs
//Description:Return the key configuration according to the str_Id specified
map<string , string> XmlReader::FindConfByID(string str_Id)
	{
		map< string , map<string , string> >::iterator iter_Map = map_ElemVal.find(str_Id);
		if(map_ElemVal.end() != iter_Map)
			{
				return map_ElemVal[str_Id];
			}
		else
			{
				return map<string , string>();
			}
	}