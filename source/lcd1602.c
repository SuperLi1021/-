#include <reg52.h>
#include "lcd1602.h"
#include <string.h>
#include <intrins.h>

uchar code table0[] = {"O: I: L: H: D:  "};
uchar code table2[] = {"0123456789"};
uchar dis[3];
uchar num = 0;


/*初始化LCD1602的设置*/
void LCDInit(){
	uchar i;
	lcden = 0; // 拉低使能端，准备产生使能高脉冲信号
	writeCommand(0x38); // 显示模式设置(16x2， 5x7点阵，8位数据接口)
	writeCommand(0x0c); // 开显示，不显示光标
	writeCommand(0x06); // 写一个字符后地址指针自动加1
	writeCommand(0x01); // 显示清零，数据指针清零
	
	/*LCD上电界面*/
	writeCommand(0x80); // 将数据指针定位到第一行首
	for(i = 0; i < strlen(table0); i++){
		writeDataLCD(table0[i]);
		delay(5);
	}

	writeCommand(0x80 + 0x40); // 将数据指针定位到第二行首

}

/*LCD显示函数*/
void display(uint l,m,h,dat,zkb,sw){
	uint disINT = (uint)dat;
	uchar  i;
	dis[0] = l % 1000 / 100;
	dis[1] = l % 100 / 10;
	dis[2] = l % 10;
	for(i = 0; i < 3; i++){
		writeCommand(0x80 + 0x40 + i);
		writeDataLCD(table2[dis[i]]);
		delay(5);
	}
	dis[0] = m % 1000 / 100;
	dis[1] = m % 100 / 10;
	dis[2] = m % 10;
	for(i = 0; i < 3; i++){
		writeCommand(0x80 + 0x40 + 3 + i);
		writeDataLCD(table2[dis[i]]);
		delay(5);
	}
	dis[0] = h % 1000 / 100;
	dis[1] = h % 100 / 10;
	dis[2] = h % 10;
	for(i = 0; i < 3; i++){
		writeCommand(0x80 + 0x40 + 6 + i);
		writeDataLCD(table2[dis[i]]);
		delay(5);
	}
	dis[0] = disINT % 1000 / 100;
	dis[1] = disINT % 100 / 10;
	dis[2] = disINT % 10;
	for(i = 0; i < 3; i++){
		writeCommand(0x80 + 0x40 + 9 + i);
		writeDataLCD(table2[dis[i]]);
		delay(5);
	}
		sw=sw%10;
		writeCommand(0x80 + 0x40 + 12);
		writeDataLCD(table2[sw]);
		delay(5);
	dis[0] = zkb  %100/ 10 ;
	dis[1] = zkb %  10;
	for(i = 0; i < 2; i++){
		writeCommand(0x80 + 0x40 + 13 + i);
		writeDataLCD(table2[dis[i]]);
		delay(5);
	}
	}


/*写指令函数*/
void writeCommand(unsigned char command)
	{
	lcdrs = 0; // 命令选择
	lcdrw = 0;
	P0 = command;
	delay(5);
	
	lcden = 1; // 产生一个正脉冲使能信号
	delay(5);
	lcden = 0;
}

/*写数据函数*/
void writeDataLCD(uchar dat){
	lcdrs = 1; // 数据选择
	lcdrw = 0;

	P0 = dat;
	delay(5);

	lcden = 1;
	delay(5);
	lcden = 0;
}
