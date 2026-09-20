#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit LED1 = P2^0;

void Timer0_init()
{
	TMOD |= 0x01;
	TH0 = 0xFC;
	TL0 = 0x18;
	
	ET0 = 1;
	EA = 1;
	
	TR0 = 1;
}

void Timer0() interrupt 1
{
	static u16 count;
	
	TH0 = 0xFC;
	TL0 = 0x18;
	count++;
	
	if(count == 1000)
	{
		count = 0;
		LED1=~LED1;
	}
}

void main()
{
	Timer0_init();
	
	while(1)
	{
	}
}