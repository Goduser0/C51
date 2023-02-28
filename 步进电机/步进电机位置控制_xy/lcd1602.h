#ifndef _lcd1602_H
#define _lcd1602_H
#include "reg52.h"

//管脚定义
sbit LCD_RS=P3^4;//数据命令选择
sbit LCD_EA=P3^5; //使能信号
#define LCD_DATAPORT P0	//宏定义LCD1602数据端口


//函数声明
void lcd_init(void);
void lcd_clear(void);
void lcd_show_string(unsigned char x,unsigned char y,unsigned char *str);

#endif