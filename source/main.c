














































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
#define FOSC 11.0592 // 系统晶振频率11.0592MHz

/*distance   表示此次加药剂量
m时间间隔
l模式
h次数
zkb占空比
pl 频率
FACTOR流量计算系数
*/



	
/*主模块端口定义*/
sbit pwm = P2^1; // 电平触发输入引脚






/*主模块函数声明*/
void computeDis();

 
 
uchar TxStr[3] = {0};
uchar dat[2] ={0x01,0x02};



/*定义全局变量*/
uint distance = 0; // 存放距离
unsigned int sw,l,m,h,d,ll,tingzhi,tingzhis,shijian, FACTOR,zkb,pl,pwmt,quanshu,yunxing;
/*distance   表示此次加药剂量
m时间间隔
l模式
h次数
zkb占空比
pl 频率
FACTOR流量计算系数
tingzhi 间隔标志
tingzhis 间隔时间
shijian 单片机运行实际时间
dj 不记pwm情况下的电机启动
外部中断0 跳沿触发 计算圈数
定时器0  计时
定时器1 产生波特率
定时器2 pwm调速
实际流量=圈数*流量计算系数

*/
 uchar djb;

/*主函数*/
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
    SectorErase(0x2000);    //擦除第一扇区
    byte_write(0x2001,dat[0]);   //在地址为0x2001的内存写入一个字节
    byte_write(0x2002,dat[1]);   //在地址为0x2002的内存写入一个字节
    delay(1000);       //延时1s
    TxStr[0] = byte_read(0x2001);     //从地址0x2001读取一个字节
        TxStr[1] = byte_read(0x2002);     //从地址0x2002读取一个字节
 

 
        delay(2000);        //延时2s
  */
    while(1)
    { 
       

	
	if(yunxing==1)

{

		if(tingzhi==1)
	{	
	if(bz==0)
	 {tingzhis=shijian;//计算停止时间
		bz=1;
		}

	if((shijian-tingzhis)>=m)
	{
	tingzhi=0;//停止标志位恢复
	bz=0;
	}
	}


	computeDis();		//计算
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
	display(distance,l,m,h);		// 显示流量 模式l 时间间隔m 次数h 
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





/*void timer0Service() interrupt 1{  // 定时器0中断    秒计时
	
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





/*timer2溢出中断服务程序*/
void timer2Service() interrupt 5{  // pwm调速

	TF2=0;
	pwmt++;
	
if(pwmt>=pl) //1khz
 
pwmt=0;
 
if(pwmt<=zkb) //占空比%30,可改
 
pwm=1;
 
if(pwmt>zkb) pwm=0;
 


}


/*pwmt pwm调速中的时间
zkb   占空比
pl 频率
pwm 电机实际输出
TF2 定时器2 溢出重置
*/


/*模式 ：5 / 10 / 15
加药速度：
计量
加料时间
次数
*/



