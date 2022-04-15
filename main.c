/*
操    作: 1、要使P0口的LED工作，需要将跳线插座J22的跳线帽接至ON端
		  2、要使蜂鸣器工作，需要将跳线插座J7的跳线帽接至SPE端
		  3、要使DS18B20数字温度传感器工作，需要将跳线插座J7的跳线帽接至TDQ端
内部时钟：11.0592MHz       
*/
 
/*头文件及变量声明*/
#include "stc15f2k60s2.h"
#include <intrins.h> 
#include "Delay.h" 
#include "LCD1602.h"
//#include "I2C.h" 
#include "Mlx90614.h" 

//*************主函数******************************************* 
void main() 
{ 
	LCD_Init();
	Mlx90614_I2C_Init();
	//函数部分
	
	while(1) 
	{ 
		Mlx90614_DisplayT();
		Delay1s();	
	} 
} 
