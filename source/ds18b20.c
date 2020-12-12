#include <reg52.h>
#include "ds18b20.h"
#include "delay.h" 
#include <string.h>
#include <intrins.h>




void DS18B20_init1()
{	 

       DQ1=0;
       delay_us(60);    //延时480到960us
       DQ1=1;
       delay_us(8);   
       delay_us(40);   
       
}



void write_byte1(uchar dat)   //写一个字节
{
   uchar i;
   for(i=0;i<8;i++)
   {
      DQ1=0;  //每写入一位数据之前先把总线拉低1us
     DQ1=dat&0x01;    //取最低位写入
     delay_us(6);   //延时68us，持续时间最少60us
     DQ1=1;   //然后释放总线
     dat=dat>>1;    //从低位开始写
     delay_us(1);
	 }

}


uchar read_byte1()    //读一个字节
{
  uchar i,dat=0;
  for(i=0;i<8;i++)
  {
     DQ1=0;  //先将总线拉低1us
_nop_();
		DQ1=1;//然后释放总线
     dat=dat>>1;       //从最低位开始读
     if(DQ1)
		 dat=dat|0x80;   //每次读一位
     delay_us(5);   //读取完之后等待48us再接着读取下一个数
   }
   return dat;
}









uint read_temper1 ()
{    
   uchar a,b;         
   uint t=0;
	EA=0;
   DS18B20_init1();       
   write_byte1(0xcc);   //跳过ROM操作命令
   write_byte1(0x44);     //发送启动温度转换命令
   DS18B20_init1();       
   write_byte1(0xcc);    //跳过ROM操作命令
   write_byte1(0xbe);      //发送读温度寄存器命令
   a=read_byte1();    //先读低八位
   b=read_byte1();      //再读高八位
	 EA=1; 
   t=b;        
   t<<=8;      //左移八位
   t=t|a;      //t为16位的数，使高八位为b的值，低八位为a的值  
   return t;    //返回温度值

}





uint temper_change1()
{
    uint temper;
    float tp;
    temper=read_temper1();
    if(temper<0)    //考虑负温度的情况
    {
        temper=temper-1;
        temper=~temper;
        tp=temper*0.0625;  //16位温度转换成10进制的温度
        temper=tp*100+0.5;   //留两个小数点，并四舍五入
    }
    else
    {
        tp=temper*0.0625;  //16位温度转换成10进制的温度
        temper=tp*100+0.5;  //留两个小数点，并四舍五入
    }
    return temper;
}

void DS18B20_init2()
{	 

       DQ2=0;
       delay_us(60);    //延时480到960us
       DQ2=1;
       delay_us(8);   
       delay_us(40);   
       
}



void write_byte2(uchar dat)   //写一个字节
{
   uchar i;
   for(i=0;i<8;i++)
   {
      DQ2=0;  //每写入一位数据之前先把总线拉低1us
     DQ2=dat&0x01;    //取最低位写入
     delay_us(6);   //延时68us，持续时间最少60us
     DQ2=1;   //然后释放总线
     dat=dat>>1;    //从低位开始写
     delay_us(1);
	 }

}


uchar read_byte2()    //读一个字节
{
  uchar i,dat=0;
  for(i=0;i<8;i++)
  {
     DQ2=0;  //先将总线拉低1us
_nop_();
		DQ2=1;  //然后释放总线
     dat=dat>>1;       //从最低位开始读
     if(DQ2)
		 dat=dat|0x80;   //每次读一位
     delay_us(5);   //读取完之后等待48us再接着读取下一个数
   }
   return dat;
}









uint read_temper2 ()
{    
   uchar a,b;         
   uint t=0;
	EA=0;
   DS18B20_init2();       
   write_byte2(0xcc);   //跳过ROM操作命令
   write_byte2(0x44);     //发送启动温度转换命令
   DS18B20_init2();       
   write_byte2(0xcc);    //跳过ROM操作命令
   write_byte2(0xbe);      //发送读温度寄存器命令
   a=read_byte2();    //先读低八位
   b=read_byte2();      //再读高八位 
	 EA=1;
   t=b;        
   t<<=8;      //左移八位
   t=t|a;      //t为16位的数，使高八位为b的值，低八位为a的值  
   return t;    //返回温度值
	
}





uint temper_change2()
{
    uint temper;
    float tp;
    temper=read_temper2();
    if(temper<0)    //考虑负温度的情况
    {
        temper=temper-1;
        temper=~temper;
        tp=temper*0.0625;  //16位温度转换成10进制的温度
        temper=tp*100+0.5;   //留两个小数点，并四舍五入
    }
    else
    {
        tp=temper*0.0625;  //16位温度转换成10进制的温度
        temper=tp*100+0.5;  //留两个小数点，并四舍五入
    }
    return temper;
}
