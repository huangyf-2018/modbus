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
����˵����������
---------------------------------------------------------------------------*/
main()
{  
  EA=1;                                   //�����ж�
  Init_SerialPort(9600);
  Init_timer2(9600);
  Recenable=0;                            //��������
  MyAddress=0x01;                         //������ַ
  while(1)
  {     
   
  }
}