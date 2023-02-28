#include "reg52.h"

typedef unsigned int uint;
typedef unsigned char uchar;

//����ULN2003���Ʋ�������ܽ�
sbit IN1_A=P2^4;
sbit IN2_B=P2^5;
sbit IN3_C=P2^6;
sbit IN4_D=P2^7;

//��������������ƽ�
sbit KEY_0=P1^0;
sbit KEY_1=P1^1;
sbit KEY_2=P1^2;
sbit KEY_3=P1^3;
sbit KEY_4=P1^4;

//����ָʾ�ƿ��ƹܽ�
sbit LED_FWD=P3^0;
sbit LED_REV=P3^1;

//�����������������ֵ
#define KEY_0_PRESS 0 //��ת
#define KEY_1_PRESS	1 //��ת
#define KEY_2_PRESS	2 //����
#define KEY_3_PRESS	3 //����
#define KEY_4_PRESS	4 //��ͣ
#define KEY_UNPRESS	-1 

//���岽������ٶȣ�ֵԽС���ٶ�Խ��
#define STEPMOTOR_MAXSPEED 1  
#define STEPMOTOR_MINSPEED 5
//���ʹ��
bit motor_EA = 1;  	

void delay_10us(uint ten_us)
{
	while(ten_us--);	
}

void delay_ms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

void step_motor_send_pulse(uchar step,uchar dir)
{
	uchar temp=step;
	
	if(dir==0)	//��ת���ĵ���
		temp=7-step;
	switch(temp)//8�Ŀ��ƣ�A->AB->B->BC->C->CD->D->DA
	{
		case 0: IN1_A=1;IN2_B=0;IN3_C=0;IN4_D=0;break;
		case 1: IN1_A=1;IN2_B=1;IN3_C=0;IN4_D=0;break;
		case 2: IN1_A=0;IN2_B=1;IN3_C=0;IN4_D=0;break;
		case 3: IN1_A=0;IN2_B=1;IN3_C=1;IN4_D=0;break;
		case 4: IN1_A=0;IN2_B=0;IN3_C=1;IN4_D=0;break;
		case 5: IN1_A=0;IN2_B=0;IN3_C=1;IN4_D=1;break;
		case 6: IN1_A=0;IN2_B=0;IN3_C=0;IN4_D=1;break;
		case 7: IN1_A=1;IN2_B=0;IN3_C=0;IN4_D=1;break;
		default: IN1_A=0;IN2_B=0;IN3_C=0;IN4_D=0;break;//ֹͣ����	
	}			
}

uchar key_scan(uchar mode)
{
	static uchar key=1;

	if(mode)key=1;//����ɨ�谴��
	if(key==1&&(KEY_0==0||KEY_1==0||KEY_2==0||KEY_3==0||KEY_4==0))//���ⰴ������
	{
		delay_10us(1000);//����
		key=0;
		if(KEY_0==0)
			return KEY_0_PRESS;
		else if(KEY_1==0)
			return KEY_1_PRESS;
		else if(KEY_2==0)
			return KEY_2_PRESS;
		else if(KEY_3==0)
			return KEY_3_PRESS;
		else if(KEY_4==0)
			return KEY_4_PRESS;	
	}
	else if(KEY_0==1&&KEY_1==1&&KEY_2==1&&KEY_3==1&&KEY_4==1) //�ް�������
	{
		key=1;			
	}
	return KEY_UNPRESS;		
}

void main()
{	
	uchar key=0;
	uchar dir=0;//Ĭ����ʱ�뷽��
	uchar speed=STEPMOTOR_MAXSPEED;//Ĭ������ٶ���ת
	uchar step=0;
	LED_FWD=0;
	LED_REV=1;
	step_motor_send_pulse(step,dir);

	while(1)
	{			
		key=key_scan(0);
		if (key!=-1)
		{
			if(key==KEY_0_PRESS)//��ת
			{
				dir=0;
				LED_FWD=0;
				LED_REV=1;    
			}
			else if(key==KEY_1_PRESS)//��ת
			{
				dir=1;
				LED_FWD=1;
				LED_REV=0;
			}
			else if(key==KEY_2_PRESS)//����
			{
				if(speed>STEPMOTOR_MAXSPEED)
				{
				speed-=1;
				}			
			}
			else if(key==KEY_3_PRESS)//����
			{
				if(speed<STEPMOTOR_MINSPEED)
				{
				speed+=1;
				}			
			}
			else if(key==KEY_4_PRESS)//��ͣ
			{
				motor_EA=!motor_EA;	
			}
		}
		if (motor_EA)
		{
			step_motor_send_pulse(step++,dir);
			if(step==8)step=0;		
			delay_ms(speed);
		}
		else
		{
			step_motor_send_pulse(-1,dir);	
		}						
	}		
}