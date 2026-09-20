#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit LED1 = P2^0;
sbit KEY = P3^2;

void delay_10us(u16 ten_us)
{
	while(ten_us--);
}

void delay_ms(u16 ms)
{
	u16 i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

void exit0_init()
{
	EA = 1;
	IT0 = 1;
	EX0 = 1;
}

void exit0() interrupt 0
{
	delay_10us(1000);
	if(KEY == 0)
	{
		LED1=~LED1;
	}
}

void main()
{
	exit0_init();
	
	while(1)
	{
	}
}