
/*******************************************************************************
* Description    :STM8S103F3P3  TSSOP20 
*******************************************************************************/
#ifndef MAP_H__
#define MAP_H__

#include <iostm8l151k4.h>
#include "type.h"

/*******************************************************************************/
//#define  			 HEAD_ADDR  	(uint16_t)0x4000 
//__root __no_init volatile u8 	  MODE[32]  		@ 0x4000;
//__root __no_init volatile u8 	  INFO[16]  		@ 0x4020;
//__root __no_init volatile u8     MATE[32]  		@ 0x4030;
//__root __no_init volatile u8      SET[16]  		@ 0x4050;
//
//#define  			STORE_ADDR  	(uint16_t)0x4060 
//__root __no_init volatile u8     DATA[32]  		@ 0x4060;
//
//#define  			   LX_ADDR  	(uint16_t)0x4080 
//__root __no_init volatile u8 	   LX[128]  		@ 0x4080;
//#define  			   UV_ADDR  	(uint16_t)0x4100 
//__root __no_init volatile u8 	   UV[128]  		@ 0x4100;
//#define  			   IN_ADDR  	(uint16_t)0x4180 
//__root __no_init volatile u8 	   IN[128]  		@ 0x4180;
//#define  			   EX_ADDR  	(uint16_t)0x4200 
//__root __no_init volatile u8 	   EX[128]  		@ 0x4200;
//
//#define  			 END_ADDR  	(uint16_t)0x427F 

/*******************************************************************************/

#define BACK_SUCCESS       0   /*³É¹¦*/
#define BACK_ERROR         1   /*´íÎó*/
#define BACK_TIMEOUT       2   /*³¬Ê±*/

#define   LX_MAX      	    0X75
#define   LX_MIN      	    0X75
#define   UV_MAX      	    0X75
#define   UV_MIN      	    0X75
#define   HU_MAX      	    0X75
#define   HU_MIN      	    0X75
#define   TC_MAX      	    0X75
#define   TC_MIN      	    0X75
/*******************************************************************************
uv-adc2-pc4
humi of soil -adc3/4-up d2-down d3
temp/humi - io  
lx -iic
*******************************************************************************/


#define SPI_PORT      		 GPIOC
#define MISO_Pin      	    GPIO_Pin_7 
#define MOSI_Pin            GPIO_Pin_6 
#define SCLK_Pin            GPIO_Pin_5 
#define CS_Pin        	    GPIO_Pin_3  

#define ADC2_Pin            GPIO_Pin_4 
#define ADC_PORT   	         GPIOD
#define ADC4_Pin            GPIO_Pin_3 
#define ADC3_Pin            GPIO_Pin_2 
/*******************************************************************************/
void Delay_ms(uint16_t i);
void Delay_us(uint16_t i);
u8 EEPROM_B(u16 addr,u8 data);
void UASRT_SEND(u8 data) ;
#endif
