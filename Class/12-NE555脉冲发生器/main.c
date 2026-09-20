#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define GPIO_DEG P0
sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

u8 SMG[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
unsigned long freq=0, show_freq=0;

void delay(u16 i)
{
	while(i--);	
}

void DisPlay(u16 outdata)
{
	u8 Display_Data[8];
	u8 i;
	
	Display_Data[0] = SMG[outdata / 10000000];
	Display_Data[1] = SMG[outdata%10000000 / 1000000];
	Display_Data[2] = SMG[outdata%1000000 / 100000];
	Display_Data[3] = SMG[outdata%100000 / 10000];
	Display_Data[4] = SMG[outdata%10000 / 1000];
	Display_Data[5] = SMG[outdata%1000 / 100];
	Display_Data[6] = SMG[outdata%100 / 10];
	Display_Data[7] = SMG[outdata%10 / 1];
	
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case(0): LSA=0;LSB=0;LSC=0;break;
			case(1): LSA=1;LSB=0;LSC=0;break;
			case(2): LSA=0;LSB=1;LSC=0;break;
			case(3): LSA=1;LSB=1;LSC=0;break;
			case(4): LSA=0;LSB=0;LSC=1;break;
			case(5): LSA=1;LSB=0;LSC=1;break;
			case(6): LSA=0;LSB=1;LSC=1;break;
			case(7): LSA=1;LSB=1;LSC=1;break;
		}
		
		GPIO_DEG = Display_Data[i];
		delay(100);
		GPIO_DEG = 0x00;
	}
}

void Timer_init()
{
	TMOD = 0x51;
	TH1 = 0x00;
	TL1 = 0x00;
	TH0 = 0xFC;
	TL0 = 0x18;
	
	ET1= 1;
	TR1 = 1;
	ET0 =1;
	TR0 = 1;
	
	EA = 1;
}

void Timer0() interrupt 1
{
	static u16 count;
	TH0 = 0xFC;
	TL0 = 0x18;
	count++;
	
	if(count == 1000)
	{
		freq += TL1;
		freq += TH1*256;
		
		if(freq != show_freq)
		{
			show_freq = freq;
		}
		count = 0;
		freq = 0;
		
		TH1 = 0x00;
		TL1 = 0x00;
	}
}

void Timer1() interrupt 3
{
	freq += 65536;
}

void main()
{
	Timer_init();
	while(1)
	{
		DisPlay(show_freq);
	}
}


