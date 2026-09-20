#include "reg52.h"
#include "delay.h"
#include "exit_set.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit PWM_0 = P2^0;
sbit PWM_1 = P2^1;

u8 angle=0,t=0,level_0=0, level_1=0;

void main()	
{
	T0_set(1);
	T1_set(1);
	while(1)
	{
		
		angle = 0;
		
		t=20;
		while(t--)
		{
			delay_10us(10000);
		}
		
		angle = 1;
		
		t=20;
		while(t--)
		{
			delay_10us(10000);
		}
	}
}

//有效脉冲范围：0.5ms-2.5ms 总脉冲长度：20ms
void PWM0_plus() interrupt 1
{	
	if(angle==0)
	{
		if(level_0==0)
		{
			TH0 = 0XFE;
			TL0 = 0X33;
		}
		else
		{
			TH0 = 0XB9;
			TL0 = 0XCC;
		}
	}
	else
	{
		if(level_0==0)
		{
			TH0 = 0XF8;
			TL0 = 0X39;
		}
		else
		{
			TH0 = 0XBF;
			TL0 = 0XC6;
		}
	}
	level_0 = !level_0;
	PWM_0 = level_0;
}

void PWM1_plus() interrupt 3
{
	if(angle==0)
	{
		if(level_1==0)
		{
			TH1 = 0xF8;
			TL1 = 0x39;
		}
		else
		{
			TH1 = 0xBF;
			TL1 = 0xC6;
		}
	}
	else
	{
		if(level_1==0)
		{
			TH1 = 0xFE;
			TL1 = 0x33;
		}
		else
		{
			TH1 = 0xB9;
			TL1 = 0xCC;
		}
	}
	level_1 = !level_1;
	PWM_1 = level_1;
}