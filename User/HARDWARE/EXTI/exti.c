#include "exti.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "Servo.h"

void EXTI_Initmm(void)
{
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟	   	 
	GPIOB->CRH&=0X0FFFFFFF; 
	GPIOB->CRH|=0X80000000;//PB5上拉输入
  GPIOB->ODR|=1<<15;      //PB5上拉	
	Ex_NVIC_Config(GPIO_B,15,FTIR);		//下降沿触发
	MY_NVIC_Init(2,1,EXTI15_10_IRQn,2);  	//抢占2，子优先级1，组2
}
void EXTImm_Enable(void)
{
	NVIC_InitTypeDef ns;
	ns.NVIC_IRQChannel=EXTI15_10_IRQn;
	ns.NVIC_IRQChannelPreemptionPriority=2;
	ns.NVIC_IRQChannelSubPriority=1;
	ns.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&ns);
}

void EXTImm_Disable(void)
{
	NVIC_InitTypeDef ns;
	ns.NVIC_IRQChannel=EXTI15_10_IRQn;
	ns.NVIC_IRQChannelPreemptionPriority=2;
	ns.NVIC_IRQChannelSubPriority=1;
	ns.NVIC_IRQChannelCmd=DISABLE;
	NVIC_Init(&ns);
}

void EXTI_InitTree(void)
{
	GPIO_InitTypeDef gs;
	NVIC_InitTypeDef ns;
	EXTI_InitTypeDef es;
	
	gs.GPIO_Pin=GPIO_Pin_4;
	gs.GPIO_Mode=GPIO_Mode_IPU;
	gs.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gs);
	gs.GPIO_Pin=GPIO_Pin_3;
	gs.GPIO_Mode=GPIO_Mode_IPU;
	gs.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gs);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
// EXTI4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	ns.NVIC_IRQChannel=EXTI4_IRQn;
	ns.NVIC_IRQChannelPreemptionPriority=2;
	ns.NVIC_IRQChannelSubPriority=0;
	ns.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&ns);
// EXTI3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	ns.NVIC_IRQChannel=EXTI3_IRQn;
	ns.NVIC_IRQChannelPreemptionPriority=2;
	ns.NVIC_IRQChannelSubPriority=0;
	ns.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&ns);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
	es.EXTI_Line=EXTI_Line4;
	es.EXTI_Mode=EXTI_Mode_Interrupt;
	es.EXTI_Trigger=EXTI_Trigger_Falling;
	es.EXTI_LineCmd=ENABLE;
	EXTI_Init(&es);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
	es.EXTI_Line=EXTI_Line3;
	es.EXTI_Mode=EXTI_Mode_Interrupt;
	es.EXTI_Trigger=EXTI_Trigger_Falling;
	es.EXTI_LineCmd=ENABLE;
	EXTI_Init(&es);
	
	
}
void EXTI_EnableTree(void)
{
	NVIC_InitTypeDef ns;
	ns.NVIC_IRQChannel=EXTI4_IRQn;
	ns.NVIC_IRQChannelPreemptionPriority=0;
	ns.NVIC_IRQChannelSubPriority=0;
	ns.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&ns);

}

void EXTI_DisableTree(void)
{
	GPIO_InitTypeDef gs;
	NVIC_InitTypeDef ns;
	EXTI_InitTypeDef es;

	gs.GPIO_Mode=GPIO_Mode_IPU;
	gs.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gs);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	ns.NVIC_IRQChannel=EXTI4_IRQn;
	ns.NVIC_IRQChannelPreemptionPriority=0;
	ns.NVIC_IRQChannelSubPriority=0;
	ns.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&ns);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
	es.EXTI_Line=EXTI_Line4;
	es.EXTI_Mode=EXTI_Mode_Interrupt;
	es.EXTI_Trigger=EXTI_Trigger_Falling;
	es.EXTI_LineCmd=ENABLE;
	EXTI_Init(&es);
}





