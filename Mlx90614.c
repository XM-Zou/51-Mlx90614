//����ǽӴ�����ģ�飨MLX90614ESF,�����2cm���ң�
//�ͺţ�GY-906-BAA 
//Ʒ�ƣ�MELEXIS
//��װ��TO-39
//оƬ��MLX90614
//�����Դ��3.3V-5V
#include "stc15f2k60s2.h"
#include <intrins.h>
#include "Mlx90614.h" 
#include "LCD1602.h"

/**
  * @brief  STC 1T��Ƭ��1us��ʱ����,�ⲿʱ��11.0592MHz
  * @param  us:��ʱ��΢����
  * @retval ��
  */
void Mlx90614_I2CDelay_us(unsigned int us)
{
  while( us--)
  {
    _nop_();
  }             
}

/***********************************************
�������ƣ�Mlx90614_I2C_Reset
��    �ܣ�I2C���߸�λ����
��ڲ�������
�� �� ֵ����	
��    ע����9�����������λ
************************************************/
void Mlx90614_I2C_Reset(void)
{
	unsigned char i;
	Mlx90614_I2C_SDA=1;           //����������
	for(i=0;i<9;i++)
	{
		Mlx90614_I2C_SCL=0;         //����ʱ����
		Mlx90614_I2CDelay_us(10);   //��ʱ
		Mlx90614_I2C_SCL=1;         //���������أ�����ʱ����
		Mlx90614_I2CDelay_us(10);   //��ʱ
	}
}

/**
  * @brief  Mlx90614_I2C��ʼ������
  * @param  ��
  * @retval ��
  */
void Mlx90614_I2C_Init(void)
{
	//��P23 P24����Ϊ׼˫���
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
  * @brief  Mlx90614_I2C��ʼ
  * @param  ��
  * @retval ��
  */
void Mlx90614_I2C_Start(void)
{
	Mlx90614_I2C_SDA=1;
	Mlx90614_I2C_SCL=1;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	Mlx90614_I2C_SDA=0;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	Mlx90614_I2C_SCL=0;
	Mlx90614_I2CDelay_us(10);           //��ʱ
}

/**
  * @brief  Mlx90614_I2Cֹͣ
  * @param  ��
  * @retval ��
  */
void Mlx90614_I2C_Stop(void)
{
	Mlx90614_I2C_SDA=0;
	Mlx90614_I2C_SCL=1;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	Mlx90614_I2C_SDA=1;
	Mlx90614_I2CDelay_us(10);           //��ʱ
}

/**
  * @brief  Mlx90614_I2C����һ���ֽ�
  * @param  Byte Ҫ���͵��ֽ�
  * @retval ��
  */
void Mlx90614_I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		Mlx90614_I2C_SDA=Byte&(0x80>>i);
		Mlx90614_I2CDelay_us(10);           //��ʱ
		Mlx90614_I2C_SCL=1;
		Mlx90614_I2CDelay_us(10);           //��ʱ
		Mlx90614_I2C_SCL=0;
		Mlx90614_I2CDelay_us(10);           //��ʱ
	}
}

/**
  * @brief  Mlx90614_I2C����һ���ֽ�
  * @param  ��
  * @retval ���յ���һ���ֽ�����
  */
unsigned char Mlx90614_I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	Mlx90614_I2C_SDA=1;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	for(i=0;i<8;i++)
	{
		Mlx90614_I2C_SCL=1;
		Mlx90614_I2CDelay_us(10);           //��ʱ
		if(Mlx90614_I2C_SDA){Byte|=(0x80>>i);}
		Mlx90614_I2CDelay_us(10);           //��ʱ
		Mlx90614_I2C_SCL=0;
		Mlx90614_I2CDelay_us(10);           //��ʱ
	}
	return Byte;
}

/**
  * @brief  Mlx90614_I2C����Ӧ��
  * @param  AckBit Ӧ��λ��0ΪӦ��1Ϊ��Ӧ��
  * @retval ��
  */
void Mlx90614_I2C_SendAck(unsigned char AckBit)
{
	Mlx90614_I2C_SDA=AckBit;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	Mlx90614_I2C_SCL=1;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	Mlx90614_I2C_SCL=0;
	Mlx90614_I2CDelay_us(10);           //��ʱ
}

/**
  * @brief  Mlx90614_I2C����Ӧ��λ
  * @param  ��
  * @retval ���յ���Ӧ��λ��0ΪӦ��1Ϊ��Ӧ��
  */
unsigned char Mlx90614_I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	Mlx90614_I2C_SCL=0;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	
	Mlx90614_I2C_SDA=1;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	Mlx90614_I2C_SCL=1;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	AckBit=Mlx90614_I2C_SDA;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	Mlx90614_I2C_SCL=0;
	Mlx90614_I2CDelay_us(10);           //��ʱ
	return AckBit;
}

/**
  * @brief  Mlx90614��ʼ��ȡ�¶�
  * @param  ��
  * @retval ��
  */
unsigned int Mlx90614_ReadT(void)
{
	unsigned char DataH,DataL;
	Mlx90614_I2C_Start();
	Mlx90614_I2C_SendByte(0x00); //Send SlaveAddress ���ʹӻ���ַ
	Mlx90614_I2C_ReceiveAck();
	Mlx90614_I2C_SendByte(0x07); //Send Command ���Ͳ�������
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
  * @brief  Mlx90614��ȡ�¶�
  * @param  ��
  * @retval �¶���ֵ
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
		LCD_ShowChar(1,1,'+');//��ʾ����
	} 
	else
	{
		T=27315-T; 
		a=T/100; 
		b=T-a*100; 
		LCD_ShowString(1,1,'-');//��ʾ����
	}
	LCD_ShowNum(1,2,a,3);	//LCD��ʾ�¶���������
	LCD_ShowChar(1,5,'.');
	LCD_ShowNum(1,6,(unsigned long)b%100,2);	//LCD��ʾ�¶�С������
	LCD_ShowSignal_T(1,8);//��ʾ���϶ȷ��š�
}
