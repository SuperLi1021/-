//��ʾ �����¶� �����¶� �¶���ֵ ռ�ձ�
//�������� �����¶� �����¶� �¶���ֵ ռ�ձ�
//�������� ��ֵ ռ�ձ�
//���� 1ѡ�� 2�� 3��
//��ʱ��1 9600������ ��ʱ��2 pwm
//��ʱ��0 



#include "eeprom.h"
#include <reg52.h>
#include <string.h>
#include <intrins.h>
#include "lcd1602.h"
#include "anjian.h"
#include "delay.h"
#include "lanya.h"
//#include "temp.h"
//#include "temp 1.h"
#include "ds18b20.h"
#define uchar unsigned char
#define uint unsigned int
#define FOSC 11.0592 // ϵͳ����Ƶ��11.0592MHz

/*distance   ��ʾ�˴μ�ҩ����
mʱ����
lģʽ
h����
zkbռ�ձ�
pl Ƶ��
FACTOR��������ϵ��
*/



	
/*��ģ��˿ڶ���*/
//sbit pwm = P1^7; // ���ʵ�ʶ���
sbit pwm = P2^1; // ���ʵ�ʶ���
sbit aaa=P2^0;
sbit led1 = P2^2; // ���ⱨ��





/*��ģ�麯������*/

static uint iiii=0;/*����ȫ�ֱ���*/ 
uchar TxStr[3] = {0};
uint wenduo = 0; // �¶�
uint wendui = 0; // �¶�
unsigned int sw,d,ll,pl,pl1,pwmt,led,yunxing;	
uchar djb,gaowen,diwen,zkb,zkb2,dj,zkbb,djbb;
uint zkb1;//led ������ռ�ձ�
uint bz;//��ͷ��־
uint w35;//�¶��Ƿ����35��
/*distance   ��ʾ�˴μ�ҩ����
mʱ����
lģʽ
h����
zkbռ�ձ�
pl Ƶ��
shijian ��Ƭ������ʵ��ʱ��
dj ����pwm����µĵ������
�ⲿ�ж�0 ���ش��� ����Ȧ��
��ʱ��0  ��ʱ
��ʱ��1 ����������
��ʱ��2 pwm����
ʵ������=Ȧ��*��������ϵ��

*/


/*������*/
void main(){
	pl1=400;//1khz
	pl=8;
	zkb=50;//30%
	zkb1=0;
	aaa=1;
	delay(10);
	zkb2=50;
	pwmt=0;
	gaowen=30;
	diwen=15;
	sw=0;
	dj=1;
	djb=0;
	djbb=0;
	zkbb=0;
	yunxing=1;
	LCDInit();
	timerInit();

/*eeprom	*/



 TxStr[0] = byte_read(0x2001);     //�ӵ�ַ0x2001��ȡһ���ֽ�
    TxStr[1] = byte_read(0x2002);     //�ӵ�ַ0x2002��ȡһ���ֽ�
 diwen=TxStr[0];
	gaowen=TxStr[1];

 
    delay(200);        //��ʱ2s

    while(1)
    { 	/*	EA=0;
					wenduo= Ds18b20ReadTemp()-100 ;

       	 	wendui= Ds18b20ReadTemp1()-100 ;
			
	
					EA=1;*/
					wenduo= temper_change1()/10;

       	 	wendui= temper_change2()/10;

	if(yunxing==1)	//������������
	{	if(zkbb==0&&djbb==0)
		{if(wendui>diwen*10)	  //�����¶ȴ��ڵ�����ֵ
		{	if(wendui>wenduo) //�����¶ȴ��������¶�
			{ dj=1;			  //�����־����
				zkb=(wendui-diwen*10)/3;
				if(zkb>=90) zkb=90;
			 }

		}
	
		if(wendui<wenduo)		   //�����¶ȵ��������¶�
		{dj=0;					   //�ص��
		}

	}
		if(wendui>gaowen*10)		   //	  �¶ȸ�����ֵ ����
		{	led=1;zkb2=2+(wendui/10-gaowen);
			}
		if(wendui<gaowen*10)		   //	  �¶ȵ�����ֵ ֹͣ����
		{	led=0;
			}
		if(wendui>350)		   //	  �¶�>35 ��־
		{	w35=1;
			}
		if(wendui<350)		   //	  �¶�<35 ��־
		{	w35=0;
			}
		
		


	}
	display(wenduo,wendui,diwen,gaowen,zkb,sw);		// �����¶� �����¶� ������ֵ ������ֵ ���ռ�ձ�
     anjian();

		
	





		if(dj==1)
			TR2=1;
		if(dj==0) 
			{TR2=0;
			 pwm=1;
			 }
			if(djb==1)
			{
					dj=1;
					delay(50);
			}
			if(djb==0)
			{
					dj=0;
					delay(10);
			}
		
		if(led==1)
		{  TR0=1 ;
			}
		if(led==0)
		{  TR0=0;
			led1=0;
			}
if(diwen!=TxStr[0]||gaowen!=TxStr[1])
  {
    SectorErase(0x2000);    //������һ����
   byte_write(0x2001,diwen);   //�ڵ�ַΪ0x2001���ڴ�д��һ���ֽ�
    byte_write(0x2002,gaowen);   //�ڵ�ַΪ0x2002���ڴ�д��һ���ֽ�
    delay(200);       //��ʱ1s
	}



}
}




void timer0Service() interrupt 1{  // ��ʱ��0�ж�    ���ʱ
	



	TH0 = (65535 - 900) / 256;
	TL0 = (65535 - 900) % 256;
	iiii++;
	if(w35==0){
		
	if(zkb1>=900)
	{bz=1;

	}

	if(zkb1<=200)
	{bz=0;
	}

	if(iiii>=pl)
	{iiii=0;

	if(bz==1)zkb1=zkb1-zkb2;
	if(bz==0)zkb1=zkb1+zkb2;
	 
	 
	}
   
	

	if(iiii>zkb1/100)
	{	led1=0;
	}
	if(iiii<zkb1/100)
	{led1=1;
	 }
 }
	if(w35==1)
	{if(iiii>450)
		iiii=0;
		if(iiii<0.5*450)led1=0;
		if(iiii>0.5*450)led1=1;
	}


}




/*timer2����жϷ������*/
void timer2Service() interrupt 5{  // pwm����

	TF2=0;
	pwmt++;
	
if(pwmt>=pl1) //1khz
 
pwmt=0;
 
if(pwmt<=zkb*4) //ռ�ձ�%30,�ɸ�
 
pwm=0;
 
if(pwmt>zkb*4) pwm=1;
 


}


/*pwmt pwm�����е�ʱ��
zkb   ռ�ձ�
pl Ƶ��
pwm ���ʵ�����
TF2 ��ʱ��2 �������
*/


/*ģʽ ��5 / 10 / 15
��ҩ�ٶȣ�
����
����ʱ��
����
*/



