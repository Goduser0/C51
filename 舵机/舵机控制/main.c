#include "reg52.h"
#include "delay.h"
#include "exit_set.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit PWM = P2^0;
sbit angle0 = P1^0;
sbit angle45 = P1^1;
sbit angle90 = P1^2;
sbit angle135 = P1^3;
sbit angle180 = P1^4;

u8 change=2,i=39;

void main()
{
	T0_set(1);	
	while(1)
	{
		if(angle0==0||angle45==0||angle90==0||angle135==0||angle180==0)                                                                                                                       
		{
			delay_10us(100);
			if(angle0==0)
			{
				change = 0;
				i=39;				
				T0_set(1);
			}
			else if(angle45==0)
			{
				
				change = 1;
				i=39;
				T0_set(1);
			}
			else if(angle90==0)
			{
				
				change = 2;
				i=39;
				T0_set(1);
			}
			else if(angle135==0)
			{
				
				change = 3;
				i=39;
				T0_set(1);
			}
			else if(angle180==0)
			{
				change = 4;
				i=39;
				T0_set(1);
			}	
		}
		 
	}	
}

//ÓÐÐ§Âö³å·¶Î§£º0.5ms-2.5ms
void PWM_plus() interrupt 1
{
	TH0 = 0XFE;
	TL0 = 0X0C;
	i++;
	i%=40; //i·¶Î§£º0~39   i=0->0.5ms i=1->1.0ms i=2->1.5ms i=3->2.0ms i=4->2.5ms
	if(i<=change)
	{PWM=1;}
	else
	{PWM=0;}
}