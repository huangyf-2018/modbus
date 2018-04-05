#include "project.h"

/*---------------------------------------------------------------------------
调用方式：void SerialPortTime() interrupt 5 using 0
函数说明：定时器2中断程序
---------------------------------------------------------------------------*/
void SerialPortTime() interrupt 5 using 0
{
  //ET2=0;                                  //定时器2中断允许控制                   
  TimeInterval=TimeInterval+1;
  if((TimeInterval>4) && countnumber) 
  {
    Recenable=1;           //发送
     Deal();                             //将接收到的数据进行处理
     Recenable=0;        //接收
    countnumber=0;
  }
  else { 
	//ET2=1;
  }                               //将定时器2打开
  TF2=0;          //定时器2溢出标志,软件清0
}
/*---------------------------------------------------------------------------
调用方式：void Init_timer2(unsigned int baudrate)
函数说明：定时器2的初始化
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
  //ET2=0;                                  // 开定时器2中断
}