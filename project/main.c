/*********************************************************************/
/*��˾���ƣ� �������ʿ����ܵ����ɷ����޹�˾                          */
/*ģ �� ���� ��ȡ�����ź�                                          */
/*�� �� �ˣ� LICHAOFAN     ���ڣ�2021-08-13                          */
/*�� �� �ˣ� LICHAOFAN     ���ڣ�2021-08-13                          */
/*���������� ��ȡ�����ź�                                              */
/*����˵����                                                         */
/*�汾��
/**********************************************************************/
#include <intrins.h>    
#include <SN8F5702.h>
#include "display.h"
#include "sys.h"

/********************************����ȫ���ֽڱ���*********************/
unsigned int PinT;
unsigned char Level,PinBit,SWFlag,SWFlags;
/********************************����ȫ��λ����***********************/

/*********************************************************************
* �� �� ���� main
* ���������� ������
* ����˵���� ������
* ���ú����� 
* ȫ�ֱ����� PinT
* �� �룺 ��
* �� �أ� ��
* �� �� �ߣ�LICHAOFAN ���ڣ�2021-08-13
* �� �� �ߣ�LICHAOFAN ���ڣ�2021-08-13
/*�汾��
/**********************************************************************/
void main(void) 
{	
    WDTR = 0x5A;         			  //���Ź���λ  
    InitT0T1();       				  //��ʱ����ʼ��
    InitT2();
    P1M=0xfd;         			    //io�˿ڳ�ʼ��
    P0M=0XEf;	
    P0OC=0X10;
    P2M=0X00;
    Level=60;
    while (1) 
  	{  WDTR = 0x5A;

	  		switch(PinT)						//��ʾ���յ����ź�
	  		{   
	  				case 0x0277: Level=1 ;display(Level);break;
	  				case 0x026F: if(Level<=50)Level=Level+10;display(Level);break;//- 
	  				case 0x0239: Level=20;display(Level);break;
	  				case 0x027D: if(Level>=20)Level=Level-10;;display(Level);break;//+
	  				case 0x027B:SWFlags=~SWFlags;display(Level);break;//switch
	  				case 0x025F: Level=50;display(Level);break;
	  				case 0x027E: Level=60;display(Level);break;
					default:Level=0;display(Level);break; 
	  		}  
			if(SWFlags==1)
			{
				if((P1&0X02)==0x02)
				{
					
					SWFlag=1;
				}
				else
					SWFlag=0;
			}
			else
			SWFlag=0;


  	}
}





