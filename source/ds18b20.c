#include <reg52.h>
#include "ds18b20.h"
#include "delay.h" 
#include <string.h>
#include <intrins.h>




void DS18B20_init1()
{	 

       DQ1=0;
       delay_us(60);    //��ʱ480��960us
       DQ1=1;
       delay_us(8);   
       delay_us(40);   
       
}



void write_byte1(uchar dat)   //дһ���ֽ�
{
   uchar i;
   for(i=0;i<8;i++)
   {
      DQ1=0;  //ÿд��һλ����֮ǰ�Ȱ���������1us
     DQ1=dat&0x01;    //ȡ���λд��
     delay_us(6);   //��ʱ68us������ʱ������60us
     DQ1=1;   //Ȼ���ͷ�����
     dat=dat>>1;    //�ӵ�λ��ʼд
     delay_us(1);
	 }

}


uchar read_byte1()    //��һ���ֽ�
{
  uchar i,dat=0;
  for(i=0;i<8;i++)
  {
     DQ1=0;  //�Ƚ���������1us
_nop_();
		DQ1=1;//Ȼ���ͷ�����
     dat=dat>>1;       //�����λ��ʼ��
     if(DQ1)
		 dat=dat|0x80;   //ÿ�ζ�һλ
     delay_us(5);   //��ȡ��֮��ȴ�48us�ٽ��Ŷ�ȡ��һ����
   }
   return dat;
}









uint read_temper1 ()
{    
   uchar a,b;         
   uint t=0;
	EA=0;
   DS18B20_init1();       
   write_byte1(0xcc);   //����ROM��������
   write_byte1(0x44);     //���������¶�ת������
   DS18B20_init1();       
   write_byte1(0xcc);    //����ROM��������
   write_byte1(0xbe);      //���Ͷ��¶ȼĴ�������
   a=read_byte1();    //�ȶ��Ͱ�λ
   b=read_byte1();      //�ٶ��߰�λ
	 EA=1; 
   t=b;        
   t<<=8;      //���ư�λ
   t=t|a;      //tΪ16λ������ʹ�߰�λΪb��ֵ���Ͱ�λΪa��ֵ  
   return t;    //�����¶�ֵ

}





uint temper_change1()
{
    uint temper;
    float tp;
    temper=read_temper1();
    if(temper<0)    //���Ǹ��¶ȵ����
    {
        temper=temper-1;
        temper=~temper;
        tp=temper*0.0625;  //16λ�¶�ת����10���Ƶ��¶�
        temper=tp*100+0.5;   //������С���㣬����������
    }
    else
    {
        tp=temper*0.0625;  //16λ�¶�ת����10���Ƶ��¶�
        temper=tp*100+0.5;  //������С���㣬����������
    }
    return temper;
}

void DS18B20_init2()
{	 

       DQ2=0;
       delay_us(60);    //��ʱ480��960us
       DQ2=1;
       delay_us(8);   
       delay_us(40);   
       
}



void write_byte2(uchar dat)   //дһ���ֽ�
{
   uchar i;
   for(i=0;i<8;i++)
   {
      DQ2=0;  //ÿд��һλ����֮ǰ�Ȱ���������1us
     DQ2=dat&0x01;    //ȡ���λд��
     delay_us(6);   //��ʱ68us������ʱ������60us
     DQ2=1;   //Ȼ���ͷ�����
     dat=dat>>1;    //�ӵ�λ��ʼд
     delay_us(1);
	 }

}


uchar read_byte2()    //��һ���ֽ�
{
  uchar i,dat=0;
  for(i=0;i<8;i++)
  {
     DQ2=0;  //�Ƚ���������1us
_nop_();
		DQ2=1;  //Ȼ���ͷ�����
     dat=dat>>1;       //�����λ��ʼ��
     if(DQ2)
		 dat=dat|0x80;   //ÿ�ζ�һλ
     delay_us(5);   //��ȡ��֮��ȴ�48us�ٽ��Ŷ�ȡ��һ����
   }
   return dat;
}









uint read_temper2 ()
{    
   uchar a,b;         
   uint t=0;
	EA=0;
   DS18B20_init2();       
   write_byte2(0xcc);   //����ROM��������
   write_byte2(0x44);     //���������¶�ת������
   DS18B20_init2();       
   write_byte2(0xcc);    //����ROM��������
   write_byte2(0xbe);      //���Ͷ��¶ȼĴ�������
   a=read_byte2();    //�ȶ��Ͱ�λ
   b=read_byte2();      //�ٶ��߰�λ 
	 EA=1;
   t=b;        
   t<<=8;      //���ư�λ
   t=t|a;      //tΪ16λ������ʹ�߰�λΪb��ֵ���Ͱ�λΪa��ֵ  
   return t;    //�����¶�ֵ
	
}





uint temper_change2()
{
    uint temper;
    float tp;
    temper=read_temper2();
    if(temper<0)    //���Ǹ��¶ȵ����
    {
        temper=temper-1;
        temper=~temper;
        tp=temper*0.0625;  //16λ�¶�ת����10���Ƶ��¶�
        temper=tp*100+0.5;   //������С���㣬����������
    }
    else
    {
        tp=temper*0.0625;  //16λ�¶�ת����10���Ƶ��¶�
        temper=tp*100+0.5;  //������С���㣬����������
    }
    return temper;
}
