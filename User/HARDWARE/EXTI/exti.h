#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"

#define INT PBin(15)   //PB5���ӵ�MPU6050���ж�����

void EXTI_Initmm(void);

void EXTImm_Enable(void);

void EXTImm_Disable(void);

void EXTI_InitTree(void);

void EXTI_EnableTree(void);

void EXTI_DisableTree(void);

#endif

























