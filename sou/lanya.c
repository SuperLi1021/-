
#include <reg52.h>
#include "lanya.h"

#include "delay.h"

uint db=0;
uchar lb,mb,hb;

uchar zifu[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};

/*timer��ʼ������*/
void timerInit(){

	SCON = 0x50;
	TMOD = 0x21;					 // ͬʱʹ��������ʱ��
	CP_RL2=0;//��ʱ��2   16λ�Զ���װ
	EXEN2=0;
	TH2 = RCAP2H= 0xFF;						 // �ó�ֵ ff
	TL2 = RCAP2L= 0x07;							//a7
	TH1 = 0xFD;               // TH1:  ��ʼֵΪ0xFD  �����ʣ�9600 ����Ƶ�ʣ�11.0592MHz  
	TL1 = 0x00;
	TH0 = 0x4c;
	TL0 = 0x00;
	ET2 = 1;
	ET0 = 1; 						// ��timer0����ж�
	TR1 = 1;                  // TR1:  ������ʱ��1                         
	EA  = 1;                  //�����ж�
	EX0=1;	
	IT0=1;
	ES  = 1;                  //�򿪴����ж�

	
	}


void uart_send_byte(unsigned char dat)
{
	SBUF = dat; // �������͵����ͻ���Ĵ���SBUF��һλһλ�ķ���
	while(!TI); // �ȴ�������� (�������TIӲ����1)
	TI = 0;// ��TI���㣬��ʾ���Է�����һ�ֽ����ݡ�
}
// �����жϴ����� �����ڽ��յ����ݣ�����������϶��������𴮿��жϣ�
void uart_send_str(unsigned char *s)
{
	while(*s != '\0')// '\0':�ַ���������־
	{
		uart_send_byte(*s);// ����1���ֽ����ݣ�1���ַ�ռ8λ��1�ֽ�
		s++;// ָ����һ���ַ�
	}
}

void uart_interrupt(void) interrupt 4 		//Ҳ�д����жϷ������
{	
	unsigned char send_data1[]="ireceive" ;// Ҫ���͵���Ϣ

	unsigned char recv_data;// ������Ž��յ�������
	unsigned int send_data[3] ;
	unsigned char send_data0[3] ;// Ҫ���͵���Ϣ
	unsigned char send_data2[3] ;// Ҫ���͵���Ϣ
	unsigned char send_data3[3] ;// Ҫ���͵���Ϣ
	unsigned char send_data4[3] ;// Ҫ���͵���Ϣ
	unsigned char send_data5[3] ;// Ҫ���͵���Ϣ
	unsigned char send_data6[3] ;// Ҫ���͵���Ϣ
	unsigned char send_data7[3] ;// Ҫ���͵���Ϣ
	unsigned char send_data8[3] ;// Ҫ���͵���Ϣ
	unsigned char send_data9[3] ;// Ҫ���͵���Ϣ

	send_data[0] = wenduo % 1000/100;
	send_data[1] = wenduo % 100 / 10;
	send_data[2] = wenduo % 10;
	send_data2[0] = zifu[send_data[0]];
	send_data2[1] = zifu[send_data[1]];
	send_data2[2] = zifu[send_data[2]];
	send_data3[0] = wendui % 1000/100;
	send_data3[1] = wendui % 100 / 10;
	send_data3[2] = wendui % 10;
	send_data4[0] = zifu[send_data3[0]];
	send_data4[1] = zifu[send_data3[1]];
	send_data4[2] = zifu[send_data3[2]];
	send_data5[0] = diwen % 1000/100;
	send_data5[1] = diwen % 100 / 10;
	send_data5[2] = diwen % 10;
	send_data6[0] = zifu[send_data5[0]];
	send_data6[1] = zifu[send_data5[1]];
	send_data6[2] = zifu[send_data5[2]];
	send_data7[0] = gaowen % 1000/100;
	send_data7[1] = gaowen % 100 / 10;
	send_data7[2] = gaowen % 10;
	send_data8[0] = zifu[send_data7[0]];
	send_data8[1] = zifu[send_data7[1]];
	send_data8[2] = zifu[send_data7[2]];
	send_data9[0] = zkb % 1000/100;
	send_data9[1] = zkb % 100 / 10;
	send_data9[2] = zkb % 10;
	send_data0[0] = zifu[send_data9[0]];
	send_data0[1] = zifu[send_data9[1]];
	send_data0[2] = zifu[send_data9[2]];

	if(RI) //��������(1�ֽ�)��ϣ�RI�ᱻӲ����1
	{
		RI = 0;            		// �� �����жϱ�־λ ����(�ô��ڿ��Լ�����������)
		recv_data = SBUF;           	//��ȡ���յ������ݣ�����ŵ�data
	if(recv_data==0xff){djb=0;}
	if(recv_data==0xfe){djb=1;}
	if(lb||mb||hb==1)
	{	if(recv_data==0x00) {db= 10*db+0;}
	if(recv_data==0x01){db= 10*db+1;}
	if(recv_data==0x02){db= 10*db+2;}
	if(recv_data==0x03){db= 10*db+3;}
	if(recv_data==0x04){db= 10*db+4;}
	if(recv_data==0x05){db= 10*db+5;}
	if(recv_data==0x06){db= 10*db+6;}
	if(recv_data==0x07){db= 10*db+7;}
	if(recv_data==0x08){db= 10*db+8;}
	if(recv_data==0x09){db= 10*db+9;}
	if(recv_data==0x0a){lb=0;diwen=db;db=0;}//������ֵ
  	if(recv_data==0x0b){lb=0;gaowen=db;db=0;}//������ֵ
	if(recv_data==0x0d){lb=0; pl =db;db=0;}//Ƶ��
	if(recv_data==0x0e){lb=0; zkb =db;db=0;}//ռ�ձ�

	}
		if(recv_data ==0x0a){
		lb=1;	}




	
		
	    uart_send_str(send_data2); //�յ�����֮�󣬷����ַ���"I received."���Է�
	    uart_send_str(send_data4); //�յ�����֮�󣬷����ַ���"I received."���Է�
	    uart_send_str(send_data6); //�յ�����֮�󣬷����ַ���"I received."���Է�
	    uart_send_str(send_data8); //�յ�����֮�󣬷����ַ���"I received."���Է�
	    uart_send_str(send_data0); //�յ�����֮�󣬷����ַ���"I received."���Է�
	}
	if(TI)// ��������(1�ֽ�)���
	{
		TI = 0;// �� �����жϱ�־λ ����(�ô��ڿ��Լ�����������)
	}

} 

