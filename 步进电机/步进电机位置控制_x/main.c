#include "reg52.h"
#include "lcd1602.h"
#include "stdlib.h"

typedef unsigned int uint;
typedef unsigned char uchar;

//����L298���Ʋ�������ܽ�
sbit IN1_A=P2^0;
sbit IN1_B=P2^1;
sbit IN1_C=P2^2;
sbit IN1_D=P2^3;

//��������������ƽ�
sbit KEY_0=P1^0;
sbit KEY_1=P1^1;
sbit KEY_2=P1^2;
sbit KEY_3=P1^3;
sbit KEY_4=P1^4;
sbit KEY_5=P1^5;

//����ָʾ�ƿ��ƹܽ�
sbit LED_FWD=P3^0;
sbit LED_REV=P3^1;
sbit MOTOR1_EA=P3^2;
 
//�����������������ֵ
#define KEY_0_PRESS 0 //��ת
#define KEY_1_PRESS	1 //��ת
#define KEY_2_PRESS	2 //1plus
#define KEY_3_PRESS	3 //10plus
#define KEY_4_PRESS	4 //100plus
#define KEY_5_PRESS	5 //��ͣ
#define KEY_UNPRESS	-1 

//��ʱ
void delay_10us(unsigned int ten_us)
{
	while(ten_us--);
}

//��ʱ��0�ж��趨����������Ƶ�ʿ���
void T0_set(bit T0)//T0==1��ʼ������T0==0ֹͣ����
{
	TMOD |= 0X01;
	TH0 = 0XF2;
	TL0 = 0X54;
	TR0 = T0;
	ET0 = 1;
	EA = 1;
}

//��ʱ��1�ж��趨��ˢ��LCD��ʾ����
void T1_set(bit T1)//T1==1��ʼ������T1==0ֹͣ����
{
	TMOD |= 0X10;
	TH1 = 0X3C;
	TL1 = 0XB0;
	TR1 = T1;
	ET1 = 1;
	EA = 1;
}

//�����������
uchar key_scan(uchar mode)
{
	static uchar key=1;
	if(mode)key=1;//����ɨ�谴��
	if(key==1&&(KEY_0==0||KEY_1==0||KEY_2==0||KEY_3==0||KEY_4==0||KEY_5==0))//���ⰴ������
	{
		delay_10us(5000);//����
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
		else if(KEY_5==0)
			return KEY_5_PRESS;		
	}
	else if(KEY_0==1&&KEY_1==1&&KEY_2==1&&KEY_3==1&&KEY_4==1&&KEY_5==1) //�ް�������
	{
		key=1;			
	}
	return KEY_UNPRESS;		
}

//����������巢��
void step_motor_send_pulse(uchar step,uchar dir)
{
	uchar temp=step;	
	if(dir==0)	//��ת���ĵ���
		temp=3-step;
		switch(temp)//4�Ŀ��ƣ�A->B->C->D
		{
			case 0: IN1_A=1;IN1_B=0;IN1_C=0;IN1_D=0;break;
			case 1: IN1_A=0;IN1_B=1;IN1_C=0;IN1_D=0;break;
			case 2: IN1_A=0;IN1_B=0;IN1_C=1;IN1_D=0;break;
			case 3: IN1_A=0;IN1_B=0;IN1_C=0;IN1_D=1;break;
			default: IN1_A=0;IN1_B=0;IN1_C=0;IN1_D=0;break;
		}			
}

uchar step0=0;//��ʼ��
uchar dir;//��ʼ��ת����
float milex=100.00;
char milex_str[6];

uint key_press_value,num_plus=0,set_num_plus=10;

void int2str(float a)
{
	uint baiwei=((int)a)/100;
	uint shiwei=(((int)a)%100)/10;
	uint gewei=((int)a)%10;
	int b=a*100;
	uint shifengwei=(b%100)/10;
	uint baifengwei=b%10;
	char tra[10]={'0','1','2','3','4','5','6','7','8','9'};
	milex_str[0]=tra[baiwei];milex_str[1]=tra[shiwei];milex_str[2]=tra[gewei];milex_str[3]='.';milex_str[4]=tra[shifengwei];milex_str[5]=tra[baifengwei];
}

void main()
{		
	MOTOR1_EA=0;
	lcd_init();//LCD��ʼ��
	T1_set(1);
	while(1)
	{
		key_press_value=key_scan(1);
		if (key_press_value!=-1&&milex>=0&&milex<=200)
		{
			if (key_press_value==0)
			{MOTOR1_EA=1;dir=1;LED_FWD=1;LED_REV=0;}
			else if (key_press_value==1)
			{MOTOR1_EA=1;dir=0;LED_FWD=0;LED_REV=1;}
			else if (key_press_value==2)
			{
				set_num_plus=1;
				T0_set(1);
			}
			else if (key_press_value==3)
			{	
				set_num_plus=10;
				T0_set(1);
			}
			else if (key_press_value==4)
			{
				set_num_plus=100;
				T0_set(1);
			}
			else if (key_press_value==5)
			{
				MOTOR1_EA=0;
			}				
		}								
	}		
}


void bujujiao(void) interrupt 1
{
	TH0 = 0XF2;
	TL0 = 0X54;
	(step0)%=4;step_motor_send_pulse((step0)++,dir);
	if(dir==0){if((milex+1.05)<=200.0){milex+=1.05;}}
	if(dir==1){if((milex-1.05)>=0.0){milex-=1.05;}}
	num_plus++;
	if(num_plus==set_num_plus){T0_set(0);num_plus=0;}

}

//LCD��ʾ
void LCD_SHOW(void) interrupt 3
{
	TH1 = 0X3C;
	TL1 = 0XB0;
	if(dir==1){lcd_show_string(0,0,"X+");}else if(dir==0){lcd_show_string(0,0,"X-");}
	int2str(milex);
	lcd_show_string(0,1,milex_str);
}	   