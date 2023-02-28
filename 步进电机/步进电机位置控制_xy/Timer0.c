#include "reg52.h"

//计时器0中断设定
void T0_set(bit T0)//T0==1开始工作，T0==0停止工作
{
	//计时模式；方式1
	TMOD |= 0X01;
	//初值设定
	TH0 = 0XF2;
	TL0 = 0X54;

	TR0 = T0;
	ET0 = 1;
	EA = 1;
}