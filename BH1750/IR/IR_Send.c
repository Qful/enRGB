#include <ioCC2540.h>
#include <IR_Send.h>
//#include <hal_mcu.h>
#define uint unsigned int
#define uchar unsigned char
#define u32 unsigned long
#define u8  unsigned char
#define OP P1_7      //�������
volatile uint count_T3;
volatile uchar Flag_Ir_Send;
volatile  uint endcount; 
void SendIRdata(volatile uchar iraddr1,volatile uchar p_irdata1)  
{   
                                                              
//      halIntState_t intState;                                   
//      HAL_ENTER_CRITICAL_SECTION(intState); //��ʱ����ʼ��
      P1SEL &=~0X80;              //��ͨI/O�� 
      P1DIR |= 0x80;              //17 ����
      T3CTL |= 0x08 ;             //������ж�     
      T3IE = 1;                   //�����жϺ�T3�ж�
//      T3CTL|=0X20;              //2��Ƶ��16us 
      T3CTL &= ~0X03;             //�Զ���װ 00��>0xff
      T3CTL |=0X10;               //����
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
    while(count_T3<endcount);                            //����9ms����ʼ��   
    Flag_Ir_Send=0; 
    endcount=282;   
    count_T3=0;
    while(count_T3<endcount);                   //����4.5ms�Ľ����		 //��ʱ�� �� 9MS~14.5ms ֮�� �յ����Ǹߵ�ƽ
    irdata=iraddr1; 			   //���͵�ַ
    for(i=0;i<8;i++) 			 //�ȷ���0.56ms��38KHZ���Ⲩ����������0.56ms�ĵ͵�ƽ��
    {    			    
        endcount=34; 
        Flag_Ir_Send=1; 
        count_T3=0;
        while(count_T3<endcount);                   //ֹͣ���ͺ����źţ��������еĸߵ�ƽ��    
        Flag_Ir_Send=0; 
        if(irdata&0x01)                             //�ж϶���������λΪ1����0 
        {  
            endcount=102;                           //1Ϊ��ĸߵ�ƽ
        }      
        else 
        {  
            endcount=34;                            //0Ϊխ�ĸߵ�ƽ
        } 
        count_T3=0;  
        
        while(count_T3<endcount);
        irdata=irdata>>1; 
    }
    irdata=iraddr2;                         //���͵�ַ�ķ���
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
    irdata = p_irdata1; 		 //���Ͱ�λ����
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
    irdata = p_irdata2;              //���Ͱ�λ���ݷ���
    for(i=0;i<8;i++) 
    {  
        endcount=34; 	                        //��ʼ��
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
    Flag_Ir_Send=1; 		                         //����
    count_T3=0; 
    while(count_T3<endcount);
    Flag_Ir_Send=0;
    OP=1;
    //OP=0;
     T3IE=0;                                              //ֹͣ�ж�
    T3CTL &=~0X10;                                       //ֹͣ
//    HAL_EXIT_CRITICAL_SECTION(intState);
    T3IE=0;                                              //ֹͣ�ж�
    T3CTL &=~0X10;                                       //ֹͣ
}
#pragma vector = T3_VECTOR //��ʱ��T3
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
                //count_T8=count_T8; //���ڶ�ʱ��3����
                //endcount=endcount; 
 }
