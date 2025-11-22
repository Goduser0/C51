#include "reg52.h"
#include "stdio.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define SMG_PORT P0

sbit LSA = P1^0;
sbit LSB = P1^1;
sbit LSC = P1^2;

//共阴数码管
u8 nsmg_code[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//共阳数码管
u8 psmg_code[17] = {0xC0,0xF9,0xA4,0xB0,0X99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xFF};

void delay_10us(u16 time)
{
	while(time--);
}

void show_one_number()
{
	u8 i;
	while(1)
	{
		for (i=0;i<17;i++)
		{
			SMG_PORT = nsmg_code[i];
			delay_10us(5e4);
		}
	}
}

void show_eight_number()
{
	u8 i;
	
	while(1)
	{
		for(i=0;i<8;i++)
		{
			switch(7-i)
			{
				case 0: LSC=1;LSB=1;LSA=1;break;
				case 1: LSC=1;LSB=1;LSA=0;break;
				case 2: LSC=1;LSB=0;LSA=1;break;
				case 3: LSC=1;LSB=0;LSA=0;break;
				case 4: LSC=0;LSB=1;LSA=1;break;
				case 5: LSC=0;LSB=1;LSA=0;break;
				case 6: LSC=0;LSB=0;LSA=1;break;
				case 7: LSC=0;LSB=0;LSA=0;break;
			}
			
			SMG_PORT = nsmg_code[i];
			delay_10us(200); //best delay time to show number meanwhile
		}
	}
}

void main()
{	
//	show_one_number();
	show_eight_number();
}