#ifndef __TEMP_1_H_
#define __TEMP_1_H_

#include<reg52.h>
//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//--����ʹ�õ�IO��--//
sbit DSPORT1=P2^0;

//--����ȫ�ֺ���--//
void Delay1ms1(uint );
uchar Ds18b20Init1();
void Ds18b20WriteByte1(uchar com);
uchar Ds18b20ReadByte1();
void  Ds18b20ChangTemp1();
void  Ds18b20ReadTempCom1();
int Ds18b20ReadTemp1();

#endif
