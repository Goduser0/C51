#ifndef _lcd1602_H
#define _lcd1602_H
#include "reg52.h"

//�ܽŶ���
sbit LCD_RS=P3^4;//��������ѡ��
sbit LCD_EA=P3^5; //ʹ���ź�
#define LCD_DATAPORT P0	//�궨��LCD1602���ݶ˿�


//��������
void lcd_init(void);
void lcd_clear(void);
void lcd_show_string(unsigned char x,unsigned char y,unsigned char *str);

#endif