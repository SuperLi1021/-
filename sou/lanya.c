
#include <reg52.h>
#include "lanya.h"

#include "delay.h"

uint db=0;
uchar lb,mb,hb;

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
void uart_send_str(unsigned char *s)
{
	while(*s != '\0')// '\0':字符串结束标志
	{
		uart_send_byte(*s);// 发送1个字节数据，1个字符占8位，1字节
		s++;// 指向下一个字符
	}
}

void uart_interrupt(void) interrupt 4 		//也叫串行中断服务程序
{	
	unsigned char send_data1[]="ireceive" ;// 要发送的信息

	unsigned char recv_data;// 用来存放接收到的数据
	unsigned int send_data[3] ;
	unsigned char send_data0[3] ;// 要发送的信息
	unsigned char send_data2[3] ;// 要发送的信息
	unsigned char send_data3[3] ;// 要发送的信息
	unsigned char send_data4[3] ;// 要发送的信息
	unsigned char send_data5[3] ;// 要发送的信息
	unsigned char send_data6[3] ;// 要发送的信息
	unsigned char send_data7[3] ;// 要发送的信息
	unsigned char send_data8[3] ;// 要发送的信息
	unsigned char send_data9[3] ;// 要发送的信息

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

	if(RI) //接收数据(1字节)完毕，RI会被硬件置1
	{
		RI = 0;            		// 将 接收中断标志位 清零(让串口可以继续接收数据)
		recv_data = SBUF;           	//读取接收到的数据，并存放到data
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
	if(recv_data==0x0a){lb=0;diwen=db;db=0;}//低温阈值
  	if(recv_data==0x0b){lb=0;gaowen=db;db=0;}//高温阈值
	if(recv_data==0x0d){lb=0; pl =db;db=0;}//频率
	if(recv_data==0x0e){lb=0; zkb =db;db=0;}//占空比

	}
		if(recv_data ==0x0a){
		lb=1;	}




	
		
	    uart_send_str(send_data2); //收到数据之后，发送字符串"I received."给对方
	    uart_send_str(send_data4); //收到数据之后，发送字符串"I received."给对方
	    uart_send_str(send_data6); //收到数据之后，发送字符串"I received."给对方
	    uart_send_str(send_data8); //收到数据之后，发送字符串"I received."给对方
	    uart_send_str(send_data0); //收到数据之后，发送字符串"I received."给对方
	}
	if(TI)// 发送数据(1字节)完毕
	{
		TI = 0;// 将 发送中断标志位 清零(让串口可以继续发送数据)
	}

} 

