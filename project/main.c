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
unsigned char Level,PinBit,SWFlag;
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
    P1M=0xff;         			    //io�˿ڳ�ʼ��
    P0M=0XEf;	
    P0OC=0X10;
    P2M=0X00;
    Level=60;
    while (1) 
  	{  WDTR = 0x5A;

	  		switch(PinT)						//��ʾ���յ����ź�
	  		{   
	  				case 0x0277: Level=1 ;display(Level);break;
	  				case 0x026F: Level=10;display(Level);break;//- 
	  				case 0x0239: Level=20;display(Level);break;
	  				case 0x027D: Level=30;display(Level);break;//+
	  				case 0x027B: Level=40;display(Level);break;//switch
	  				case 0x025F: Level=50;display(Level);break;
	  				case 0x027E: Level=60;display(Level);break;
					default:Level=0;display(Level);break; 
	  		}  
			switch(P0&0X01)
			{
				case 0:SWFlag=0;break;
				case 1:SWFlag=1;break;
			}

  	}
}





