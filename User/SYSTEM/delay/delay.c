#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
#endif

////////////////////////////////////////////////////////////////////////////////// 	 

static u8  fac_us=0;//us延时倍乘数			   
static u16 fac_ms=0;//ms延时倍乘数,在ucos下,代表每个节拍的ms数

void delay_init(u8 SYSCLK)
{
  SysTick->CTRL &=~(1<<2); //??????
  fac_us=SYSCLK/8;
  fac_ms=(u16)fac_us*1000;
}								    

    		
	    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01 ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
} 

void delayUs(u32 _us)
{
  u32 temp;
  SysTick->LOAD=_us*fac_us;
  SysTick->VAL=0X00;
  SysTick->CTRL=0X01; //????
  do{
    temp=SysTick->CTRL;
  }while( temp&0x01 && !(temp&(1<<16)) );//????????

  SysTick->CTRL=0x00;//????
  SysTick->VAL=0x00;  //????
}

void delayMs(u16 _ms)
{
  u32 temp;
  SysTick->LOAD=_ms*fac_ms;
  SysTick->VAL=0X00;
  SysTick->CTRL=0X01; //????
  do{
    temp=SysTick->CTRL;
  }while( temp&0x01 && !(temp&(1<<16)) );//????????

  SysTick->CTRL=0x00;//????
  SysTick->VAL=0x00;  //????
}

			 



































