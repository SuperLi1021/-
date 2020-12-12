#ifndef _ds18b20_h_
#define _ds18b20_h_


#define uchar unsigned char
#define uint unsigned int


//sbit DQ1 = P2^4;
//sbit DQ2 = P2^3;

sbit DQ1 = P2^0;
sbit DQ2 = P2^1;




void DS18B20_init1();
void write_byte1(uchar dat);   //写一个字节
uchar read_byte1();    //读一个字节
uint read_temper1 ();
uint temper_change1();


void DS18B20_init2();
void write_byte2(uchar dat);   //写一个字节
uchar read_byte2();    //读一个字节
uint read_temper2 ();
uint temper_change2();

#endif