#include "./Init.h"
#include "stm32f10x_rcc.h"

TIM_OCInitTypeDef tos;

/*---------------------------------*/
static u8 fac_us;
static u16 fac_ms;


void delay_init(u8 SYSCLK)
{
  SysTick->CTRL &=~(1<<2); //??????
  fac_us=SYSCLK/8;
  fac_ms=(u16)fac_us*1000;
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
