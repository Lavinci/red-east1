#include "Servo.h"
#include "exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "control.h"	


NVIC_InitTypeDef ns;

extern u8 Ball[8];
void ServoInit(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
	
		TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 
	
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
	
    TIM_TimeBaseStructure.TIM_Period = 199;//199
    TIM_TimeBaseStructure.TIM_Prescaler =7199;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 185;//
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;

		TIM_OC1Init(TIM1, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_OCInitStructure.TIM_Pulse = 195;//
		TIM_OC3Init(TIM1, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
//-----------------------------------------------------------		

  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;

  TIM_BDTRInitStructure.TIM_DeadTime = 0;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
//-----------------------------------------------------------		

    TIM_CtrlPWMOutputs(TIM1,ENABLE);//

    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);

}

void Servo_Right(void)
{
  int i;
	mpu_set_dmp_state(0);
//-------------------------------	
	 for(i=188;i<=192;i++)
	 {

   TIM_SetCompare3(TIM1,i);
   delayMs(50);	
	TIM_SetCompare3(TIM1,200);
		delayMs(1000); 
	TIM_SetCompare3(TIM1,188);
   delayMs(500);	
	TIM_SetCompare3(TIM1,200);
	 }
	 
//-------------------------------		 
	 mpu_set_dmp_state(1);
}

void Servo_Left(void)
{
  int i;
  mpu_set_dmp_state(0);
//-------------------------------	
	 for(i=188;i>=183;i--)//zuobian
	 {

	 TIM_SetCompare3(TIM1,i);
   delayMs(50);	
	TIM_SetCompare3(TIM1,0);
		delayMs(1000);	
	TIM_SetCompare3(TIM1,188);
   delayMs(500);	
	 }
	TIM_SetCompare3(TIM1,0);	
//-------------------------------		 
	 	 mpu_set_dmp_state(1);
}

void EXTI4_IRQHandler()
{


	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
  {
    	EXTI_ClearITPendingBit(EXTI_Line4);
		
//------------关闭位置PID，设置电机速度为零-----------------------------	
  ns.NVIC_IRQChannel=EXTI15_10_IRQn;
  ns.NVIC_IRQChannelCmd=DISABLE;
  NVIC_Init(&ns);	
	Set_Pwm(0,0,0,0);

//这个是用树莓派返回的数值表来确认击打哪一边
  if(Ball[1])
    Servo_Left();//击打左臂

//---------开启位置PID-------------------------		
	ns.NVIC_IRQChannel=EXTI15_10_IRQn;
  ns.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&ns);	
  }
}

void EXTI3_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
  {
    	EXTI_ClearITPendingBit(EXTI_Line3);
		
//------------关闭位置PID，设置电机速度为零-----------------------------	
  ns.NVIC_IRQChannel=EXTI15_10_IRQn;
  ns.NVIC_IRQChannelCmd=DISABLE;
  NVIC_Init(&ns);	
	Set_Pwm(0,0,0,0);

//这个是用树莓派返回的数值表来确认击打哪一边
  if(Ball[0])
	  Servo_Right();//右击打

	
	
	
//---------开启位置PID-------------------------		
	ns.NVIC_IRQChannel=EXTI15_10_IRQn;
  ns.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&ns);	
  }
}



	
