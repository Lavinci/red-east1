#include "camera.h"
#include "Init.h"

u8 pos;
u8 tree[8];

void Camera_Init()
{
	GPIO_InitTypeDef gs;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  gs.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_4;
  gs.GPIO_Mode= GPIO_Mode_IPD;
  gs.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&gs);
}

void SetState(u8 pos)
{
  u8 i,left,right;
  for(i=0;i<10;i++)
  {
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2))
      left++;
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4));
      right++;
    delayMs(10);
  }

  if(left>8)  tree[pos-1]=1;
  else        tree[pos-1]=0;

  if(right>8) tree[pos]=1;
  else        tree[pos]=0;
}
