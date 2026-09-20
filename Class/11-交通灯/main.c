#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define GPIO_DEG P0
#define GPIO_TRAFFIC P1

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

sbit P1_R = P1^0;
sbit P1_G = P1^1;

sbit C1_R = P1^2;
sbit C1_Y = P1^3;
sbit C1_G = P1^4;

sbit C2_R = P1^5;
sbit C2_Y = P1^6;
sbit C2_G = P1^7;

sbit P2_G = P3^0;
sbit P2_R = P3^1;

u8 SMG[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

u8 Display_Data[8];

u8 Sec=1;

void delay(u16 i)
{
	while(i--);	
}

void Timer0_init()
{
	TMOD |= 0x01;
	// 1ms
	TH0 = 0xFC; 
	TL0 = 0x18;
	
	ET0 = 1;
	EA = 1;
	
	TR0 = 1;
}

void DisPlay()
{
	u8 i;
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

void main()
{
	Timer0_init();
	
	while(1)
	{
		if(Sec<=7)
		{
			Display_Data[0]=0x00;
			Display_Data[1]=0x00;
			Display_Data[2]=SMG[(11-Sec) / 10];
			Display_Data[3]=SMG[(11-Sec) % 10];
			Display_Data[4]=0x00;
			Display_Data[5]=0x00;
			Display_Data[6]=SMG[(8-Sec) / 10];
			Display_Data[7]=SMG[(8-Sec) % 10];
			DisPlay();
			
			C1_R=0;
			C1_Y=1;
			C1_G=1;
			C2_R=1;
			C2_Y=1;
			C2_G=0;
			P1_R=0;
			P1_G=~P1_R;
			P2_R=1;
			P2_G=~P2_R;
		}
		else if(Sec<=10)
		{
			Display_Data[0]=0x00;
			Display_Data[1]=0x00;
			Display_Data[2]=SMG[(11-Sec) / 10];
			Display_Data[3]=SMG[(11-Sec) % 10];
			Display_Data[4]=0x00;
			Display_Data[5]=0x00;
			Display_Data[6]=SMG[(11-Sec) / 10];
			Display_Data[7]=SMG[(11-Sec) % 10];
			DisPlay();
			
			C1_R=0;
			C1_Y=1;
			C1_G=1;
			C2_R=1;
			C2_Y=0;
			C2_G=1;
			P1_R=0;
			P1_G=~P1_R;
			P2_R=1;
			P2_G=~P2_R;
		}
		else if(Sec<=17)
		{
			Display_Data[0]=0x00;
			Display_Data[1]=0x00;
			Display_Data[2]=SMG[(18-Sec) / 10];
			Display_Data[3]=SMG[(18-Sec) % 10];
			Display_Data[4]=0x00;
			Display_Data[5]=0x00;
			Display_Data[6]=SMG[(21-Sec) / 10];
			Display_Data[7]=SMG[(21-Sec) % 10];
			DisPlay();
			
			C1_R=1;
			C1_Y=1;
			C1_G=0;
			C2_R=0;
			C2_Y=1;
			C2_G=1;
			P1_R=1;
			P1_G=~P1_R;
			P2_R=0;
			P2_G=~P2_R;
		}
		else if(Sec<=20)
		{
			Display_Data[0]=0x00;
			Display_Data[1]=0x00;
			Display_Data[2]=SMG[(21-Sec) / 10];
			Display_Data[3]=SMG[(21-Sec) % 10];
			Display_Data[4]=0x00;
			Display_Data[5]=0x00;
			Display_Data[6]=SMG[(21-Sec) / 10];
			Display_Data[7]=SMG[(21-Sec) % 10];
			DisPlay();
			
			C1_R=1;
			C1_Y=0;
			C1_G=1;
			C2_R=0;
			C2_Y=1;
			C2_G=1;
			P1_R=1;
			P1_G=~P1_R;
			P2_R=0;
			P2_G=~P2_R;
		}
	}
}

void Timer0() interrupt 1
{
	static u16 count;
	
	TH0 = 0xFC;
	TL0 = 0x18;
	count++;
	
	if(count == 1000) // 1s
	{
		count = 0;
		Sec++;
		if(Sec>20)
		{
			Sec=1;
		}
	}
}