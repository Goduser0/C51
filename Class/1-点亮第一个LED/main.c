#include "reg52.h"
#define LED_PORT P2
typedef unsigned int u16;
typedef unsigned char u8;

sbit LED1 = P0^0;

void delay_10us(u16 ten_us)
{
	while(ten_us--);
}


void blink()
{
	u16 delay_time = 10000;
	while(1)
	{	
		LED1 = 1;
		delay_10us(delay_time);
		LED1 = 0;
		delay_10us(delay_time);
	}
}

void horse_race_lamp()
{
	u8 i;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			LED_PORT = 0x01<<i;
			delay_10us(10000);
		}
		for(i=0;i<8;i++)
		{
			LED_PORT = 0x80>>i;
			delay_10us(10000);
		}

	}
}

void main()
{
	//blink();
	horse_race_lamp();
}