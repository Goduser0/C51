#include "reg52.h"
#include "delay.h"

sbit motor_INT1=P3^4;
sbit motor_INT2=P3^5;
sbit motor_INT3=P3^6;
sbit motor_INT4=P3^7;

void motor_out(unsigned char rec)
{
	switch(rec)
	{
		case 0:motor_INT1=1;motor_INT2=0;motor_INT3=0;motor_INT4=1;break;
		case 1:motor_INT1=0;motor_INT2=1;motor_INT3=1;motor_INT4=0;break;
		case 2:motor_INT1=1;motor_INT2=0;motor_INT3=1;motor_INT4=0;break;
		case 3:motor_INT1=0;motor_INT2=1;motor_INT3=0;motor_INT4=1;break;
		default:motor_INT1=0;motor_INT2=0;motor_INT3=0;motor_INT4=0;break;
	}
	delay_10us(100000);
	motor_INT1=0;motor_INT2=0;motor_INT3=0;motor_INT4=0;
}