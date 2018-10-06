#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_it.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

void Camera_Init(void);

void SetState(u8 pos);

#endif
