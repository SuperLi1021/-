#include <intrins.h>



#include "delay.h"










/*��ʱxms����*/
void delay(uint xms){
	uint i, j;
	for(i = xms; i > 0; i--)
		for(j = 110; j > 0; j--);
}

void delay_us(uint n)    //��ʱԼ16΢��
{   
    while(n--);
   }