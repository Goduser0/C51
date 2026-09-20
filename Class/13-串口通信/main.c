#include "reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

void UsartInit()
{
	TMOD = 0X20;
	TH1 = 0XF3;
	TL1 = 0XF3;
	PCON = 0X80;
	TR1 = 1;
	SCON = 0X50;
	ES = 1;
	EA = 1;
}

void main()
{
	UsartInit();
	while(1);
}

void Usart() interrupt 4
{
	u8 rec_data;
	
	rec_data = SBUF;
	RI = 0;
	SBUF = rec_data;
	while(!TI);
	TI = 0;
}
