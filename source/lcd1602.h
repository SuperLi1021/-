#ifndef _lcd1602_h_
#define _lcd1602_h_

#define uchar unsigned char
#define uint unsigned int

/*LCD1602显示模块端口定义*/
sbit lcdrs = P2^6;
sbit lcdrw = P2^5;
sbit lcden = P2^7;



										   	
/*LCD1602显示模块函数声明*/
void delay(uint xms);
void writeCommand(uchar command);
void writeDataLCD(uchar dat);
void LCDInit();
void display(uint l,m,h,dat,zkb,sw);

#endif

