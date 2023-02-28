#include "reg52.h"
#include "delay.h"
#include "interrupt_set.h"
#include "PWM_OUT.h"
#include "motor.h"

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

sbit IRIN=P3^2;
unsigned char IrValue[6];
unsigned char Time;  
 
unsigned char DisplayData[8];
unsigned char code smgduan[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0X76};


void DigDisplay()
{
	unsigned char i;
	for(i=0;i<3;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ	
		}
		P0=DisplayData[i];//��������
		delay_10us(100); //���һ��ʱ��ɨ��	
		P0=0x00;//����
	}		
}

void main()
{
	INT0_set();
	IRIN=1;
	pwm_send();
	while(1)
	{
		if (IrValue[2]==0X07)
		{pwm_send(0);IrValue[2]=0X00;}
		else if (IrValue[2]==0X15)
		{pwm_send(1);IrValue[2]=0X00;}
		else if (IrValue[2]==0X44)
		{pwm_send(2);IrValue[2]=0X00;}
		else if (IrValue[2]==0X40)
		{pwm_send(3);IrValue[2]=0X00;}
		
		else if (IrValue[2]==0X5A)
		{motor_out(0);IrValue[2]=0X00;}
		else if (IrValue[2]==0X08)
		{motor_out(1);IrValue[2]=0X00;}
		else if (IrValue[2]==0X18)
		{motor_out(2);IrValue[2]=0X00;}
		else if (IrValue[2]==0X1C)
		{motor_out(3);IrValue[2]=0X00;}

//		DisplayData[0] = smgduan[IrValue[2]/16];
//		DisplayData[1] = smgduan[IrValue[2]%16];
//		DisplayData[2] = smgduan[16];
//	    DigDisplay();	
	}
}

void ReadIr() interrupt 0
{
	unsigned char j,k;
	unsigned int err;
	Time=0;					 
	delay_10us(700);	//7ms
	if(IRIN==0)		//ȷ���Ƿ���Ľ��յ���ȷ���ź�
	{	 
		
		err=1000;				//1000*10us=10ms,����˵�����յ�������ź�
		/*������������Ϊ����ѭ���������һ������Ϊ�ٵ�ʱ������ѭ������ó�������ʱ
		�������������*/	
		while((IRIN==0)&&(err>0))	//�ȴ�ǰ��9ms�ĵ͵�ƽ��ȥ  		
		{			
			delay_10us(1);
			err--;
		} 
		if(IRIN==1)			//�����ȷ�ȵ�9ms�͵�ƽ
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //�ȴ�4.5ms����ʼ�ߵ�ƽ��ȥ
			{
				delay_10us(1);
				err--;
			}
			for(k=0;k<4;k++)		//����4������
			{				
				for(j=0;j<8;j++)	//����һ������
				{

					err=60;		
					while((IRIN==0)&&(err>0))//�ȴ��ź�ǰ���560us�͵�ƽ��ȥ
					{
						delay_10us(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //����ߵ�ƽ��ʱ�䳤�ȡ�
					{
						delay_10us(10);	 //0.1ms
						Time++;
						err--;
						if(Time>30)
						{
							return;
						}
					}
					IrValue[k]>>=1;	 //k��ʾ�ڼ�������
					if(Time>=8)			//����ߵ�ƽ���ִ���565us����ô��1
					{
						IrValue[k]|=0x80;
					}
					Time=0;		//����ʱ��Ҫ���¸�ֵ							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}			
}