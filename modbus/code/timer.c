#include "project.h"

/*---------------------------------------------------------------------------
���÷�ʽ��void SerialPortTime() interrupt 5 using 0
����˵������ʱ��2�жϳ���
---------------------------------------------------------------------------*/
void SerialPortTime() interrupt 5 using 0
{
  //ET2=0;                                  //��ʱ��2�ж��������                   
  TimeInterval=TimeInterval+1;
  if((TimeInterval>4) && countnumber) 
  {
    Recenable=1;           //����
     Deal();                             //�����յ������ݽ��д���
     Recenable=0;        //����
    countnumber=0;
  }
  else { 
	//ET2=1;
  }                               //����ʱ��2��
  TF2=0;          //��ʱ��2�����־,�����0
}
/*---------------------------------------------------------------------------
���÷�ʽ��void Init_timer2(unsigned int baudrate)
����˵������ʱ��2�ĳ�ʼ��
---------------------------------------------------------------------------*/
void Init_timer2(unsigned int baudrate)
{
  unsigned int data TimReg2;
  T2CON = 0x00;
  T2MOD = 0x00;
  TimReg2=65536-(OSFREQ/384/baudrate*11);
  RCAP2L=TimReg2&0x00ff;
  RCAP2H=(TimReg2>8);       //RCAP2H=TimReg2/256
  RCAP2L=0;
  RCAP2H=0;
  TL2  = RCAP2L;                          // 
  TH2  = RCAP2H;                          // 
  TR2=1;                                  // T2CON.2 start timer  
  //ET2=0;                                  // ����ʱ��2�ж�
}