#ifndef _INIT_H_
#define _INIT_H_
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
/*-----------------------------------*/

#include <string.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*-----------------------------------*/
//接口在此定义 PORT以P开头 GPIO以G开头
//LED B13
#define PLED GPIOB
#define GLED GPIO_Pin_13

//MOTOA C4 C6
#define PMOTOA1 GPIOC
#define GMOTOA1 GPIO_Pin_6
#define PMOTOA2 GPIOC
#define GMOTOA2 GPIO_Pin_4
//MOTOB C7 B0
#define PMOTOB1 GPIOC
#define GMOTOB1 GPIO_Pin_7
#define PMOTOB2 GPIOB
#define GMOTOB2 GPIO_Pin_0
//MOTOC C8 C5
#define PMOTOC1 GPIOC
#define GMOTOC1 GPIO_Pin_8
#define PMOTOC2 GPIOC
#define GMOTOC2 GPIO_Pin_5
//MOTOD B1 C9
#define PMOTOD1 GPIOC
#define GMOTOD1 GPIO_Pin_9
#define PMOTOD2 GPIOB
#define GMOTOD2 GPIO_Pin_1

//pwm-TIM8

#define GENERAL_TIM_Prescaler 1//3600-1 //72kkHZ/36k=2kHZ =0.5ms
#define GENERAL_TIM_Period 2000 //周期2k/20= 10HZ=10ms


/*--------------------------------------*/


//初始化gpio

extern void delay_init(u8 SYSCLK);
extern void delayUs(u32 _us); //
extern void delayMs(u16 _ms); //最大为1864ms

#endif
