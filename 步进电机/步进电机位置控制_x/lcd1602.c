#include "lcd1602.h"

typedef unsigned int u16;
typedef unsigned char u8;

//1ms��ʱ
void delay_ms(u16 ms)
{
	u16 i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

//LCD д����
void lcd_write_cmd(u8 cmd)
{
	LCD_RS=0;//ѡ������
	LCD_EA=0;
	LCD_DATAPORT=cmd;//׼������
	delay_ms(1);
	LCD_EA=1;//������д��
	delay_ms(1);
	LCD_EA=0;//�½������д��	
}

//LCD д����
void lcd_write_data(u8 dat) 
{
	LCD_RS=1;//ѡ������
	LCD_EA=0;
	LCD_DATAPORT=dat;//׼������
	delay_ms(1);
	LCD_EA=1;//������д��
	delay_ms(1);
	LCD_EA=0;//�½������д��		
}

//LCD ��ʼ��
void lcd_init(void)
{
	lcd_write_cmd(0x38);//��������8λ����ʾ2�У�5*7����/�ַ�
	lcd_write_cmd(0x0c);//��ʾ���ܿ����޹�꣬�����˸
	lcd_write_cmd(0x06);//д�������ݺ������ƣ���ʾ�����ƶ�
	lcd_write_cmd(0x01);//����	
}

//LCD ����
void lcd_clear(void)
{
	lcd_write_cmd(0x01);	
}

//LCD��ʾ�ַ�
//x,y����ʾ���꣬x=0~15��y=0~1;
//str����ʾ�ַ���

void lcd_show_string(u8 x,u8 y,u8 *str)
{
	u8 i=0;

	if(y>1||x>15)return;//���в���������ǿ���˳�

	if(y<1)	//��1����ʾ
	{	
		while(*str!='\0')
		{
			if(i<16-x)//����ַ����ȳ�����һ����ʾ��Χ�����ڵڶ��м�����ʾ
			{
				lcd_write_cmd(0x80+i+x);//��һ����ʾ��ַ����	
			}
			else
			{
				lcd_write_cmd(0x40+0x80+i+x-16);//�ڶ�����ʾ��ַ����	
			}
			lcd_write_data(*str);//��ʾ����
			str++;
			i++;	
		}	
	}
	else	//��2����ʾ
	{
		while(*str!='\0')
		{
			if(i<16-x) //����ַ����ȳ����ڶ�����ʾ��Χ�����ڵ�һ�м�����ʾ
			{
				lcd_write_cmd(0x80+0x40+i+x);	
			}
			else
			{
				lcd_write_cmd(0x80+i+x-16);	
			}
			lcd_write_data(*str);
			str++;
			i++;	
		}	
	}				
}