
#include <reg52.h>
#include "lanya.h"
#include <stdio.h>
#include "delay.h"

uint db=0;
uchar lb,mb,hb,a;
uchar ii=0;
uchar zifu[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};


/*timer初始化函数*/
void timerInit(){

	SCON = 0x50;
	TMOD = 0x21;					 // 同时使用两个定时器
	CP_RL2=0;//定时器2   16位自动重装
	EXEN2=0;
	TH2 = RCAP2H= 0xFF;						 // 置初值 ff
	TL2 = RCAP2L= 0x07;							//a7
	TH1 = 0xFD;               // TH1:  初始值为0xFD  波特率：9600 晶振频率：11.0592MHz  
	TL1 = 0x00;
	TH0 = 0x4c;
	TL0 = 0x00;
	ET2 = 1;
	ET0 = 1; 						// 开timer0溢出中断
	TR1 = 1;                  // TR1:  开启定时器1                         
	EA  = 1;                  //打开总中断
	EX0=1;	
	IT0=1;
	ES  = 1;                  //打开串口中断

	
	}


void uart_send_byte(unsigned char dat)
{
	SBUF = dat; // 将数据送到发送缓冲寄存器SBUF，一位一位的发送
	while(!TI); // 等待发送完毕 (发送完毕TI硬件置1)
	TI = 0;// 将TI清零，表示可以发送下一字节数据。
}
// 串口中断处理函数 （串口接收到数据，发送数据完毕都可以引起串口中断）
void uart_send_1()
{
                TI = 1;//发送请求标志位
                puts("外");//发送的汉字
                while(!TI);//判断是否发送完成  发送完成出循环
                TI = 0;
                delay(10);//延迟1秒
}
void uart_send_2()
{
                TI = 1;//发送请求标志位
                puts("内");//发送的汉字
                while(!TI);//判断是否发送完成  发送完成出循环
                TI = 0;
                delay(10);//延迟1秒
}void uart_send_3()
{
                TI = 1;//发送请求标志位
                puts("高");//发送的汉字
                while(!TI);//判断是否发送完成  发送完成出循环
                TI = 0;
                delay(10);//延迟1秒
}void uart_send_4()
{
                TI = 1;//发送请求标志位
                puts("低");//发送的汉字
                while(!TI);//判断是否发送完成  发送完成出循环
                TI = 0;
                delay(10);//延迟1秒
}void uart_send_5()
{
                TI = 1;//发送请求标志位
                puts("占");//发送的汉字
                while(!TI);//判断是否发送完成  发送完成出循环
                TI = 0;
                delay(10);//延迟1秒
}
void uart_send_int(unsigned int s)
{
	
	uchar dis[4];

	dis[0] = (s % 1000 / 100)+48;
	dis[1] = (s % 100 / 10)+48;
	dis[2] = (s % 10)+48;
	dis[3] = 10;

		uart_send_byte(dis[0]);// 发送1个字节数据，1个字符占8位，1字节
		uart_send_byte(dis[1]);// 发送1个字节数据，1个字符占8位，1字节
		uart_send_byte(dis[2]);// 发送1个字节数据，1个字符占8位，1字节
		uart_send_byte(dis[3]);// 发送1个字节数据，1个字符占8位，1字节
	
}


void uart_interrupt(void) interrupt 4 		//也叫串行中断服务程序
{	
	uint shuju;
	

	unsigned char recv_data1[2];// 用来存放接收到的数据
	unsigned char recv_data[4];	
	a=0;
	if(RI) //接收数据(1字节)完毕，RI会被硬件置1
	{ 
		RI = 0;            		// 将 接收中断标志位 清零(让串口可以继续接收数据)
		
		recv_data1[ii] = SBUF;           	//读取接收到的数据，并存放到data

		ii++;
		if(ii==2)
		{		ii=0;
			 uart_send_int(a);

 uart_send_1();

	    uart_send_int(wenduo); //收到数据之后，发送字符串"I received."给对方
uart_send_2();
      uart_send_int(wendui); //收到数据之后，发送字符串"I received."给对方
 uart_send_3();

	    uart_send_int(gaowen); //收到数据之后，发送字符串"I received."给对方
 uart_send_4();

	    uart_send_int(diwen); //收到数据之后，发送字符串"I received."给对方
 uart_send_5();

	    uart_send_int(zkb); //收到数据之后，发送字符串"I received."给对方
			



	
		}
	}
	if(TI)// 发送数据(1字节)完毕
	{
		TI = 0;// 将 发送中断标志位 清零(让串口可以继续发送数据)
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

