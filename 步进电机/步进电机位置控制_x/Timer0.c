#include "reg52.h"

//��ʱ��0�ж��趨
void T0_set(bit T0)//T0==1��ʼ������T0==0ֹͣ����
{
	//��ʱģʽ����ʽ1
	TMOD |= 0X01;
	//��ֵ�趨
	TH0 = 0XF2;
	TL0 = 0X54;

	TR0 = T0;
	ET0 = 1;
	EA = 1;
}