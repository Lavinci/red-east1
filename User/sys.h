#ifndef __SYS_H
#define __SYS_H	  
#include <stm32f10x.h>   

//0,?????ucos
//1,???ucos
#define SYSTEM_SUPPORT_UCOS		0		//?????????????????UCOS
																	    
	 
//¦Ë??????,???51?????GPIO???????
//??????????,?¦Ï?<<CM3??????>>??????(87?~92?).
//IO?????????
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO???????
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO?????,???????IO??!
//???n???§³??16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //??? 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //???? 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //??? 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //???? 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //??? 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //???? 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //??? 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //???? 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //??? 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //????

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //??? 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //????

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //??? 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //????
/////////////////////////////////////////////////////////////////
//Ex_NVIC_Config??????
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 

#define FTIR   1  //????????
#define RTIR   2  //?????????
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "usart.h"
#include "usartx.h"
#include "adc.h"
#include "timer.h"
#include "motor.h"
#include "encoder.h"
#include "ioi2c.h"
#include "mpu6050.h"
#include "show.h"								   
#include "exti.h"
#include "DataScope_DP.h"
#include "CAN.h"
#include "stmflash.h"
//#include "Servo.h"

#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	
extern int Encoder_A,Encoder_B,Encoder_C,Encoder_D;                    //???????????????
extern long int Motor_A,Motor_B,Motor_C,Motor_D;                   //???PWM????
extern u8 Flag_Left,Flag_Right,Flag_sudu,Flag_Direction; //??????????????
extern u8 Flag_Stop,Flag_Show;                               //?????¦Ë?? ??????¦Ë ????? ?????
extern long int Target_A,Target_B,Target_C,Target_D,Rate_A,Rate_B,Rate_C,Rate_D;                      //?????????
extern  int Voltage,Voltage_Zheng,Voltage_Xiao;                //????????????????
extern float Angle_Balance,Gyro_Balance,Gyro_Turn;           //?????? ????????? ?????????
extern float Show_Data_Mb;                                    //??????????????????????????????
extern int Temperature;
extern u32 Distance;                                           //?????????
extern u8 Bi_zhang,delay_50,delay_flag;
extern float Acceleration_Z;
extern int RC_Velocity,RC_Position;
extern int Encoder_A_EXTI;
extern u8 Run_Flag,PID_Send,Flash_Send,Turn_Flag;
extern u8 rxbuf[8],Urxbuf[8],txbuf[8],txbuf2[8],CAN_ON_Flag,Usart_ON_Flag,Usart_Flag;
extern float Pitch,Roll,Yaw,Move_X,Move_Y,Move_Z; 
extern long int Position_A,Position_B,Position_C,Position_D;
extern u16 PID_Parameter[10],Flash_Parameter[10];
extern float	Position_KP,Position_KI,Position_KD;  //¦Ë?????PID????
extern float Velocity_KP,Velocity_KI;	                    //??????PID????
/////////////////////////////////////////////////////////////////  
void Stm32_Clock_Init(u8 PLL);  //???????  
void Sys_Soft_Reset(void);      //????¦Ë
void Sys_Standby(void);         //?????? 	
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//?????????
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);//????NVIC????
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//?????§Ø?
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);//???§Ø????¨²???(???GPIOA~G)
void JTAG_Set(u8 mode);
//////////////////////////////////////////////////////////////////////////////
//??????????
void WFI_SET(void);		//???WFI???
void INTX_DISABLE(void);//????????§Ø?
void INTX_ENABLE(void);	//?????????§Ø?
void MSR_MSP(u32 addr);	//?????????
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include <string.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#endif











