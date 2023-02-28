#include "reg52.h"

//外部中断0设定, 管脚P3.2
void INT0_set()
{
	IT0 = 0; //设定为低电平触发
	EX0 = 1;
	EA = 1;   
}

//外部中断1设定，管脚P3.3
void INT1_set()
{
	IT1 = 0; //设定为低电平触发
	EX1 = 1;
	EA = 1;	
}

//计时器0中断设定
void T0_set(bit T0)//T0==1开始工作，T0==0停止工作
{
	//计时模式；方式1
	TMOD |= 0X01;
	//初值设定
	TH0 = 0XFF;
	TL0 = 0X9C;

	TR0 = T0;
	ET0 = 1;
	EA = 1;
}

//计时器1中断设定
void T1_set()
{
	//计时模式；方式1
	TMOD |= 0X10;
    //初值设定
	TH1 = 0X00;
	TL1 = 0X00;

	TR1 = 1;
	ET1 = 1;
	EA = 1;
}






