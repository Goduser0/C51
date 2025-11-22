#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define GPIO_MULDAT P0
#define GPIO_LED P2

sbit SHLD = P1^6;
sbit CLK_INH = P3^6;
sbit QH = P1^7;

//共阴数码管
u8 nsmg_code[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//共阳数码管
u8 psmg_code[17] = {0xC0,0xF9,0xA4,0xB0,0X99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xFF};


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

// 串转并
u8 Hc165_Read_Byte()
{
	u8 OutData = 0x00;
	u8 i = 0;
	
	//初始化
	CLK_INH = 1;
	SHLD = 1;
	
	//写入并行数据
	GPIO_MULDAT = 0x4f;
	SHLD = 0;
	delay_10us(1);
	SHLD = 1;
	delay_10us(1);
	
	//串行输出
	for(i=0;i<8;i++)
	{
		
		CLK_INH=0;
		delay_10us(1);
		
		CLK_INH=1;
		
		OutData |= QH;
		OutData = OutData<<1;
	}
	OutData = GPIO_MULDAT;
	return OutData;

}

void sin2mul()
{
	u8 dat;
	
	dat = Hc165_Read_Byte();
	while(1)
	{
		GPIO_LED = psmg_code[(dat & 0xf0)>>4];
		delay_ms(1000);
		GPIO_LED = psmg_code[dat & 0x0f];
		delay_ms(1000);
	}
}

void main()
{
	sin2mul();
}