#include "project.h"

/*---------------------------------------------------------------------------
���÷�ʽ��void SendData(unsigned char  *output,unsigned char  Outlength)
����˵������������������
---------------------------------------------------------------------------*/
void SendData(unsigned char  *output,unsigned char  Outlength)
{  
  ES=0;
  while(Outlength--)
  {  
    TI=0;
    ACC=*output;
    TB8=P;
    SBUF=*(output++);
    while(!TI);
    TI=0;   
  }  
  ES=1;
}

/*---------------------------------------------------------------------------
���÷�ʽ��void SeiralA() interrupt 4 using 0
����˵����ͨѶ�ж�
---------------------------------------------------------------------------*/
void SeiralA() interrupt 4 using 0
{
  if(RI) 
  {
    if((TimeInterval>2)&&(TimeInterval<=4)) 
    { countnumber=0;}
    if(countnumber>60) 
    { countnumber=0;}                     
    ReceiveData[countnumber++]=SBUF;   //�����յ������ݵ���������
    TimeInterval=0;
    RI=0;
    //ET2=1;                                //�����յ����ݺ�,����ʱ��2����
  }                
}
/*---------------------------------------------------------------------------
���÷�ʽ��void Init_SerialPort(unsigned int baudrate)
����˵�������ڳ�ʼ��
---------------------------------------------------------------------------*/
void Init_SerialPort(unsigned int baudrate)
{
  unsigned char TimReg2;
  SCON = 0xd0;                            // ��ʽ3, 8-bit UART, enable rcvr      
  TMOD = 0x21;                            // T0��ʽ1��16λ��,  T1��ʽ2,8λ��װ        
  TimReg2=256-(OSFREQ/384/baudrate);
  TH1 = TimReg2;                          // ��ʱ��1,��11.0592MHz��,������Ϊ9600   
  TL1 = TH1;
  TR1= 1;                                 // TR1:  ��ʱ��ʼ                          
  //PS=1;                                 // �����ж�����
  ES=1;                                 // �����ж�
}