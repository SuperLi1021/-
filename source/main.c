














































#include "eeprom.h"
#include <reg52.h>
#include <string.h>
#include <intrins.h>
#include "lcd1602.h"
#include "anjian.h"
#include "delay.h"
#include "lanya.h"
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
sbit pwm = P2^1; // ��ƽ������������






/*��ģ�麯������*/
void computeDis();

 
 
uchar TxStr[3] = {0};
uchar dat[2] ={0x01,0x02};



/*����ȫ�ֱ���*/
uint distance = 0; // ��ž���
unsigned int sw,l,m,h,d,ll,tingzhi,tingzhis,shijian, FACTOR,zkb,pl,pwmt,quanshu,yunxing;
/*distance   ��ʾ�˴μ�ҩ����
mʱ����
lģʽ
h����
zkbռ�ձ�
pl Ƶ��
FACTOR��������ϵ��
tingzhi �����־
tingzhis ���ʱ��
shijian ��Ƭ������ʵ��ʱ��
dj ����pwm����µĵ������
�ⲿ�ж�0 ���ش��� ����Ȧ��
��ʱ��0  ��ʱ
��ʱ��1 ����������
��ʱ��2 pwm����
ʵ������=Ȧ��*��������ϵ��

*/
 uchar djb;

/*������*/
void main(){
	uchar bz =0;
	quanshu=0;
	pl=100;//1khz
	zkb=50;//30%
	pwmt=0;
	tingzhis=0;
	tingzhi=0;
	shijian=0;
	l=100;
	m=20;
	h=10;
	sw=0;

	dj=0;

	yunxing=0;
	LCDInit();
	timerInit();
 	FACTOR=115; 
/*eeprom	
    SectorErase(0x2000);    //������һ����
    byte_write(0x2001,dat[0]);   //�ڵ�ַΪ0x2001���ڴ�д��һ���ֽ�
    byte_write(0x2002,dat[1]);   //�ڵ�ַΪ0x2002���ڴ�д��һ���ֽ�
    delay(1000);       //��ʱ1s
    TxStr[0] = byte_read(0x2001);     //�ӵ�ַ0x2001��ȡһ���ֽ�
        TxStr[1] = byte_read(0x2002);     //�ӵ�ַ0x2002��ȡһ���ֽ�
 

 
        delay(2000);        //��ʱ2s
  */
    while(1)
    { 
       

	
	if(yunxing==1)

{

		if(tingzhi==1)
	{	
	if(bz==0)
	 {tingzhis=shijian;//����ֹͣʱ��
		bz=1;
		}

	if((shijian-tingzhis)>=m)
	{
	tingzhi=0;//ֹͣ��־λ�ָ�
	bz=0;
	}
	}


	computeDis();		//����
	if(tingzhi==0)
	{	if(h>0)
		{
			
					
			if(distance<l)
			{dj=1;
			delay(1);
			}
			if(distance>=l)
			{	
				dj=0;
				delay(1);
				h=h-1;
				tingzhi=1;
			}
		}
	}

}
	display(distance,l,m,h);		// ��ʾ���� ģʽl ʱ����m ����h 
     anjian();

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
}





/*void timer0Service() interrupt 1{  // ��ʱ��0�ж�    ���ʱ
	
static uint ii=0;

	TH0 = 0x4c;
	TL0 = 0x00;
	ii++;
	if(ii==20)
	{ii=0;
	shijian++;
	}

	}


	*/





/*timer2����жϷ������*/
void timer2Service() interrupt 5{  // pwm����

	TF2=0;
	pwmt++;
	
if(pwmt>=pl) //1khz
 
pwmt=0;
 
if(pwmt<=zkb) //ռ�ձ�%30,�ɸ�
 
pwm=1;
 
if(pwmt>zkb) pwm=0;
 


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



