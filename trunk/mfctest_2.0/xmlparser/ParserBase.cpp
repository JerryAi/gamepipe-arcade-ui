#include "ParserBase.h"
#include <iostream>
/*
Name:ParserBase
Paramters:string str_File .This para specify the path of the file to be loaded
Return:void
Description:This is constructor load the xml file before other operation. It'll abort if fail to load the file
*/
ParserBase::ParserBase(string str_File)
{

		if(!tiXmlDoc.LoadFile(str_File.c_str()))
			{
				cout<<"Fail to load the xml file"<<endl;
				exit(1);
			}
}