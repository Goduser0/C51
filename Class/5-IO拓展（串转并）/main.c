#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define GPIO_LED P0

sbit SRCLK = P3^6;
sbit RRCLK = P3^5;
sbit SER = P3^4;

u8 ghc595_buf[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

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

void Hc595_Send_Byte(u8 dat)
{
	u8 i=0;
	
	for(i=0;i<8;i++)
	{
		SER=dat>>7;
		dat<<=1;
		SRCLK=0;
		delay_10us(1);
		SRCLK=1;
		delay_10us(1);
	}
	
	RRCLK=0;
	delay_10us(1);
	RRCLK=1;
}

// ´®×ª²¢
void sin2mul()
{
	u8 i = 0;
	GPIO_LED = 0x00;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			Hc595_Send_Byte(0x00);
			Hc595_Send_Byte(ghc595_buf[i]);
			delay_ms(500);
		}
	}
}

void main()
{
	sin2mul();
}