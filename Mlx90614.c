//红外非接触测温模块（MLX90614ESF,测距是2cm左右）
//型号：GY-906-BAA 
//品牌：MELEXIS
//封装：TO-39
//芯片：MLX90614
//供电电源：3.3V-5V
#include "stc15f2k60s2.h"
#include <intrins.h>
#include "Mlx90614.h" 
#include "LCD1602.h"

/**
  * @brief  STC 1T单片机1us延时程序,外部时钟11.0592MHz
  * @param  us:延时的微秒数
  * @retval 无
  */
void Mlx90614_I2CDelay_us(unsigned int us)
{
  while( us--)
  {
    _nop_();
  }             
}

/***********************************************
函数名称：Mlx90614_I2C_Reset
功    能：I2C总线复位操作
入口参数：无
返 回 值：无	
备    注：发9个脉冲产生复位
************************************************/
void Mlx90614_I2C_Reset(void)
{
	unsigned char i;
	Mlx90614_I2C_SDA=1;           //拉高数据线
	for(i=0;i<9;i++)
	{
		Mlx90614_I2C_SCL=0;         //拉低时钟线
		Mlx90614_I2CDelay_us(10);   //延时
		Mlx90614_I2C_SCL=1;         //产生上升沿，拉高时钟线
		Mlx90614_I2CDelay_us(10);   //延时
	}
}

/**
  * @brief  Mlx90614_I2C初始化函数
  * @param  无
  * @retval 无
  */
void Mlx90614_I2C_Init(void)
{
	//将P23 P24设置为准双向口
	P2M1 &=~( (1<<3) | (1<<4) );  
	P2M0 &=~( (1<<3) | (1<<4) );
	
	Mlx90614_I2C_Reset();
	
	Mlx90614_I2C_SCL=1;Mlx90614_I2C_SDA=1;_nop_(); 
	_nop_();_nop_();_nop_(); 
	Mlx90614_I2C_SCL=0; 
	Mlx90614_I2CDelay_us(1000); 
	Mlx90614_I2C_SCL=1; 
}

/**
  * @brief  Mlx90614_I2C开始
  * @param  无
  * @retval 无
  */
void Mlx90614_I2C_Start(void)
{
	Mlx90614_I2C_SDA=1;
	Mlx90614_I2C_SCL=1;
	Mlx90614_I2CDelay_us(10);           //延时
	Mlx90614_I2C_SDA=0;
	Mlx90614_I2CDelay_us(10);           //延时
	Mlx90614_I2C_SCL=0;
	Mlx90614_I2CDelay_us(10);           //延时
}

/**
  * @brief  Mlx90614_I2C停止
  * @param  无
  * @retval 无
  */
void Mlx90614_I2C_Stop(void)
{
	Mlx90614_I2C_SDA=0;
	Mlx90614_I2C_SCL=1;
	Mlx90614_I2CDelay_us(10);           //延时
	Mlx90614_I2C_SDA=1;
	Mlx90614_I2CDelay_us(10);           //延时
}

/**
  * @brief  Mlx90614_I2C发送一个字节
  * @param  Byte 要发送的字节
  * @retval 无
  */
void Mlx90614_I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		Mlx90614_I2C_SDA=Byte&(0x80>>i);
		Mlx90614_I2CDelay_us(10);           //延时
		Mlx90614_I2C_SCL=1;
		Mlx90614_I2CDelay_us(10);           //延时
		Mlx90614_I2C_SCL=0;
		Mlx90614_I2CDelay_us(10);           //延时
	}
}

/**
  * @brief  Mlx90614_I2C接收一个字节
  * @param  无
  * @retval 接收到的一个字节数据
  */
unsigned char Mlx90614_I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	Mlx90614_I2C_SDA=1;
	Mlx90614_I2CDelay_us(10);           //延时
	for(i=0;i<8;i++)
	{
		Mlx90614_I2C_SCL=1;
		Mlx90614_I2CDelay_us(10);           //延时
		if(Mlx90614_I2C_SDA){Byte|=(0x80>>i);}
		Mlx90614_I2CDelay_us(10);           //延时
		Mlx90614_I2C_SCL=0;
		Mlx90614_I2CDelay_us(10);           //延时
	}
	return Byte;
}

/**
  * @brief  Mlx90614_I2C发送应答
  * @param  AckBit 应答位，0为应答，1为非应答
  * @retval 无
  */
void Mlx90614_I2C_SendAck(unsigned char AckBit)
{
	Mlx90614_I2C_SDA=AckBit;
	Mlx90614_I2CDelay_us(10);           //延时
	Mlx90614_I2C_SCL=1;
	Mlx90614_I2CDelay_us(10);           //延时
	Mlx90614_I2C_SCL=0;
	Mlx90614_I2CDelay_us(10);           //延时
}

/**
  * @brief  Mlx90614_I2C接收应答位
  * @param  无
  * @retval 接收到的应答位，0为应答，1为非应答
  */
unsigned char Mlx90614_I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	Mlx90614_I2C_SCL=0;
	Mlx90614_I2CDelay_us(10);           //延时
	
	Mlx90614_I2C_SDA=1;
	Mlx90614_I2CDelay_us(10);           //延时
	Mlx90614_I2C_SCL=1;
	Mlx90614_I2CDelay_us(10);           //延时
	AckBit=Mlx90614_I2C_SDA;
	Mlx90614_I2CDelay_us(10);           //延时
	Mlx90614_I2C_SCL=0;
	Mlx90614_I2CDelay_us(10);           //延时
	return AckBit;
}

/**
  * @brief  Mlx90614开始读取温度
  * @param  无
  * @retval 无
  */
unsigned int Mlx90614_ReadT(void)
{
	unsigned char DataH,DataL;
	Mlx90614_I2C_Start();
	Mlx90614_I2C_SendByte(0x00); //Send SlaveAddress 发送从机地址
	Mlx90614_I2C_ReceiveAck();
	Mlx90614_I2C_SendByte(0x07); //Send Command 发送操作命令
	Mlx90614_I2C_ReceiveAck();
	//------------ 
	Mlx90614_I2C_Start();
	Mlx90614_I2C_SendByte(0x01); 
	Mlx90614_I2C_ReceiveAck();
	DataL=Mlx90614_I2C_ReceiveByte(); 
	Mlx90614_I2C_SendAck(0);//bit_out=0; 
	DataH=Mlx90614_I2C_ReceiveByte();
	Mlx90614_I2C_SendAck(1);//bit_out=1; 
	//Pecreg=Mlx90614_I2C_ReceiveByte();
	Mlx90614_I2C_Stop();//stop_bit(); 
	return(DataH*256+DataL); 
}

/**
  * @brief  Mlx90614读取温度
  * @param  无
  * @retval 温度数值
  */
void Mlx90614_DisplayT(void)
{
	unsigned int Temp;
	unsigned int T,a,b;
	Temp=Mlx90614_ReadT();
	 
	T=Temp*2; 

	if(T>=27315) 
	{ 
		T=T-27315; 
		a=T/100; 
		b=T%100; 
		LCD_ShowChar(1,1,'+');//显示正号
	} 
	else
	{
		T=27315-T; 
		a=T/100; 
		b=T-a*100; 
		LCD_ShowString(1,1,'-');//显示负号
	}
	LCD_ShowNum(1,2,a,3);	//LCD显示温度整数部分
	LCD_ShowChar(1,5,'.');
	LCD_ShowNum(1,6,(unsigned long)b%100,2);	//LCD显示温度小数部分
	LCD_ShowSignal_T(1,8);//显示摄氏度符号℃
}
