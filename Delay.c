/*ͷ�ļ�����������*/
#include <INTRINS.H>

/*��ʱ����*/
void Delay1s()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

 /***********************************************
�������ƣ�Delay_ms
��    �ܣ�STC 1T��Ƭ��1ms��ʱ����
��ڲ�����ms:��ʱ�ĺ�����
�� �� ֵ����	
��    ע��ʾ����ʵ��1.05ms ʱ��11.0592MHz
************************************************/
void Delay_ms(unsigned int ms)
{
  unsigned int i;
  while( (ms--) != 0)
  {
    for(i = 0; i < 600; i++); 
  }             
}

void Delay1ms(unsigned char xms)		//@11.0592MHz
{
	unsigned char i, j;
	while(xms)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
}

void Delay500_us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

void Delay70us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 1;
	j = 189;
	do
	{
		while (--j);
	} while (--i);
}

void Delay50us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 1;
	j = 134;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}

void Delay5us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 11;
	while (--i);
}

