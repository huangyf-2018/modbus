#include "project.h"

char TimeInterval;
char MyAddress;            
char data DI[6]={1,2,3,4,5,6}; 
char data DO[6]={6,7,8,9,10,11}; 
char data AI[6]={11,12,13,14,15,16};
char data AO[6]={16,17,18,19,20,21};   
unsigned char data ReceiveData[14];
unsigned char data  countnumber;

/*---------------------------------------------------------------------------
函数说明：主函数
---------------------------------------------------------------------------*/
main()
{  
  EA=1;                                   //开总中断
  Init_SerialPort(9600);
  Init_timer2(9600);
  Recenable=0;                            //接收允许
  MyAddress=0x01;                         //本机地址
  while(1)
  {     
   
  }
}