#ifndef _SERVO_H_
#define _SERVO_H_
#include "stm32f10x.h"
#include "sys.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_it.h"
#include "stm32f10x_tim.h"

void ServoInit(void);

void Servo_Right(void);

void Servo_Left(void);

#endif
