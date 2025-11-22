#include "reg52.h"
typedef unsigned int u16;
typedef unsigned char u8;

#define SMG_PORT P0
#define BUTTON P2

u8 psmg_code[17] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0xFF};	

void delay_10us(u16 time)
{
	while(time--);
}

int single_button_scan()
{
	static single_key_value=0;
	single_key_value=0;
	BUTTON = 0xff;
	
	if(BUTTON != 0xff)
	{
		delay_10us(1000);
		if(BUTTON != 0xff)
		{
			switch(BUTTON)
			{
				case 0x7f: single_key_value=1; break;
				case 0xbf: single_key_value=2; break;
				case 0xdf: single_key_value=3; break;
				case 0xef: single_key_value=4; break;
				case 0xf7: single_key_value=5; break;
				case 0xfb: single_key_value=6; break;
				case 0xfd: single_key_value=7; break;
				case 0xfe: single_key_value=8; break;
			}
		}
	}
	
	return single_key_value;
	
}

void single_button_detect()
{
	u8 key;
	SMG_PORT = 0x00;
	while(1)
	{
		key = single_button_scan();
		SMG_PORT = psmg_code[key];
	}
}

int matrix_button_scan()
{
	static key_value = 0;
	u8 temp_1, temp_2;
	
	BUTTON = 0x0f;
	if(BUTTON != 0x0f)
	{
		delay_10us(1000);
		if(BUTTON != 0x0f)
		{
			temp_1 = BUTTON;
			BUTTON = 0xf0;
			temp_2  =BUTTON;
			
			switch(temp_1)
			{
				case 0x07: key_value=1;break;
				case 0x0b: key_value=2;break;
				case 0x0d: key_value=3;break;
				case 0x0e: key_value=4;break;
			}
			switch(temp_2)
			{
				case 0x70: key_value=key_value + 0*4;break;
				case 0xb0: key_value=key_value + 1*4;break;
				case 0xd0: key_value=key_value + 2*4;break;
				case 0xe0: key_value=key_value + 3*4;break;
			}
		}
	}
	
	
	return key_value;
}

void matrix_button_detect()
{
	u8 key;
	SMG_PORT = 0xff;
	while(1)
	{
		key = matrix_button_scan();
		SMG_PORT = psmg_code[key];
	}
}


void main()
{
//	single_button_detect();
	matrix_button_detect();
}