#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define LED_COL1 P1
#define LED_COL2 P0

sbit RRCLK = P3^5;
sbit SRCLK = P3^6;
sbit SER = P3^4;

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

void Hc595_Load_Byte(u8 indata1, u8 indata2, u8 indata3, u8 indata4)
{
	u8 i = 0;
	SRCLK = 1;
	RRCLK = 1;
	
	for(i=0;i<8;i++)
	{
		SER = indata1>>7;
		indata1<<=1;
		
		SRCLK = 0;
		_nop_();
		_nop_();
		SRCLK = 1;
	}
	
	for(i=0;i<8;i++)
	{
		SER = indata2>>7;
		indata2<<=1;
		
		SRCLK = 0;
		_nop_();
		_nop_();
		SRCLK = 1;
	}

	for(i=0;i<8;i++)
	{
		SER = indata3>>7;
		indata3<<=1;
		
		SRCLK = 0;
		_nop_();
		_nop_();
		SRCLK = 1;
	}
	
	for(i=0;i<8;i++)
	{
		SER = indata4>>7;
		indata4<<=1;
		
		SRCLK = 0;
		_nop_();
		_nop_();
		SRCLK = 1;
	}
	
	RRCLK = 0;
	_nop_();
	_nop_();
	RRCLK = 1;
}

void LedMatrix()
{
	u8 row1[16] = {0x00,0x80,0x60,0xF8,0x07,0x40,0x20,0x18,0x0F,0x08,0xC8,0x08,0x08,0x28,0x18,0x00};
	u8 row2[16] = {0x01,0x00,0x00,0xFF,0x00,0x10,0x0C,0x03,0x40,0x80,0x7F,0x00,0x01,0x06,0x18,0x00};
	u8 col1[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
	u8 col2[16] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	u8 i;
	while(1)
	{
		for(i=0;i<16;i++)
		{
			Hc595_Load_Byte(col1[i],col2[i], row2[i], row1[i]);
			delay_10us(5);
		}
		delay_10us(3e4);
		
		for(i=0;i<15;i++)
		{
			Hc595_Load_Byte(col1[i],col2[i], row2[i+1], row1[i+1]);
			delay_10us(5);
		}
		delay_10us(3e4);
		
		for(i=0;i<14;i++)
		{
			Hc595_Load_Byte(col1[i],col2[i], row2[i+2], row1[i+2]);
			delay_10us(5);
		}
		
		delay_10us(3e4);
	}
}

void main()
{
	LedMatrix();
}