/*头文件及变量声明*/
#include "I2C.h"
#include <intrins.h>

/**
  * @brief  STC 1T单片机1us延时程序,外部时钟11.0592MHz
  * @param  us:延时的微秒数
  * @retval 无
  */
void I2CDelay_us(unsigned int us)
{
  while( us--)
  {
    _nop_();
  }             
}

/**
  * @brief  I2C初始化函数
  * @param  无
  * @retval 无
  */
void I2C_Init(void)
{
	//将P54 P55设置为准双向口
	P5M1 &=~( (1<<4) | (1<<5) );  
	P5M0 &=~( (1<<4) | (1<<5) );
}

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void I2C_Start(void)
{
	I2C_SDA=1;
	I2C_SCL=1;
	I2CDelay_us(10);           //延时
	I2C_SDA=0;
	I2CDelay_us(10);           //延时
	I2C_SCL=0;
	I2CDelay_us(10);           //延时
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void I2C_Stop(void)
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2CDelay_us(10);           //延时
	I2C_SDA=1;
	I2CDelay_us(10);           //延时
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的字节
  * @retval 无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);
		I2CDelay_us(10);           //延时
		I2C_SCL=1;
		I2CDelay_us(10);           //延时
		I2C_SCL=0;
		I2CDelay_us(10);           //延时
	}
}

/**
  * @brief  I2C接收一个字节
  * @param  无
  * @retval 接收到的一个字节数据
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	I2C_SDA=1;
	I2CDelay_us(10);           //延时
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;
		I2CDelay_us(10);           //延时
		if(I2C_SDA){Byte|=(0x80>>i);}
		I2CDelay_us(10);           //延时
		I2C_SCL=0;
		I2CDelay_us(10);           //延时
	}
	return Byte;
}

/**
  * @brief  I2C发送应答
  * @param  AckBit 应答位，0为应答，1为非应答
  * @retval 无
  */
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA=AckBit;
	I2CDelay_us(10);           //延时
	I2C_SCL=1;
	I2CDelay_us(10);           //延时
	I2C_SCL=0;
	I2CDelay_us(10);           //延时
}

/**
  * @brief  I2C接收应答位
  * @param  无
  * @retval 接收到的应答位，0为应答，1为非应答
  */
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA=1;
	I2CDelay_us(10);           //延时
	I2C_SCL=1;
	I2CDelay_us(10);           //延时
	AckBit=I2C_SDA;
	I2CDelay_us(10);           //延时
	I2C_SCL=0;
	I2CDelay_us(10);           //延时
	return AckBit;
}
