#ifndef __TEMP 1_H_
#define __TEMP 1_H_

#include<reg52.h>
//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//--定义使用的IO口--//
sbit DSPORT=P2^0;

//--声明全局函数--//
void Delay1ms1(uint );
uchar Ds18b20Init1();
void Ds18b20WriteByte1(uchar com);
uchar Ds18b20ReadByte1();
void  Ds18b20ChangTemp1();
void  Ds18b20ReadTempCom1();
int Ds18b20ReadTemp1();

#endif
