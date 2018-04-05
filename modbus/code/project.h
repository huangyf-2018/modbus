#ifndef __PROJECT_H_
#define __PROJECT_H_

#include "stc12c56xx.h"
#include <intrins.h>//_nop_();

#define  OSFREQ 11059200

sbit Recenable = P1^6;//¿ØÖÆ¶Ë
sbit led = P2^7;//¿ØÖÆ¶Ë

extern char TimeInterval;
extern char data DI[6]; 
extern char data DO[6];
extern char data AI[6];
extern char data AO[6];
extern unsigned char data ReceiveData[14];
extern unsigned char data  countnumber;

void Init_timer2(unsigned int baudrate);
void Init_SerialPort(unsigned int baudrate);
void SendData(unsigned char  *output,unsigned char  Outlength);
unsigned int CRC16(unsigned char *puchMsg, unsigned int usDataLen);
void Deal();
#endif