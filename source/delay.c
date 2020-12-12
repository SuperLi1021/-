#include <intrins.h>



#include "delay.h"










/*延时xms函数*/
void delay(uint xms){
	uint i, j;
	for(i = xms; i > 0; i--)
		for(j = 110; j > 0; j--);
}

void delay_us(uint n)    //延时约16微妙
{   
    while(n--);
   }