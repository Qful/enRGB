#include <ioCC2540.h>
#include <uart.h>
#include <Reccept.h>
#include <string.h>

static uchar Ir_Buf[4];
static uchar recFlag = 0,i;
static uint recTemp = 0;
static uint recNumBit = 0;
static uint recNumByte = 0;
static unsigned int time = 0;

//����LED�Ķ˿�
#define LED1  P1_0
#define LED2  P1_1
#define IR_Tx P1_7
#define IR_Rx P1_6

/****************************************************************
    ��ʱ����											
****************************************************************/
void Delay_ms(uint n)
{
  uint i,j;
  for(i=0;i<n;i++)
    for(j=0;j<1774;j++);
}

void delay_us(unsigned int i)
{
  unsigned int j=18;
  while(i--)
  {
    while(j--);
    j=18;
  }
}

void IO_Init()
{
  P1DIR |= 0x01; 
  P1DIR |= 0x02; 	
  P1DIR &= ~0x40; 	//16 ����
  P1DIR |= 0x80;    //17 ����
  IR_Tx = 1;
  LED1 = IR_Rx;
  LED2 = 1;
}

/****************************
KEY��ʼ������--�ⲿ�жϷ�ʽ
*****************************/
void InitEx()
{
  P1DIR &=~ 0X40;    //P16����
  P1DIR |= 0X80;     //P17���
  IR_Tx = 1;
  
  P1IEN |= 0X40;  //P16 ����Ϊ�жϷ�ʽ 
  PICTL &=~ 0X40; // �½��ش���   
  IEN2 |= 0X10;   // ����P1���ж�; 
  P1IFG = 0x00;   // ��ʼ���жϱ�־λ
  EA = 1; 
}
/*******************************
 * ��ȡ�͵�ƽʱ��
***********************************/
unsigned char Ir_Get_Low()
{
  unsigned int t=0;	 
  while(!IR_Rx)
  {	 
    t++;delay_us(1);					 
    if(t==250){
		return t;} //��ʱ���
  }
  return t;
}

/******************************************************************************************
 * ��ȡ�ߵ�ƽʱ��
******************************************************************************************/
unsigned char Ir_Get_High()
{
  unsigned int t=0;	 
  while(IR_Rx)
  {	 
    t++;delay_us(1);					 
    if(t==250){
		return t;} //��ʱ���
  }
  return t;
}

/**************************** 
      �жϴ����� 
*****************************/ 
#pragma vector = P1INT_VECTOR   
  __interrupt void P1_ISR(void)
{   
  //*************������ 9ms + 4.5ms************
  time = Ir_Get_High();
  
  if(recFlag)     
  {
    if( (time>5)&&(time<40) )  // 0
    {
      recTemp &= ~0x01;
    }
    else if( (time>40)&&(time<99) )  // 1
    {
      recTemp |= 0x01;
	    LED1 = 1;
		  LED2 = 1;
    }
    else
    {
      recFlag = 0;      //�Ƿ�����
	  LED2 = 0;
	  LED1 = 0;
    }
    
    if(recNumBit==7)
    {
      recNumBit = 0;
      Ir_Buf[recNumByte] = recTemp;
      if(recNumByte==3)
      {
        recFlag = 0;
        for(i=0;i<4;i++)   
        {
          UartSend_Uchar(Ir_Buf[i]);
          UartSend_String(" ",1); 
        }
        UartSend_String("\n",1); 
      }
      else
      {
        recNumByte++;
      }  
    }
    else
    {
      recNumBit++;
      recTemp<<=1;
    }
  }
  else
  {
    if( (time>180)&&(time<220) )   //4.5ms����
    {
      recFlag = 1;
      recNumBit = 0;
      recNumByte = 0;
    }
  } 
  P1IFG = 0;             //���жϱ�־ 
  P1IF = 0;             //���жϱ�־ 
} 