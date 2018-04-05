#include "project.h"


/*---------------------------------------------------------------------------
调用方式：unsigned char getbit(unsigned int  address,unsigned char  function)
函数说明：取出所给地址的位值
---------------------------------------------------------------------------*/
unsigned char getbit(unsigned int  address,unsigned char  function)
{
  unsigned char data Offset;
  unsigned char data temp;
  unsigned char data *Myaddress;  
  Offset=(char)address&0x07;
  switch (function)                 //根据功能码不同进行相应处理
  {
   case 2:
           Myaddress=DI;
           break;
   case 1:
           Myaddress=DO;             
           break;
   default:
           return 2;
  }
  temp=(char)(address>>3);
  temp=*(Myaddress+temp);
  temp>>=(Offset);
  if (temp&0x01)
    return 1;
  else
    return 0;
}
/*---------------------------------------------------------------------------
调用方式：void Function12(unsigned char address,unsigned char len)
函数说明：功能码1，2处理
---------------------------------------------------------------------------*/
void Function12(unsigned char address,unsigned char len)
{
  unsigned int data i;
  unsigned char data j;
  unsigned char data length;
  unsigned char data *send;
  unsigned int data temp;
  unsigned char data function;
  length=0;
  send=ReceiveData;
  function=send[1];
  for (i=1;i<=len;i++)
	{
    length++;
    *(send+2+length)=0;
    for (j=0;j<8;j++)
    {
      *(send+2+length)=*(send+2+length)|getbit(address,function)<<j;
   address++;
   i++;
   if(i>len)break;
    }
    i--;
  }
  *(send+2)=length;                        //数据长度
  temp=CRC16(send,length+3);               //DI状态数据
  *(send+3+length)=(char)(temp>>8);        //CRC校验高
  *(send+4+length)=(char)temp;             //CRC校验低
  SendData(send,length+5);                 //调用A发送程序
}
/*---------------------------------------------------------------------------
调用方式：void Function3(unsigned char  address,unsigned char  len)
函数说明：功能码3处理-----读取寄存器
---------------------------------------------------------------------------*/
void Function3(unsigned char  address,unsigned char  len)
{
  unsigned char data i;
  unsigned char data *send;
  unsigned int data temp;
  send=ReceiveData;
  *(send+2)=2*len;                         //数据长度高
  address=2*address;
  for(i=0;i<len;i++)                       //取输入寄存器数据
  {
    *(send+3+2*i)=AO[address++];
    *(send+4+2*i)=AO[address++];
  }
  temp=CRC16(send,2*len+3);                //CRC校验
  *(send+3+2*len)=(char)(temp>>8);
  *(send+4+2*len)=(char)temp;
  SendData(send,2*len+5);                  //调用A发送程序
}
/*---------------------------------------------------------------------------
调用方式：void Function4(unsigned char  address,unsigned char  len)
函数说明：功能码处理4----读取输入寄存器
---------------------------------------------------------------------------*/
void Function4(unsigned char  address,unsigned char  len)
{
  unsigned char data i;
  unsigned char data *send;
  unsigned int data temp;

  send=ReceiveData;
  *(send+2)=2*len;
  address=2*address;
  for(i=0;i<len;i++)                       //取数据
  {
    *(send+4+2*i)=AI[address++];
    *(send+3+2*i)=AI[address++];
  }
  temp=CRC16(send,2*len+3);
  *(send+3+2*len)=(char)(temp>>8);
  *(send+4+2*len)=(char)temp;
  SendData(send,2*len+5); 
}
/*---------------------------------------------------------------------------
调用方式：void Function6(unsigned char address)
函数说明：写单路寄存器
---------------------------------------------------------------------------*/
void Function6(unsigned char address)
{
  int temp;
  unsigned char data *WriteData;
  temp=2*address;
  WriteData=AO;
  //将写入的数据进行处理
  //your code to add here to deal with the write value
  *(WriteData+temp)=ReceiveData[4];
  *(WriteData+temp+1)=ReceiveData[5];
  SendData(ReceiveData,countnumber);       //调用发送程序，返回与主机相同的报文
}
/*---------------------------------------------------------------------------
调用方式：void SendError(char ErrorCode)
函数说明：
---------------------------------------------------------------------------*/
void SendError(char ErrorCode)
{
  unsigned char data *send;
  unsigned int data temp;
  send=ReceiveData;
  *(send+1)=ReceiveData[1]|0x01;//最高位置1
  *(send+2)=ErrorCode;
  temp=CRC16(send,3);
  *(send+3)=(char)(temp>>8);
  *(send+4)=(char)temp;
  SendData(send,countnumber);              //调用发送程序,返回错误代码
}
/*---------------------------------------------------------------------------
调用方式：void Deal()
函数说明：接收数据处理
---------------------------------------------------------------------------*/
void Deal()
{
  unsigned int data temp;
  unsigned char data address;
  unsigned char data length;
  unsigned char data counter;
  unsigned char data *Pointer;
  Pointer=ReceiveData;
  counter=countnumber;
  if (counter<=3 ) return;
  temp=Pointer[counter-2]<<8;   
  temp= temp|Pointer[counter-1];
  if( temp==CRC16(Pointer,counter-2))      //较验正确
  { 
    address=Pointer[3];
    length=Pointer[5];
    if(address<48)
    {
      switch (Pointer[1])                  //根据功能码不同进行相应处理*/
   {
    case 1:
            Function12(address,length);
            break;
	case 2:
            Function12(address,length);
            break;
    case 3:
            address=address-1;
            Function3(address,length);
            break;
    case 4:
            address=address-1;
            Function4(address,length);
            break;
    case 6:
            address=address-1;
            Function6(address);
    default:
               SendError(0x81);
               break;
      }
    }
    else
    { SendError(0x82);}
  }
  countnumber=0;
}
/*bit Chargetbit(unsigned char character,unsigned char Number) 
{ 
  if(character>>Number&0x01==1)
    return 1;
  else
    return 0;
}
//设定某一位的值***********************************************************
unsigned char SetBit(unsigned char Character,unsigned char num,bit boolen)
{
  unsigned char code bit_value[]={1,2,4,8,16,32,64,128};
  if(boolen)  
   return Character|bit_value[num];
  else
    return Character&~bit_value[num];
}*/