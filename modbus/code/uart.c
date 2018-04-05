#include "project.h"

/*---------------------------------------------------------------------------
调用方式：void SendData(unsigned char  *output,unsigned char  Outlength)
函数说明：发送数据至窗口
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
调用方式：void SeiralA() interrupt 4 using 0
函数说明：通讯中断
---------------------------------------------------------------------------*/
void SeiralA() interrupt 4 using 0
{
  if(RI) 
  {
    if((TimeInterval>2)&&(TimeInterval<=4)) 
    { countnumber=0;}
    if(countnumber>60) 
    { countnumber=0;}                     
    ReceiveData[countnumber++]=SBUF;   //将接收到的数据到缓冲区内
    TimeInterval=0;
    RI=0;
    //ET2=1;                                //当接收到数据后,将定时器2开启
  }                
}
/*---------------------------------------------------------------------------
调用方式：void Init_SerialPort(unsigned int baudrate)
函数说明：串口初始化
---------------------------------------------------------------------------*/
void Init_SerialPort(unsigned int baudrate)
{
  unsigned char TimReg2;
  SCON = 0xd0;                            // 方式3, 8-bit UART, enable rcvr      
  TMOD = 0x21;                            // T0方式1（16位）,  T1方式2,8位重装        
  TimReg2=256-(OSFREQ/384/baudrate);
  TH1 = TimReg2;                          // 定时器1,在11.0592MHz下,波特率为9600   
  TL1 = TH1;
  TR1= 1;                                 // TR1:  定时开始                          
  //PS=1;                                 // 串行中断优先
  ES=1;                                 // 接收中断
}