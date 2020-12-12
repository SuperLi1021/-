//显示 室外温度 室内温度 温度阈值 占空比
//蓝牙发送 室外温度 室内温度 温度阈值 占空比
//蓝牙接收 阈值 占空比
//按键 1选择 2加 3减
//定时器1 9600波特率 定时器2 pwm
//定时器0 



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
//sbit pwm = P1^7; // 电机实际动作
sbit pwm = P2^3; // 电机实际动作

sbit led1 = P2^2; // 声光报警





/*主模块函数声明*/

static uint iiii=0;/*定义全局变量*/ 
uchar TxStr[3] = {0};
uint wenduo = 0; // 温度
uint wendui = 0; // 温度
unsigned int sw,d,ll,pl,pl1,pwmt,led,yunxing;	
uchar djb,gaowen,diwen,zkb,zkb2,dj,zkbb,djbb;
uint zkb1;//led 呼吸灯占空比
uint bz;//回头标志
uint w35;//温度是否高于35度
/*distance   表示此次加药剂量
m时间间隔
l模式
h次数
zkb占空比
pl 频率
shijian 单片机运行实际时间
dj 不记pwm情况下的电机启动
外部中断0 跳沿触发 计算圈数
定时器0  计时
定时器1 产生波特率
定时器2 pwm调速
实际流量=圈数*流量计算系数

*/


/*主函数*/
void main(){
	pl1=100;//1khz
	pl=100;
	zkb=10;//30%
	zkb1=0;
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



 TxStr[0] = byte_read(0x2001);     //从地址0x2001读取一个字节
    TxStr[1] = byte_read(0x2002);     //从地址0x2002读取一个字节
 //diwen=TxStr[0];
//	gaowen=TxStr[1];

 
    delay(200);        //延时2s

    while(1)
    { 	/*	EA=0;
					wenduo= Ds18b20ReadTemp()-100 ;

       	 	wendui= Ds18b20ReadTemp1()-100 ;
			
	
					EA=1;*/
					wenduo= temper_change1()/10;

       	 	wendui= temper_change2()/10;

	if(yunxing==1)	//程序允许运行
	{	if(zkbb==0&&djbb==0)
		{if(wendui>diwen*10)	  //室内温度大于低温阈值
		{	if(wendui>wenduo) //室内温度大于室外温度
			{ dj=1;			  //电机标志启动
				zkb=(wendui-diwen*10)/3;
				if(zkb>=90) zkb=90;
			 }

		}
	
		if(wendui<wenduo)		   //室内温度低于室外温度
		{dj=0;					   //关电机
		}

	}
		if(wendui>gaowen*10)		   //	  温度高于阈值 报警
		{	led=1;zkb2=51-((wendui-gaowen*10)*50)/(350-gaowen*10);pl1=51+(((wendui-gaowen*10)*50)/(350-gaowen*10))*10;
			}
		if(wendui<gaowen*10)		   //	  温度低于阈值 停止报警
		{	led=0;
			}
		if(wendui>350)		   //	  温度>35 标志
		{	w35=1;
			}
		if(wendui<350)		   //	  温度<35 标志
		{	w35=0;
			}
		
		


	}
	display(wenduo,wendui,diwen,gaowen,zkb,sw);		// 室外温度 室内温度 低温阈值 高温阈值 电机占空比
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
    SectorErase(0x2000);    //擦除第一扇区
   byte_write(0x2001,diwen);   //在地址为0x2001的内存写入一个字节
    byte_write(0x2002,gaowen);   //在地址为0x2002的内存写入一个字节
    delay(200);       //延时1s
	}



}
}




void timer0Service() interrupt 1{  // 定时器0中断    秒计时
	



	TH0 = 0xfc;
	TL0 = 0x00;
	iiii++;
	if(w35==0){
		
	if(zkb1>=zkb2)
	{bz=1;

	}

	if(zkb1<=1)
	{bz=0;
	}

	if(iiii>=pl)
	{iiii=0;

	if(bz==1)zkb1--;
	if(bz==0)zkb1++;
	 
	 
	}
   
	

	if((zkb2*iiii/pl)>zkb1)
	{	led1=1;
	}
	if((zkb2*iiii/pl)<zkb1)
	{led1=0;
	 }
 }
	if(w35==1)
	{if(iiii>800)
		iiii=0;
		if(iiii<0.5*800)led1=0;
		if(iiii>0.5*800)led1=1;
	}


}




/*timer2溢出中断服务程序*/
void timer2Service() interrupt 5{  // pwm调速

	TF2=0;
	pwmt++;
	
if(pwmt>=pl) //1khz
 
pwmt=0;
 
if(pwmt<=zkb) //占空比%30,可改
 
pwm=0;
 
if(pwmt>zkb) pwm=1;
 


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



