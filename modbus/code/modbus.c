#include "project.h"


/*---------------------------------------------------------------------------
���÷�ʽ��unsigned char getbit(unsigned int  address,unsigned char  function)
����˵����ȡ��������ַ��λֵ
---------------------------------------------------------------------------*/
unsigned char getbit(unsigned int  address,unsigned char  function)
{
  unsigned char data Offset;
  unsigned char data temp;
  unsigned char data *Myaddress;  
  Offset=(char)address&0x07;
  switch (function)                 //���ݹ����벻ͬ������Ӧ����
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
���÷�ʽ��void Function12(unsigned char address,unsigned char len)
����˵����������1��2����
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
  *(send+2)=length;                        //���ݳ���
  temp=CRC16(send,length+3);               //DI״̬����
  *(send+3+length)=(char)(temp>>8);        //CRCУ���
  *(send+4+length)=(char)temp;             //CRCУ���
  SendData(send,length+5);                 //����A���ͳ���
}
/*---------------------------------------------------------------------------
���÷�ʽ��void Function3(unsigned char  address,unsigned char  len)
����˵����������3����-----��ȡ�Ĵ���
---------------------------------------------------------------------------*/
void Function3(unsigned char  address,unsigned char  len)
{
  unsigned char data i;
  unsigned char data *send;
  unsigned int data temp;
  send=ReceiveData;
  *(send+2)=2*len;                         //���ݳ��ȸ�
  address=2*address;
  for(i=0;i<len;i++)                       //ȡ����Ĵ�������
  {
    *(send+3+2*i)=AO[address++];
    *(send+4+2*i)=AO[address++];
  }
  temp=CRC16(send,2*len+3);                //CRCУ��
  *(send+3+2*len)=(char)(temp>>8);
  *(send+4+2*len)=(char)temp;
  SendData(send,2*len+5);                  //����A���ͳ���
}
/*---------------------------------------------------------------------------
���÷�ʽ��void Function4(unsigned char  address,unsigned char  len)
����˵���������봦��4----��ȡ����Ĵ���
---------------------------------------------------------------------------*/
void Function4(unsigned char  address,unsigned char  len)
{
  unsigned char data i;
  unsigned char data *send;
  unsigned int data temp;

  send=ReceiveData;
  *(send+2)=2*len;
  address=2*address;
  for(i=0;i<len;i++)                       //ȡ����
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
���÷�ʽ��void Function6(unsigned char address)
����˵����д��·�Ĵ���
---------------------------------------------------------------------------*/
void Function6(unsigned char address)
{
  int temp;
  unsigned char data *WriteData;
  temp=2*address;
  WriteData=AO;
  //��д������ݽ��д���
  //your code to add here to deal with the write value
  *(WriteData+temp)=ReceiveData[4];
  *(WriteData+temp+1)=ReceiveData[5];
  SendData(ReceiveData,countnumber);       //���÷��ͳ��򣬷�����������ͬ�ı���
}
/*---------------------------------------------------------------------------
���÷�ʽ��void SendError(char ErrorCode)
����˵����
---------------------------------------------------------------------------*/
void SendError(char ErrorCode)
{
  unsigned char data *send;
  unsigned int data temp;
  send=ReceiveData;
  *(send+1)=ReceiveData[1]|0x01;//���λ��1
  *(send+2)=ErrorCode;
  temp=CRC16(send,3);
  *(send+3)=(char)(temp>>8);
  *(send+4)=(char)temp;
  SendData(send,countnumber);              //���÷��ͳ���,���ش������
}
/*---------------------------------------------------------------------------
���÷�ʽ��void Deal()
����˵�����������ݴ���
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
  if( temp==CRC16(Pointer,counter-2))      //������ȷ
  { 
    address=Pointer[3];
    length=Pointer[5];
    if(address<48)
    {
      switch (Pointer[1])                  //���ݹ����벻ͬ������Ӧ����*/
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
//�趨ĳһλ��ֵ***********************************************************
unsigned char SetBit(unsigned char Character,unsigned char num,bit boolen)
{
  unsigned char code bit_value[]={1,2,4,8,16,32,64,128};
  if(boolen)  
   return Character|bit_value[num];
  else
    return Character&~bit_value[num];
}*/