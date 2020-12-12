
#include <reg52.h>
#include "lanya.h"
#include <stdio.h>
#include "delay.h"

uint db=0;
uchar lb,mb,hb,a;
uchar ii=0;
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
void uart_send_1()
{
                TI = 1;//���������־λ
                puts("��");//���͵ĺ���
                while(!TI);//�ж��Ƿ������  ������ɳ�ѭ��
                TI = 0;
                delay(10);//�ӳ�1��
}
void uart_send_2()
{
                TI = 1;//���������־λ
                puts("��");//���͵ĺ���
                while(!TI);//�ж��Ƿ������  ������ɳ�ѭ��
                TI = 0;
                delay(10);//�ӳ�1��
}void uart_send_3()
{
                TI = 1;//���������־λ
                puts("��");//���͵ĺ���
                while(!TI);//�ж��Ƿ������  ������ɳ�ѭ��
                TI = 0;
                delay(10);//�ӳ�1��
}void uart_send_4()
{
                TI = 1;//���������־λ
                puts("��");//���͵ĺ���
                while(!TI);//�ж��Ƿ������  ������ɳ�ѭ��
                TI = 0;
                delay(10);//�ӳ�1��
}void uart_send_5()
{
                TI = 1;//���������־λ
                puts("ռ");//���͵ĺ���
                while(!TI);//�ж��Ƿ������  ������ɳ�ѭ��
                TI = 0;
                delay(10);//�ӳ�1��
}
void uart_send_int(unsigned int s)
{
	
	uchar dis[4];

	dis[0] = (s % 1000 / 100)+48;
	dis[1] = (s % 100 / 10)+48;
	dis[2] = (s % 10)+48;
	dis[3] = 10;

		uart_send_byte(dis[0]);// ����1���ֽ����ݣ�1���ַ�ռ8λ��1�ֽ�
		uart_send_byte(dis[1]);// ����1���ֽ����ݣ�1���ַ�ռ8λ��1�ֽ�
		uart_send_byte(dis[2]);// ����1���ֽ����ݣ�1���ַ�ռ8λ��1�ֽ�
		uart_send_byte(dis[3]);// ����1���ֽ����ݣ�1���ַ�ռ8λ��1�ֽ�
	
}


void uart_interrupt(void) interrupt 4 		//Ҳ�д����жϷ������
{	
	uint shuju;
	

	unsigned char recv_data1[2];// ������Ž��յ�������
	unsigned char recv_data[4];	
	a=0;
	if(RI) //��������(1�ֽ�)��ϣ�RI�ᱻӲ����1
	{ 
		RI = 0;            		// �� �����жϱ�־λ ����(�ô��ڿ��Լ�����������)
		
		recv_data1[ii] = SBUF;           	//��ȡ���յ������ݣ�����ŵ�data

		ii++;
		if(ii==2)
		{		ii=0;
			 uart_send_int(a);

 uart_send_1();

	    uart_send_int(wenduo); //�յ�����֮�󣬷����ַ���"I received."���Է�
uart_send_2();
      uart_send_int(wendui); //�յ�����֮�󣬷����ַ���"I received."���Է�
 uart_send_3();

	    uart_send_int(gaowen); //�յ�����֮�󣬷����ַ���"I received."���Է�
 uart_send_4();

	    uart_send_int(diwen); //�յ�����֮�󣬷����ַ���"I received."���Է�
 uart_send_5();

	    uart_send_int(zkb); //�յ�����֮�󣬷����ַ���"I received."���Է�
			



	
		}
	}
	if(TI)// ��������(1�ֽ�)���
	{
		TI = 0;// �� �����жϱ�־λ ����(�ô��ڿ��Լ�����������)
	}
	recv_data[0]=recv_data1[0]/0x10;
	recv_data[1]=recv_data1[0]%0x10;
	recv_data[2]=recv_data1[1]/0x10;
	recv_data[3]=recv_data1[1]%0x10;
	shuju=recv_data[1]*100+recv_data[2]*10+recv_data[3];
	if(recv_data[0]==10) gaowen=shuju;
	if(recv_data[0]==11) diwen=shuju;
	if(recv_data[0]==12) zkb=shuju;
	if(recv_data[0]==13) pl=shuju;
	if(recv_data[0]==14)	djb=1;
	if(recv_data[0]==15) djb=0;


	


} 

