#include "reg52.h"
#include "delay.h"
#include "interrupt_set.h"

sbit PWM_eye_L = P2^0;
sbit PWM_eye_R = P2^1;

unsigned char change_eye_l=4,change_eye_r=4,i=39;

void pwm_send(unsigned char angle)
{			
	switch(angle)
	{
		case 0:if(change_eye_l>0){change_eye_l-=1;};break;
		case 1:if(change_eye_l<9){change_eye_l+=1;};break;
		case 2:if(change_eye_r>0){change_eye_r-=1;};break;
		case 3:if(change_eye_r<9){change_eye_r+=1;};break;
	}
	i=79;T0_set(1);		
}

//ÓĞĞ§Âö³å·¶Î§£º0.5ms-2.5ms
void PWM_plus() interrupt 1
{
	TH0 = 0XFF;
	TL0 = 0X06;
	i++;
	i%=80; //i·¶Î§£º0~39   i=0->0.5ms i=1->1.0ms i=2->1.5ms i=3->2.0ms i=4->2.5ms
	if (i<=change_eye_l){PWM_eye_L=1;} 
	else {PWM_eye_L=0;}
	if (i<=change_eye_r){PWM_eye_R=1;}
	else {PWM_eye_R=0;}	
}