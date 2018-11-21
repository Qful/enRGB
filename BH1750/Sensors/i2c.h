#ifndef __i2c_H
#define __i2c_H

#include "Yuenjee.h"



void i2c_Port_Init(void);    //��ʼ��IIC��IO��				 
void I2C_Start(void);				//����IIC��ʼ�ź� �ɹ��򷵻�1
void I2C_Stop(void);	  			//����IICֹͣ�ź�
void I2C_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 I2C_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 I2C_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void I2C_Ack(void);					//IIC����ACK�ź�
void I2C_NAck(void);				//IIC������ACK�ź�
	  
#endif

