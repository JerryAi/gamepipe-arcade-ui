#pragma warning(disable:4996)
#include "XmlWriter.h"
#include <stdlib.h>
//Name:AddGame
//Paramter:string str_Id , string str_Name , map<string , string> map_Keys
//Return:void
//Description:add a game block and store the key pairs ,id and name into it
void XmlWriter::AddGame(string str_Id , string str_Name , map<string , string> map_Keys)
	{
		TiXmlElement* tiXmlElem_Root = tiXmlDoc.RootElement();
		TiXmlElement* tiXmlElem_GaConf = new TiXmlElement("gameconf");
		tiXmlElem_Root->LinkEndChild(tiXmlElem_GaConf);
		
		TiXmlElement* tiXmlElem_Id = new TiXmlElement("");
		TiXmlElement* tiXmlElem_Name = new TiXmlElement("");
		CreateElement(tiXmlElem_Id , string("id") , str_Id);
		CreateElement(tiXmlElem_Name , string("name") , str_Name);
		
		tiXmlElem_GaConf->LinkEndChild(tiXmlElem_Id);
		tiXmlElem_GaConf->LinkEndChild(tiXmlElem_Name);
		
		TiXmlElement* tiXmlElem_Key = new TiXmlElement("keys");
		
		map<string , string>::iterator iter_Map = map_Keys.begin();
		int int_Count = 1;
		while(map_Keys.end() != iter_Map)
		{
			char a[3];
			itoa(int_Count , a , 10);
			string str_Num = string(a);
			string str_KeyNum = string("key");
			//str_KeyNum.append(str_Num);
			
			TiXmlElement* tiXmlElem_Keys = new TiXmlElement(str_KeyNum.c_str());
			
			TiXmlElement* tiXmlElem_Ori = NULL;
			TiXmlElement* tiXmlElem_Cor = NULL;
			
			CreateElement(tiXmlElem_Ori , string("origin") , iter_Map->first);
			CreateElement(tiXmlElem_Cor , string("correl") , iter_Map->second);
			
			tiXmlElem_Keys->LinkEndChild(tiXmlElem_Ori);
			tiXmlElem_Keys->LinkEndChild(tiXmlElem_Cor);
			
			tiXmlElem_Key->LinkEndChild(tiXmlElem_Keys);
			
			iter_Map++;
			int_Count++;
		}
		
		tiXmlElem_GaConf->LinkEndChild(tiXmlElem_Key);
		tiXmlDoc.SaveFile("gameconfiguration.xml");

	}

//Name:RemoveGame
//Paramter:string str_Id
//Return:true if it succeeds ,false if it fails
//Description:Remove a block of game according to id specified	
bool XmlWriter::RemoveGame(string str_Id)
	{
		TiXmlElement* tiXmlElem_Root = tiXmlDoc.RootElement();
		TiXmlElement* tiXmlElem_GameConf = tiXmlElem_Root->FirstChildElement();
		while(NULL != tiXmlElem_GameConf)
		{
			string str_NodeID = string(tiXmlElem_GameConf->FirstChildElement()->FirstChild()->Value());
			if(0 == str_NodeID.compare(str_Id))
				{
					break;
				}
			tiXmlElem_GameConf = tiXmlElem_GameConf->NextSiblingElement();
		}
		
		if(NULL != tiXmlElem_GameConf)
			{
				tiXmlElem_Root->RemoveChild(tiXmlElem_GameConf);
				tiXmlDoc.SaveFile("gameconfiguration.xml");
				return true;
			}
		else
			{
				return false;
			}
	}	

//Name:RemoveKey
//Paramter:string str_OriginalKey , string str_Id
//Return:true if it succeeds ,false if it fails
//Description:Remove a key pair according to teh original key and id specified
bool XmlWriter::RemoveKey(string str_OriginalKey , string str_Id)
	{
		TiXmlElement* tiXmlElem_Root = tiXmlDoc.RootElement();
		TiXmlElement* tiXmlElem_GameConf = tiXmlElem_Root->FirstChildElement();
		TiXmlElement* tiXmlElem_Origin = NULL;
		bool find = false;
		while(NULL != tiXmlElem_GameConf)
		{
			string str_NodeID = string(tiXmlElem_GameConf->FirstChildElement()->FirstChild()->Value());
			if(0 == str_NodeID.compare(str_Id))
				{
					TiXmlElement* tiXmlElem_Keys = tiXmlElem_GameConf->FirstChildElement()->NextSiblingElement()->NextSiblingElement();//locate the pointer onto the keys mark
					tiXmlElem_Origin = tiXmlElem_Keys->FirstChildElement();
					while(NULL != tiXmlElem_Origin)
					{
						string str_Ori = string(tiXmlElem_Origin->FirstChild()->Value());
						if(0 == str_Ori.compare(str_OriginalKey))
							{
								tiXmlElem_Keys->RemoveChild(tiXmlElem_Origin);
								tiXmlDoc.SaveFile("gameconfiguration.xml");
								return true;
							}
					}
				}
			tiXmlElem_GameConf = tiXmlElem_GameConf->NextSiblingElement();
		}
		
		return false;
	}

//Name:ChangKeyMap
//Paramter:string str_Original , string str_Correl , string str_Id
//Return:true if it succeeds ,false if it fails
//Description:Modify the mapping result according to the original key and game id specified
bool XmlWriter::ChangKeyMap(string str_Original , string str_Correl , string str_Id)
	{
		TiXmlElement* tiXmlElem_Root = tiXmlDoc.RootElement();
		TiXmlElement* tiXmlElem_GameConf = tiXmlElem_Root->FirstChildElement();
		TiXmlElement* tiXmlElem_Origin = NULL;
		bool find = false;
		while(NULL != tiXmlElem_GameConf)
		{
			string str_NodeID = string(tiXmlElem_GameConf->FirstChildElement()->FirstChild()->Value());
			if(0 == str_NodeID.compare(str_Id))
				{
					TiXmlElement* tiXmlElem_Keys = tiXmlElem_GameConf->FirstChildElement()->NextSiblingElement()->NextSiblingElement();//locate the pointer onto the keys mark
					tiXmlElem_Origin = tiXmlElem_Keys->FirstChildElement();
					while(NULL != tiXmlElem_Origin)
					{
						string str_Ori = string(tiXmlElem_Origin->FirstChild()->Value());
						if(0 == str_Ori.compare(str_Original))
							{
								//tiXmlElem_Keys->RemoveChild(tiXmlElem_Origin);
								tiXmlElem_Origin->NextSiblingElement()->FirstChild()->SetValue(str_Correl.c_str());
								tiXmlDoc.SaveFile("gameconfiguration.xml");
								return true;
							}
					}
				}
			tiXmlElem_GameConf = tiXmlElem_GameConf->NextSiblingElement();
		}
		
		return false;
	}

//Name:AddKey
//Paramter:string str_Original , string str_Correl , string str_Id
//Return:true if it succeeds ,false if it fails
//Description:add a pair of keys with original and the mapping one into a block specified by str_Id
bool XmlWriter::AddKey(string str_Original , string str_Correl , string str_Id)
	{
		TiXmlElement* tiXmlElem_Root = tiXmlDoc.RootElement();
		TiXmlElement* tiXmlElem_GameConf = tiXmlElem_Root->FirstChildElement();
		TiXmlElement* tiXmlElem_Origin = new TiXmlElement("");
		TiXmlElement* tiXmlElem_Correl = new TiXmlElement("");
		TiXmlElement* tiXmlElem_Key = new TiXmlElement("key");
		
		CreateElement(tiXmlElem_Origin , string("origin") , str_Original);
		CreateElement(tiXmlElem_Correl , string("correl") , str_Correl);
		
		tiXmlElem_Key->LinkEndChild(tiXmlElem_Origin);
		tiXmlElem_Key->LinkEndChild(tiXmlElem_Correl);
		
		while(NULL != tiXmlElem_GameConf)
		{
			string str_NodeID = string(tiXmlElem_GameConf->FirstChildElement()->FirstChild()->Value());
			if(0 == str_NodeID.compare(str_Id))
				{
					TiXmlElement* tiXmlElem_Keys = tiXmlElem_GameConf->FirstChildElement()->NextSiblingElement()->NextSiblingElement();//locate the pointer onto the keys mark
					tiXmlElem_Keys->LinkEndChild(tiXmlElem_Key);
					tiXmlDoc.SaveFile("gameconfiguration.xml");
					return true;
				}
			tiXmlElem_GameConf = tiXmlElem_GameConf->NextSiblingElement();
		}
		return false;
	}
	
//Name:ChangNaOrID
//Paramter:string str_Opt , string str_Obj , string str_Id
//Return:true if it succeeds ,false if it fails
//Description:Modify id or name for every block it specifies by str_Id
bool XmlWriter::ChangNaOrID(string str_Opt , string str_Obj , string str_Id)
	{
		TiXmlElement* tiXmlElem_Root = tiXmlDoc.RootElement();
		TiXmlElement* tiXmlElem_GameConf = tiXmlElem_Root->FirstChildElement();
		TiXmlElement* tiXmlElem_Id = NULL;
		TiXmlElement* tiXmlElem_Name = NULL;
		
		while(NULL != tiXmlElem_GameConf)
		{
			string str_NodeID = string(tiXmlElem_GameConf->FirstChildElement()->FirstChild()->Value());
			tiXmlElem_Id = tiXmlElem_GameConf->FirstChildElement();
			tiXmlElem_Name = tiXmlElem_Id->NextSiblingElement();
			if(0 == str_NodeID.compare(str_Id))
				{
					if(0 == string("id").compare(str_Opt))
						{
							tiXmlElem_Id->FirstChild()->SetValue(str_Obj.c_str());
							tiXmlDoc.SaveFile("gameconfiguration.xml");
							return true;
						}
					else if(0 == string("name").compare(str_Opt))
						{
							tiXmlElem_Name->FirstChild()->SetValue(str_Obj.c_str());
							tiXmlDoc.SaveFile("gameconfiguration.xml");
							return true;
						}
					else
						{
							return false;
						}
				}
			tiXmlElem_GameConf = tiXmlElem_GameConf->NextSiblingElement();

		}
		
		return false;
	}

//Name:CreateElement
//Paramter:TiXmlElement* TiXmlElem, string str_Name , string str_Content
//Return:void
//Description:create an element to make this repeating job easy
void XmlWriter::CreateElement(TiXmlElement* TiXmlElem, string str_Name , string str_Content)
	{
		TiXmlElem->SetValue(str_Name.c_str());
		TiXmlText* tiXmlTx_Content = new TiXmlText(str_Content.c_str());
		TiXmlElem->LinkEndChild(tiXmlTx_Content);//should check how does linkendchild work to avoid memory leak
	}