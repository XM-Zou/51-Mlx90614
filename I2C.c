/*ͷ�ļ�����������*/
#include "I2C.h"
#include <intrins.h>

/**
  * @brief  STC 1T��Ƭ��1us��ʱ����,�ⲿʱ��11.0592MHz
  * @param  us:��ʱ��΢����
  * @retval ��
  */
void I2CDelay_us(unsigned int us)
{
  while( us--)
  {
    _nop_();
  }             
}

/**
  * @brief  I2C��ʼ������
  * @param  ��
  * @retval ��
  */
void I2C_Init(void)
{
	//��P54 P55����Ϊ׼˫���
	P5M1 &=~( (1<<4) | (1<<5) );  
	P5M0 &=~( (1<<4) | (1<<5) );
}

/**
  * @brief  I2C��ʼ
  * @param  ��
  * @retval ��
  */
void I2C_Start(void)
{
	I2C_SDA=1;
	I2C_SCL=1;
	I2CDelay_us(10);           //��ʱ
	I2C_SDA=0;
	I2CDelay_us(10);           //��ʱ
	I2C_SCL=0;
	I2CDelay_us(10);           //��ʱ
}

/**
  * @brief  I2Cֹͣ
  * @param  ��
  * @retval ��
  */
void I2C_Stop(void)
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2CDelay_us(10);           //��ʱ
	I2C_SDA=1;
	I2CDelay_us(10);           //��ʱ
}

/**
  * @brief  I2C����һ���ֽ�
  * @param  Byte Ҫ���͵��ֽ�
  * @retval ��
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);
		I2CDelay_us(10);           //��ʱ
		I2C_SCL=1;
		I2CDelay_us(10);           //��ʱ
		I2C_SCL=0;
		I2CDelay_us(10);           //��ʱ
	}
}

/**
  * @brief  I2C����һ���ֽ�
  * @param  ��
  * @retval ���յ���һ���ֽ�����
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	I2C_SDA=1;
	I2CDelay_us(10);           //��ʱ
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;
		I2CDelay_us(10);           //��ʱ
		if(I2C_SDA){Byte|=(0x80>>i);}
		I2CDelay_us(10);           //��ʱ
		I2C_SCL=0;
		I2CDelay_us(10);           //��ʱ
	}
	return Byte;
}

/**
  * @brief  I2C����Ӧ��
  * @param  AckBit Ӧ��λ��0ΪӦ��1Ϊ��Ӧ��
  * @retval ��
  */
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA=AckBit;
	I2CDelay_us(10);           //��ʱ
	I2C_SCL=1;
	I2CDelay_us(10);           //��ʱ
	I2C_SCL=0;
	I2CDelay_us(10);           //��ʱ
}

/**
  * @brief  I2C����Ӧ��λ
  * @param  ��
  * @retval ���յ���Ӧ��λ��0ΪӦ��1Ϊ��Ӧ��
  */
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA=1;
	I2CDelay_us(10);           //��ʱ
	I2C_SCL=1;
	I2CDelay_us(10);           //��ʱ
	AckBit=I2C_SDA;
	I2CDelay_us(10);           //��ʱ
	I2C_SCL=0;
	I2CDelay_us(10);           //��ʱ
	return AckBit;
}
