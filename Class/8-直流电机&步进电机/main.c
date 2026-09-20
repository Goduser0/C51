#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit MOTOA = P1^0;
sbit MOTOB = P1^1;
sbit MOTOC = P1^2;
sbit MOTOD = P1^3;

#define SPEED 400

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

void main()
{
	P1= 0x00;
	
	while(1)
	{
		//A+
		MOTOA = 1;
		MOTOB = 0;
		MOTOC = 1;
		MOTOD = 0;
		delay_10us(SPEED);
		
		MOTOA = 0;
		MOTOB = 1;
		MOTOC = 1;
		MOTOD = 0;
		delay_10us(SPEED);
		
		//A-
		MOTOA = 0;
		MOTOB = 1;
		MOTOC = 0;
		MOTOD = 1;
		delay_10us(SPEED);
		
		MOTOA = 1;
		MOTOB = 0;
		MOTOC = 0;
		MOTOD = 1;
		delay_10us(SPEED);
	}
}