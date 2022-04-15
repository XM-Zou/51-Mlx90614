#ifndef __I2C_H__ 
#define __I2C_H__

/*ͷ�ļ�����������*/
#include "stc15f2k60s2.h"
//I2C�ӿڶ���
sbit I2C_SCL = P5^5;           //AT24C02��ʱ��
sbit I2C_SDA = P5^4;           //AT24C02������

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char Byte);
unsigned char I2C_ReceiveByte(void);
void I2C_SendAck(unsigned char AckBit);
unsigned char I2C_ReceiveAck(void);

#endif