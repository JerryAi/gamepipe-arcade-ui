#include<windows.h>
#include<stdio.h>
#include"WinIo.h"
#include <iostream>


#define KBC_CMD 0x64
#define KBC_DATA 0x60

void KBCWait4IBE()
{
DWORD dwVal=0;
do
{
        GetPortVal(KBC_CMD,&dwVal,1);
}
while((&dwVal)&&(0x2)==0);
//while((dwVal)&(0x2)==0);
//while(!(dwVal   &   0x1));
}

 void   kbcWait4OBF()   
 {   
  DWORD   dwVal=0;   
  do   
  {   
  GetPortVal(KBC_CMD,&dwVal,1);   
  }   
  while(!(dwVal   &   0x1));   
}   

void KEY_DOWN(int vk_in)
{
int myscancode;
myscancode=MapVirtualKey(byte(vk_in),0);
//std::cout<<char(myscancode)<<std::endl;
KBCWait4IBE();
SetPortVal(KBC_CMD,0xD2,1);
KBCWait4IBE();
SetPortVal(KBC_DATA,0xE2,1);
KBCWait4IBE();
SetPortVal(KBC_CMD,0xD2,1);
KBCWait4IBE();
SetPortVal(KBC_DATA,myscancode,1); 
}
void KEY_UP(int vk_in)
{
int myscancode;
myscancode=MapVirtualKey(byte(vk_in),0);
KBCWait4IBE();
SetPortVal(KBC_CMD,0xD2,1);
KBCWait4IBE();
SetPortVal(KBC_DATA,0xE0,1);
KBCWait4IBE();
SetPortVal(KBC_CMD,0xD2,1);
KBCWait4IBE();
SetPortVal(KBC_DATA,(myscancode|0x80),1);

}

void main()
{
    bool br,br1;
    //br=InitializeWinIo(); //in NT/XP no need
    //if (br==false)
    //{
// MessageBox(NULL,"初始化winio失败,程序自动关闭,请您不用担心~","XD友情提示1",MB_OK);
// ShutdownWinIo();
// exit(0);
    //}
    br1=InstallWinIoDriver("WinIo.sys");
if(br1==false)
{

	printf("Failed!!!");
   RemoveWinIoDriver();
   ShutdownWinIo();
   exit(0);
}
printf("Successfully Installed1!!! press Enter to continue...");
getchar();
InitializeWinIo();
printf("Successfully Installed!!! press Enter to continue...");
getchar();

for (int ii=0;ii<=100;ii++)
{
   KEY_DOWN(32);//模拟按键
   //KBCWait4IBE();
   Sleep(200);
   KEY_UP(32);//
   //std::cout<<"run once"<<std::endl;
}

printf("done!!!");
getchar();

    RemoveWinIoDriver();
    ShutdownWinIo();
}