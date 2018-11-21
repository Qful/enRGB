


/*******************************************************************************
* Description    :STM8S103F3P3  TSSOP20 
*******************************************************************************/
#include "DHT11.h"
#include "bh1750.h"
u8 Get_AD(u8 chan) ;
/*******************************************************************************
* Function Name  : 
* Description    : 
*******************************************************************************/
void HAL_Init(void) 
{
      asm("sim"); 
      CLK_CKDIVR = 0x00;
         
//      PA_DDR=0X06;
//      PA_CR1=0X00;
//      PA_CR2=0X00;
//      PA_ODR=0X06;
//   
//      PB_DDR=0X30;
//      PB_CR1=0X30;
//      PB_CR2=0X30;
//      PB_ODR=0X30;
//      
//      PC_DDR=0X00;
//      PC_CR1|=0XFF;
//      PC_CR2|=0X00;
//      //PC_ODR =0XFF;
//      
//      PD_DDR|=0X00;
//      PD_CR1|=0XFF;
//      PD_CR2|=0X00;
      //PD_ODR =0X0F;  
      CLK_PCKENR1 |= (1<<5);//¿ª´®¿ÚÊ±ÖÓ
      //CLK_PCKENR1 = 0x09;
      //CLK_PCKENR2 = 0x08;
      USART1_BRR2 = 0x03;
      USART1_BRR1 = 0X68; // 16m/9600
      USART1_CR2  = 0X2C;
      asm("rim"); 
}
/*******************************************************************************
* Function Name  : main
* Description    : 
*******************************************************************************/
void main( void )
{  
    u8 buff,cnt;
    HAL_Init(); 
    Delay_ms(1000);
    //PB_ODR|=0X20;
// for(cnt=0;cnt<255;cnt++) EEPROM_B(STORE_ADDR+cnt,0);    
//    DHT11();

//    WWDG_CR = 0x80;
//    WWDG_CR &= 0xBF;
//    if(PD_IDR!=0){
//      for(cnt=0;cnt<24;cnt++) {PB_ODR ^=0X20;Delay_ms(100);}}
    
    while(1) //{PB_ODR ^=0X20;Delay_ms(100);}
    {
	//if((PD_IDR & 0X10) ==0) PB_ODR |=0X20;
	//else if((PD_IDR &0X20) ==0x20) PB_ODR &=0XDF;
////	EEPROM_B(HEAD_ADDR,PA_IDR);
//	for(cnt=2;cnt<5;cnt++) 
//	{
//	      //PB_ODR^=0X20;
//	     // Delay_ms(100);
//	      buff=Get_AD(cnt) ;
//	      //UASRT_SEND(buff);
//	      //EEPROM_B(STORE_ADDR+cnt,PD_IDR);
//	}
//	buff=Get_AD(7) ;
//	//UASRT_SEND(buff);
//	
	Convert_BH1750();
//	UASRT_SEND(LX[0]);
//	UASRT_SEND(LX[1]);
	Delay_ms(1000);
    }
}

/*******************************************************************************
* Function Name  : 
* Description    : 
*******************************************************************************/
//u8 Get_AD(u8 chan) 
//{
//      //u8 buff;
//      ADC_CR1=0X01;
//      ADC_CR2=0X00;
//      ADC_CSR=chan;
//      ADC_CR1|=0X01;
//      while((ADC_CSR & 0X80)==0);
//      ADC_CR1 &=0XFE;
//      //buff=ADC_DRH;
//      return ADC_DRH;
//}

/*******************************************************************************
* Function Name  : 
* Description    : 
*******************************************************************************/
void UASRT_SEND(u8 data) 
{
      while((USART1_SR & 0x80) == 0x00); 
      USART1_DR = data;
}
//
//#pragma vector=USART_R_RXNE_vector
//__interrupt void USART1_RX_RXNE(void)
//{
//      u8 c;
//      c = USART1_DR; 
//      while(!USART1_SR_TXE);
//      c++; 
//      UASRT_SEND(c) ;
//      //UART1_DR = c;
//}
#pragma vector= USART_R_OR_vector
__interrupt void USART1_R_OR_IRQHandler(void)
{
      unsigned char ch;
      ch=USART1_DR;
      ch++; 
      UASRT_SEND(ch);
}
/*******************************************************************************
* Function Name  : 
* Description    : 
*******************************************************************************/
void IR(u8 Plant) 
{

}
/*******************************************************************************
* Function Name  : Time
*******************************************************************************/
void Delay_ms(uint16_t i) 
{
	uint16_t x=1440;  
	while(i--) 
	{
	    while(x--);
	    x=1440; 
	}
}
void Delay_us(uint16_t i) 
{ 
	while(i--);
}
/*******************************************************************************
* Function Name  : EEPROM_W
*******************************************************************************/

u8 EEPROM_B(u16 addr,u8 data)
{
      do{
	   FLASH_DUKR = 0xAE;
	   FLASH_DUKR = 0x56;	  	 
      }while((FLASH_IAPSR & 0x08) == 0);
      
      *(u8*)addr =data;  

     while((FLASH_IAPSR & 0x04) == 0);
     FLASH_IAPSR &= 0xF7;
     return  *(u8*)addr ; 
}

/*******************************************************************************
* Function Name  : 
* Description    : 
*******************************************************************************/
//void BEEP(u8 data) 
//{
//      CLK_PCKENR1 |= 0x08;
//      BEEP_CSR=0X1E;//32*8
//      BEEP_CSR|=0X20;
//
//}
