

#include "BH1750.h"
#include "i2c.h"

float result_lx=0;
u8 BUF[2]={0};
u16 result=0;

//初始化
void Init_BH1750(void)
{
	i2c_Port_Init();
	Delay_ms(15);
}

void Cmd_Write_BH1750(u8 cmd)
{
    I2C_Start();                  //起始信号
    I2C_Send_Byte(BH1750_Addr+0);   //发送设备地址+写信号
	while(I2C_Wait_Ack());
    I2C_Send_Byte(cmd);    //内部寄存器地址
	while(I2C_Wait_Ack());
    //BH1750_SendByte(REG_data);       //内部寄存器数据，
    I2C_Stop();                   //发送停止信号
    Delay_ms(5);
}
void Start_BH1750(void)
{
	Cmd_Write_BH1750(BH1750_ON);	 //power on
	Cmd_Write_BH1750(BH1750_RSET);	//clear
	Cmd_Write_BH1750(BH1750_ONE);  //一次H分辨率模式，至少120ms，之后自动断电模式  
}
void Read_BH1750(void)
{   	
    I2C_Start();                          //起始信号
    I2C_Send_Byte(BH1750_Addr+1);         //发送设备地址+读信号
    while(I2C_Wait_Ack());
    BUF[0]=I2C_Read_Byte(1);     //发送ACK
    BUF[1]=I2C_Read_Byte(0);     //发送NACK
    I2C_Stop();                  //停止信号
    Delay_ms(5);
    UASRT_SEND(BUF[0]);
    UASRT_SEND(BUF[1]);
}
void Convert_BH1750(void)
{
  	i2c_Port_Init();
	Start_BH1750();
	Delay_ms(150);
        Read_BH1750();
	//EEPROM_B(LX_ADDR,BUF[0]);
	//EEPROM_B(LX_ADDR+1,BUF[0]);
	result=BUF[0];
	result=(result<<8)+BUF[1];  //合成数据，即光照数据	
	//result_lx=(float)result/1.2;

}


