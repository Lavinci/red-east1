#ifndef _MINE_H_
#define _MINE_H_
#include "stm32f10x.h"
#include "sys.h"
#include "mine.h"
#include "sensor.h"


extern long int Target_A,Target_B,Target_C,Target_D;
extern int delay_5ms;
extern u8 delay_flag;
extern u8 delay_flag1;
int delay_5ms1;
#define A 5
uint16_t filter(uint16_t in)
{
	int i,j,min,tmp,buff[50];
	for(i=0;i<50;i++)
	{
		buff[i]=GetDis();
	}
	min=0;
	for(i=0;i<49;i++)
	{	for(j=i;j<49;j++)
		{
			if(buff[j
				]<buff[min]) min=j;
		}
		tmp=buff[j];
		buff[j]=buff[i];
		buff[i]=tmp;
	}
	return buff[3];
}
void delayy(int time)
{
	delay_flag=1;
	delay_5ms=0;
	while(delay_5ms<time){oled_show();}//{;} //
	delay_flag=0;
}

void SABCD(long int MotoASpeed,long int MotoBSpeed,long int MotoCSpeed,long int MotoDSpeed)
{
  Target_A = MotoASpeed;
  Target_B = MotoBSpeed;
  Target_C = MotoCSpeed;
  Target_D = MotoDSpeed;
}

void Stop()
{
	SABCD(0,0,0,0);
}

void Go(int speed,int time)
{
	SABCD(speed,speed,speed,speed);
	delayy(time);
}

void Back(int speed,int time)
{
	SABCD(-speed,-speed,-speed,-speed);
				
	delayy(time);
}

void TurnLeft(int speed,int time)
{
	SABCD(-speed,-speed,speed,speed);
				
	delayy(time);
}

void TurnRight(int speed,int time)
{
	SABCD(speed,speed,-speed,-speed);
				
	delayy(time);
}

void LGo(int speed,int time)
{
	SABCD(speed,0,speed,0);
				
	delayy(time);
}

void RGo(int speed,int time)
{
	SABCD(0,speed,0,speed);
				
	delayy(time);
}

void Left(long int speed,long int time)
{
	SABCD(speed,-speed,speed,-speed);				
	delayy(time);
}
void Right(long int speed,long int time)
{
	SABCD(-speed,speed,-speed,speed);				
	delayy(time);
}

void walk(long int Runtime,long int Alltime)
{
	uint16_t status;
	delay_flag1=1;
	delay_5ms1=0;
	while(delay_5ms1<Alltime)
	{
		status=filter(10);
		if(FRONT_In == 0){ Stop();delay_5ms1=Alltime; }
		switch(status)
		{
			case 0: Left(13,1);break;
			//case 1: Right(10,1);break;
			case 2:	Go(35,1);break;
			case 3: TurnLeft(18,1);break;
		//	case 4: TurnRight(10,1);break;
		case 6: TurnRight(18,1);break;
		case 7:Right(13,1);break;
		default:OLED_ShowString(10,40,"Unknow!!");OLED_Refresh_Gram();break;
		}
	}
	delay_flag1=0;
}

void walk2(long int Runtime,long int Alltime)
{
	uint16_t status;
	delay_flag1=1;
	delay_5ms1=0;
	while(delay_5ms1<Alltime)
	{
		status=filter(10);
		if(FRONT_In == 1){ Stop();delay_5ms1=Alltime; }
		switch(status)
		{
			case 0: Left(13,1);break;
			//case 1: Right(10,1);break;
			case 2:	Go(35,1);break;
			case 3: TurnLeft(10,1);break;
		//	case 4: TurnRight(10,1);break;
		case 6: TurnRight(10,1);break;
		case 7:Right(13,1);break;
		default:OLED_ShowString(10,40,"Unknow!!");OLED_Refresh_Gram();break;
		}
	}
	delay_flag1=0;
}
void walk3(long int Runtime,long int Alltime)
{
	uint16_t status;
	delay_flag1=1;
	delay_5ms1=0;
	while(delay_5ms1<Alltime)
	{
		status=filter(10);
		if(FRONT_In == 0){ Stop();delay_5ms1=Alltime; }
		switch(status)
		{
			case 0: Left(13,1);break;
			//case 1: Right(10,1);break;
			case 2:	Back(35,1);break;
			case 3: TurnLeft(18,1);break;
		//	case 4: TurnRight(10,1);break;
		case 6: TurnRight(18,1);break;
		case 7:Right(13,1);break;
		default:OLED_ShowString(10,40,"Unknow!!");OLED_Refresh_Gram();break;
		}
	}
	delay_flag1=0;
}

void walk4(long int Runtime,long int Alltime)
{
	uint16_t status;
	delay_flag1=1;
	delay_5ms1=0;
	while(delay_5ms1<Alltime)
	{
		status=filter(10);
		if(FRONT_In == 1){ Stop();delay_5ms1=Alltime; }
		switch(status)
		{
			case 0: Left(13,1);break;
			//case 1: Right(10,1);break;
			case 2:	Back(35,1);break;
			case 3: TurnLeft(18,1);break;
		//	case 4: TurnRight(10,1);break;
		case 6: TurnRight(18,1);break;
		case 7:Right(13,1);break;
		default:OLED_ShowString(10,40,"Unknow!!");OLED_Refresh_Gram();break;
		}
	}
	delay_flag1=0;
}

void strightR()
{
	walk2(50,40000);
	Go(20,100);
	TurnRight(20,250);
	Go(20,100);
	walk(50,40000);
	Go(20,400);
	TurnLeft(20,250);
	Back(20,400);
}
void strightL()
{
	walk4(50,400000);
	Go(20,200);
	TurnRight(20,250);
	Back(25,200);
	walk3(50,40000);
	Back(25,250);
	TurnRight(20,250);
	Go(20,400);
}

#endif
