#include "sensor.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "sys.h"

void DisInit(void)
{
	GPIO_InitTypeDef gs;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  gs.GPIO_Pin=FRONT_PIN;
  gs.GPIO_Mode=GPIO_Mode_IPU;
  gs.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(FRONT_PORT,&gs);
	gs.GPIO_Pin=JIGUANG1_PIN;
  GPIO_Init(JIGUANG1_PORT,&gs);
  gs.GPIO_Pin=JIGUANG2_PIN;
  GPIO_Init(JIGUANG2_PORT,&gs);
	gs.GPIO_Pin=JIGUANG3_PIN;
  GPIO_Init(JIGUANG3_PORT,&gs);
}
/**
 * @brief Get the Dis object
 * 前后均未检测到返回0
 * 左前检测到返回1
 * 右后检测到返回2
 * 均检测返回3
 * @return uint16_t 
 */
uint16_t GetDis(void)
{
  uint16_t value=0;

  if(JIGUANG1_In == 0){
    value+=4;
  }
  if(JIGUANG2_In == 0){
    value+=2;
  }
	if(JIGUANG3_In == 0){//光电检测到返回0
    value+=1;
  }
	return value;
}
