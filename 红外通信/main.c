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
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位	
		}
		P0=DisplayData[i];//发送数据
		delay_10us(100); //间隔一段时间扫描	
		P0=0x00;//消隐
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
	if(IRIN==0)		//确认是否真的接收到正确的信号
	{	 
		
		err=1000;				//1000*10us=10ms,超过说明接收到错误的信号
		/*当两个条件都为真是循环，如果有一个条件为假的时候跳出循环，免得程序出错的时
		侯，程序死在这里*/	
		while((IRIN==0)&&(err>0))	//等待前面9ms的低电平过去  		
		{			
			delay_10us(1);
			err--;
		} 
		if(IRIN==1)			//如果正确等到9ms低电平
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //等待4.5ms的起始高电平过去
			{
				delay_10us(1);
				err--;
			}
			for(k=0;k<4;k++)		//共有4组数据
			{				
				for(j=0;j<8;j++)	//接收一组数据
				{

					err=60;		
					while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
					{
						delay_10us(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //计算高电平的时间长度。
					{
						delay_10us(10);	 //0.1ms
						Time++;
						err--;
						if(Time>30)
						{
							return;
						}
					}
					IrValue[k]>>=1;	 //k表示第几组数据
					if(Time>=8)			//如果高电平出现大于565us，那么是1
					{
						IrValue[k]|=0x80;
					}
					Time=0;		//用完时间要重新赋值							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}			
}