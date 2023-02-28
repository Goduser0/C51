#include "lcd1602.h"

typedef unsigned int u16;
typedef unsigned char u8;

//1ms延时
void delay_ms(u16 ms)
{
	u16 i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

//LCD 写命令
void lcd_write_cmd(u8 cmd)
{
	LCD_RS=0;//选择命令
	LCD_EA=0;
	LCD_DATAPORT=cmd;//准备命令
	delay_ms(1);
	LCD_EA=1;//上升沿写入
	delay_ms(1);
	LCD_EA=0;//下降沿完成写入	
}

//LCD 写数据
void lcd_write_data(u8 dat) 
{
	LCD_RS=1;//选择数据
	LCD_EA=0;
	LCD_DATAPORT=dat;//准备数据
	delay_ms(1);
	LCD_EA=1;//上升沿写入
	delay_ms(1);
	LCD_EA=0;//下降沿完成写入		
}

//LCD 初始化
void lcd_init(void)
{
	lcd_write_cmd(0x38);//数据总线8位，显示2行，5*7点阵/字符
	lcd_write_cmd(0x0c);//显示功能开，无光标，光标闪烁
	lcd_write_cmd(0x06);//写入新数据后光标右移，显示屏不移动
	lcd_write_cmd(0x01);//清屏	
}

//LCD 清屏
void lcd_clear(void)
{
	lcd_write_cmd(0x01);	
}

//LCD显示字符
//x,y：显示坐标，x=0~15，y=0~1;
//str：显示字符串

void lcd_show_string(u8 x,u8 y,u8 *str)
{
	u8 i=0;

	if(y>1||x>15)return;//行列参数不对则强制退出

	if(y<1)	//第1行显示
	{	
		while(*str!='\0')
		{
			if(i<16-x)//如果字符长度超过第一行显示范围，则在第二行继续显示
			{
				lcd_write_cmd(0x80+i+x);//第一行显示地址设置	
			}
			else
			{
				lcd_write_cmd(0x40+0x80+i+x-16);//第二行显示地址设置	
			}
			lcd_write_data(*str);//显示内容
			str++;
			i++;	
		}	
	}
	else	//第2行显示
	{
		while(*str!='\0')
		{
			if(i<16-x) //如果字符长度超过第二行显示范围，则在第一行继续显示
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