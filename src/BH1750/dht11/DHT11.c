#include"DHT11.h"
/*******************************************************************************
* Function Name  : 
* Description    : 
*******************************************************************************/

char Humi[6]={0};
char Temp[6]={0};
u8 cnt;

int DHT11_Read_Byte(void)
{
	int Data = 0;
	for (cnt = 0; cnt < 8; cnt++)
	{
		while((PA_IDR&0X08)==0);	
		Delay_us(30);
		if ((PA_IDR&0X08)== 1)
		{ 
		  	Data++;
		}
		while((PA_IDR&0X08)==1);		
		Data <<= 1;
	}
	return Data;
}

void DHT11(void) 
{
	int Data_Buff[5];
	PA_ODR &=0XF7;
	Delay_ms(20);
	PA_ODR|=0X08;
	Delay_us(20);
	PA_DDR &=0XF7;
	Delay_us(20);
	if ((PA_IDR&0X08)==0)
	{
		while((PA_IDR&0X08)==0);
		// if ((PA_IDR&0X08)==1) 
		// {
			// for(cnt=0;cnt<180;cnt++) 
			// {
			  // PB_ODR^=0X20;
			  // Delay_ms(80);
			// }
		// }
		while((PA_IDR&0X08)==1);
		for (cnt = 0; cnt< 5; cnt++)
		{
			Data_Buff[cnt] = DHT11_Read_Byte();
		}
		while((PA_IDR&0X08)==0);
		PA_DDR|=0X08; 
		PA_ODR|=0X08;
//		EEPROM_B(STORE_ADDR,Data_Buff[0]);
//		EEPROM_B(STORE_ADDR+1,Data_Buff[1]);
//		EEPROM_B(STORE_ADDR+2,Data_Buff[2]);
//		EEPROM_B(STORE_ADDR+3,Data_Buff[3]);
//		EEPROM_B(STORE_ADDR+4,Data_Buff[4]);
//		EEPROM_B(STORE_ADDR+4,0xff);
		//EEPROM_B(HEAD_ADDR,0X55);
		if ((Data_Buff[0] + Data_Buff[1] + Data_Buff[2] + Data_Buff[3])==Data_Buff[4])
		{			
		  	for(cnt=0;cnt<180;cnt++) 
			{
			  PB_ODR^=0X20;
			  Delay_ms(80);
			}
//			EEPROM_B(STORE_ADDR,Data_Buff[0]);
//			EEPROM_B(STORE_ADDR+1,Data_Buff[1]);
//			EEPROM_B(STORE_ADDR+2,Data_Buff[2]);
//			EEPROM_B(STORE_ADDR+3,Data_Buff[3]);
//			EEPROM_B(STORE_ADDR+4,0x77);
			Humi[0] = Data_Buff[0] / 10 + 48;
			Humi[1] = Data_Buff[0] % 10 + 48;
			Humi[2] = '.';
			Humi[3] = Data_Buff[1] / 10 + 48;
			Humi[4] = Data_Buff[1] % 10 + 48;

			Temp[0] = Data_Buff[2] / 10 + 48;
			Temp[1] = Data_Buff[2] % 10 + 48;
			Temp[2] = '.';
			Temp[3] = Data_Buff[3] / 10 + 48;
			Temp[4] = Data_Buff[3] % 10 + 48;
		}
	}

}

