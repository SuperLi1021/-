#include <reg52.h>
#include "anjian.h"
#include "delay.h"
void anjian()
{
		if(key1==0) 
		{yunxing=0;
		delay(10);
		if (key1==0)
		sw+=1;
		}
		if(sw==3) 
		{	if(key2==0)
		{ zkbb=1;
			 zkb+=10;}
			if(zkb>90)zkb=90;
			if(key3==0)
			{zkbb=1;
		 zkb-=10;}
			if(zkb<10) zkb=10;
			}
		if(sw==2) 
		{	if(key2==0) gaowen+=1;
			if(key3==0) gaowen-=1;}
		if(sw==1) 
		{	if(key2==0) diwen+=1;
			if(key3==0) diwen-=1;
		}
		if(sw==4){if(key2==0) {djbb=1;djb=1;}
							if(key3==0){djbb=1;djb=0;}}
		if(sw==5){if(key3==0)zkbb=0;djbb=0;}
		if(sw==6) {sw=0;yunxing=1;}
}