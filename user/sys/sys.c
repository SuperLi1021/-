/*********************************************************************/
/*公司名称： 深圳市朗科智能电气股份有限公司                          */
/*模 块 名： 系统模块                                                */
/*创 建 人： LICHAOFAN     日期：2021-08-13                          */
/*修 改 人： LICHAOFAN     日期：2021-08-13                          */
/*功能描述： 提供定时，延时，信号抓取，信号处理				         */
/*其他说明：                                                         */
/*版本：                                                             */
/*********************************************************************/

#include <SN8F5702.h>
/********************************定义全局位变量***********************/
bit PinFlag;

/********************************定义全局字节变量*********************/
extern unsigned int PinT;
extern unsigned char Level,PinBit,SWFlag,HWFlag,sw;

/*********************************************************************
* 函 数 名： InitT0T1
* 功能描述： 对定时器初始化
* 函数说明： 定时器初始化函数
* 调用函数： 
* 全局变量：
* 输 入： 无
* 返 回： 无
* 设 计 者：LICHAOFAN 日期：2021-08-13
* 修 改 者：LICHAOFAN 日期：2021-08-13
/*版本：
/**********************************************************************/
void InitT0T1(void)
{	
	TH1   = 0x9b;	 			   //装入初值
	TL1   = 0x9b;
	TH0   = 0x9B;				 	 //装入初值
	TL0   = 0x9B;
	TMOD  = 0x66;					 //使用T0 T1 自动装填模式
	TCON0 = 0x22;					 //外分频控制 /32
	TCON  = 0x50;					 //启动定时器T0 T1 的功能控制位
	IEN0  = 0x8A;					 //使能中断
}


/*********************************************************************
* 函 数 名： InitT2
* 功能描述： 对定时器t2初始化
* 函数说明： 定时器t2初始化函数
* 调用函数： 
* 全局变量：
* 输 入： 无
* 返 回： 无
* 设 计 者：LICHAOFAN 日期：2021-08-16
* 修 改 者：LICHAOFAN 日期：2021-08-16
/*版本：
/**********************************************************************/
void InitT2(void)
{	
	TH2 = 0xE5;						//定时2.5ms
	TL2 = 0xF5;
	T2CON = 0x00;
	IEN0 |= 0xA0;					//使能T2中断

}			 
/*********************************************************************
* 函 数 名： T2Interrupt
* 功能描述： 输出2.5ms低电平
* 函数说明： T2中断处理函数
* 调用函数： 
* 全局变量：
* 输 入： 无
* 返 回： 无
* 设 计 者：LICHAOFAN 日期：2021-08-13
* 修 改 者：LICHAOFAN 日期：2021-08-13
/*版本：
/**********************************************************************/
void T2Interrupt(void) interrupt ISRTimer2
{ 	static bit MotorFlag;
   	TH2 = 0xE5;											//重装初值
  	TL2 = 0xF5;
    if ((IRCON & 0x40) ==0x40)
    {
       IRCON &= 0xBF; 							// TF2清零

			if(MotorFlag==0)
				{
				
					P05=0;										//输出2.5ms低电平
					MotorFlag=1;
			    return;
				}
			
			if(MotorFlag==1)							//输出完毕，关闭定时器2
				{
					MotorFlag=0;	
					P05=1;
					T2CON =0x00;
          return;
				}
    }
}
/*********************************************************************
* 函 数 名： T1Interrupt
* 功能描述： 抓取信号中单个bit
* 函数说明： T1中断处理函数
* 调用函数： 
* 全局变量： PinBit，PinFlag
* 输 入： 无
* 返 回： 无
* 设 计 者：LICHAOFAN 日期：2021-08-13
* 修 改 者：LICHAOFAN 日期：2021-08-13
/*版本：
/**********************************************************************/
void T1Interrupt(void) interrupt ISRTimer1 
{		
	/********************************定义字节变量***********************/
		static unsigned char i,PinH,PinL;
		i++;
   	if(i<10)														//每100us取一次值，比较高低电平的数量
   	{
   		if((P0&0x10)==0X10)
   			PinH++;
   		else
   			PinL++;
   		
   	}
   	else
   	{
   		i=0;
   		if(PinH>PinL)											//高电平多则该BIT为1
   		{PinBit=1;
            P00=1;
       }
   		else															//反之为0
   		{
   			PinBit=0;
        P00=0;
   		}
   		PinH=0;														//对计数值清零，将获取成功标志位置1，关闭定时器1
   		PinL=0;
   		PinFlag=1;
   		TR1=0;
  	}
   	
   
}
/*********************************************************************
* 函 数 名： T0Interrupt
* 功能描述： 定时100us，抓取信号跳变，选择t1开启时间，对信号进行处理
* 函数说明： T0中断处理函数
* 调用函数： 
* 全局变量：  PinBit，PinFlag，PinT
* 输 入： 无
* 返 回： 无
* 设 计 者：LICHAOFAN 日期：2021-08-16
* 修 改 者：LICHAOFAN 日期：2021-08-16
/*版本：
/**********************************************************************/
void T0Interrupt(void) interrupt ISRTimer0 
{		/********************************定义字节变量***********************/
    static	unsigned int PinData,DataError,PinOld,HWTimes,PinT1;
    static	unsigned char DataF,TIME,P07Old,P07Time,ZeroOld;
    /********************************定义位变量*************************/
    static  bit P07Flag,delaytime;
    TIME++;
    if(TIME>=100)
    {TIME=0;
    P00=~P00;}														//模拟过零信号




    if((P0&0X10)!=ZeroOld)							//抓取p04下降沿
		{  delaytime=1;
 	     if((P0&0X10)==0)                  //若有则接收到红外信号，取下降沿作为触发
    	{
     		
    		TR1=1;													//若抓到下降沿，则打开t1定时器获取数据
    		DataF++;
    					
  		 }
			DataError=0;
          												
	    ZeroOld=(P0&0x10);								
	    
	  }
	  else if(delaytime==1)
     	 DataError++;	 
    if(DataError==600)									//当6ms没有收到红外信号，就认为此轮信号接收完成
    {
  	 	//	DataError=0;											//对计数值清零
   	 		DataF=0;
   	 	HWTimes++;
    }
   
    if(DataError==1500)
	{   delaytime=0;
		DataError=0;
		HWFlag=1;
	}
     
     
     
     
    if(DataF>=1)												//读取信号
   	{
				
				if(PinFlag==1)											//当有信号bit被完全获取
				{	
							  PinFlag=0;
							  PinData=(PinData<<1)+PinBit;		//记录
						if(DataF==12)													//当其为最后一位时
						{  
								if(PinOld==PinData)									//与上一次收到的值进行比较
								{   
									PinFlag=0;
								     PinT1=PinData;
					        		PinData=0;
  								}
								else																//否则记录下该值
									PinOld=PinData;
								PinData=0;
  		    					DataF=0;
  		    					PinFlag=0;
  		    					
						} 
						
				}
    
   

		}
		if((P2&0X01)!=P07Old)							//抓取过零信号
		{  
 		    P07Flag=1;
//			P05=~P05;
		    P07Old=(P2&0x01);
	    
		}
		if(P07Flag==1)										//当有过零时 计数加一
		{   
		  	P07Time++;
		}
		if(P07Time>=Level)								//当计数值大于规定值时，打开T2计时器，输出2.5ms的低电平
		{     	if(SWFlag==1)
                {  TH2 = 0xFF;
		   	         TL2 = 0xFE;
			    	T2CON =0x01;
                    }
				P07Time=0;
				P07Flag=0;
				
		}
        	if(HWFlag==1)											//相同则获取成功
									{
									     sw=1;
									     HWFlag=0;
										PinT=PinT1;
                                        PinT1=0x00;
									}

		
	  
}
  
/*********************************************************************
* 函 数 名： Delay100us
* 功能描述： 提供100us延时
* 函数说明： 延时函数
* 调用函数： _nop_()
* 全局变量：
* 输 入： unsigned int n
* 返 回： 无
* 设 计 者：LICHAOFAN 日期：2021-08-13
* 修 改 者：LICHAOFAN 日期：2021-08-13
/*版本：
/**********************************************************************/
void Delay100us(unsigned char n)
{
    unsigned char i, j;
    i = 0;
    j = 0;
    for (i=0; i<n; i++) 
    {
        for (j=0; j<2; j++) 
        {
	    	 _nop_(); _nop_();  _nop_(); _nop_();
			 _nop_();  _nop_(); _nop_(); _nop_();
        }
    }
}

