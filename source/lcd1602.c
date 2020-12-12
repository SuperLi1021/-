#include <reg52.h>
#include "lcd1602.h"
#include <string.h>
#include <intrins.h>

uchar code table0[] = {"O: I: L: H: D:  "};
uchar code table2[] = {"0123456789"};
uchar dis[3];
uchar num = 0;


/*��ʼ��LCD1602������*/
void LCDInit(){
	uchar i;
	lcden = 0; // ����ʹ�ܶˣ�׼������ʹ�ܸ������ź�
	writeCommand(0x38); // ��ʾģʽ����(16x2�� 5x7����8λ���ݽӿ�)
	writeCommand(0x0c); // ����ʾ������ʾ���
	writeCommand(0x06); // дһ���ַ����ַָ���Զ���1
	writeCommand(0x01); // ��ʾ���㣬����ָ������
	
	/*LCD�ϵ����*/
	writeCommand(0x80); // ������ָ�붨λ����һ����
	for(i = 0; i < strlen(table0); i++){
		writeDataLCD(table0[i]);
		delay(5);
	}

	writeCommand(0x80 + 0x40); // ������ָ�붨λ���ڶ�����

}

/*LCD��ʾ����*/
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


/*дָ���*/
void writeCommand(unsigned char command)
	{
	lcdrs = 0; // ����ѡ��
	lcdrw = 0;
	P0 = command;
	delay(5);
	
	lcden = 1; // ����һ��������ʹ���ź�
	delay(5);
	lcden = 0;
}

/*д���ݺ���*/
void writeDataLCD(uchar dat){
	lcdrs = 1; // ����ѡ��
	lcdrw = 0;

	P0 = dat;
	delay(5);

	lcden = 1;
	delay(5);
	lcden = 0;
}
