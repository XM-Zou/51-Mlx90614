#ifndef __MLX90614_H__ 
#define __MLX90614_H__
//Mlx90614 �˿ڶ���
sbit Mlx90614_I2C_SCL=P2^3;//ʱ����
sbit Mlx90614_I2C_SDA=P2^4;//������

void Mlx90614_I2C_Init(void);
unsigned int Mlx90614_ReadT(void);
void Mlx90614_DisplayT(void);

#endif