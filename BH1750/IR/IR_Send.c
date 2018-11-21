#include <ioCC2540.h>
#include <IR_Send.h>
//#include <hal_mcu.h>
#define uint unsigned int
#define uchar unsigned char
#define u32 unsigned long
#define u8  unsigned char
#define OP P1_7      //红外输出
volatile uint count_T3;
volatile uchar Flag_Ir_Send;
volatile  uint endcount; 
void SendIRdata(volatile uchar iraddr1,volatile uchar p_irdata1)  
{   
                                                              
//      halIntState_t intState;                                   
//      HAL_ENTER_CRITICAL_SECTION(intState); //定时器初始化
      P1SEL &=~0X80;              //普通I/O口 
      P1DIR |= 0x80;              //17 发送
      T3CTL |= 0x08 ;             //开溢出中断     
      T3IE = 1;                   //开总中断和T3中断
//      T3CTL|=0X20;              //2分频！16us 
      T3CTL &= ~0X03;             //自动重装 00－>0xff
      T3CTL |=0X10;               //启动
      EA=1; 
    volatile uint end;  uint i;uchar irdata;//end=endcount
    uchar iraddr2=~iraddr1;
    uchar p_irdata2=~p_irdata1;
    endcount=0;                 
    count_T3 = 0;  
    Flag_Ir_Send = 0; 
    OP=1; 
    endcount=553; 
    Flag_Ir_Send=1; 
    count_T3=0; 
    while(count_T3<endcount);                            //发送9ms的起始码   
    Flag_Ir_Send=0; 
    endcount=282;   
    count_T3=0;
    while(count_T3<endcount);                   //发送4.5ms的结果码		 //总时间 在 9MS~14.5ms 之间 收到的是高电平
    irdata=iraddr1; 			   //发送地址
    for(i=0;i<8;i++) 			 //先发送0.56ms的38KHZ红外波（即编码中0.56ms的低电平）
    {    			    
        endcount=34; 
        Flag_Ir_Send=1; 
        count_T3=0;
        while(count_T3<endcount);                   //停止发送红外信号（即编码中的高电平）    
        Flag_Ir_Send=0; 
        if(irdata&0x01)                             //判断二进制数个位为1还是0 
        {  
            endcount=102;                           //1为宽的高电平
        }      
        else 
        {  
            endcount=34;                            //0为窄的高电平
        } 
        count_T3=0;  
        
        while(count_T3<endcount);
        irdata=irdata>>1; 
    }
    irdata=iraddr2;                         //发送地址的反码
    for(i=0;i<8;i++)
    {
        endcount=34; 
        Flag_Ir_Send=1; 
        count_T3=0; 
        while(count_T3<endcount);    
        Flag_Ir_Send=0; 
        if(irdata&0x01) 
        {  
             endcount=102; 
        } 
        
        else 
        {  
             endcount=34; 
        } 
       count_T3=0; 
       while(count_T3<endcount);
        irdata=irdata>>1; 
    }
    irdata = p_irdata1; 		 //发送八位数据
    for(i=0;i<8;i++) 
    {
        endcount=34; 
        Flag_Ir_Send=1; 	
       count_T3=0; 
      while(count_T3<endcount); 
        Flag_Ir_Send=0;    
        if(irdata&0x01) 
        {  
            endcount=104; 
        }        
        else
        {  
            endcount=34; 
        }        
       count_T3=0; 
        while(count_T3<endcount);
        irdata=irdata>>1; 
    }	                  
    irdata = p_irdata2;              //发送八位数据反码
    for(i=0;i<8;i++) 
    {  
        endcount=34; 	                        //开始码
        Flag_Ir_Send=1; 
      count_T3=0;   
       while(count_T3<endcount);     
        Flag_Ir_Send=0; 
        if(irdata&0x01) 
        {
             endcount=102;
        }
        else
        {
            endcount=34;
        }
        count_T3=0;  
        while(count_T3<endcount);
        irdata=irdata>>1; 
    }
    endcount=34; 
    Flag_Ir_Send=1; 		                         //发送
    count_T3=0; 
    while(count_T3<endcount);
    Flag_Ir_Send=0;
    OP=1;
    //OP=0;
     T3IE=0;                                              //停止中断
    T3CTL &=~0X10;                                       //停止
//    HAL_EXIT_CRITICAL_SECTION(intState);
    T3IE=0;                                              //停止中断
    T3CTL &=~0X10;                                       //停止
}
#pragma vector = T3_VECTOR //定时器T3
 __interrupt void T3_ISR(void) 
 {              
      	count_T3++;  
	if (Flag_Ir_Send==1) 
	{  
	//OP=~OP;
                  OP=~OP;
	}   
	else 
	{  
	//OP = 0; 
                  OP=0;
	}  
                //count_T8=count_T8; //用于定时器3计数
                //endcount=endcount; 
 }
