#include "reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit buzzer = P2^5;

void delay_10us(u16 ten_us)
{
	while(ten_us--);
}

void main()
{
	u16 high_time;
	u16 delay_times;
	while(1)
	{	
		for(high_time=0;high_time<501;high_time+=5)
		{
			delay_times = 5;
			while(delay_times--)
				{
				buzzer = 1;
				delay_10us(high_time);
				buzzer = 0;
				delay_10us(500-high_time);
				}
		}
		for(high_time=0;high_time<501;high_time+=5)
		{
			delay_times = 5;
			while(delay_times--)
				{
				buzzer = 1;
				delay_10us(500-high_time);
				buzzer = 0;
				delay_10us(high_time);
				}
		}
	}
}