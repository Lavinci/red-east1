#include "sys.h"
#include "Servo.h"
#include "control.h"
#include "sensor.h"
#include "camera.h"
#include "mine.h"
u8 Ball[8];
//------------------------------------
u8 Flag_Left,Flag_Right,Flag_Direction=0;   //蓝牙遥控相关的变量
u8 Flag_Stop=1,Flag_Show=0;                 //停止标志位和 显示标志位 默认停止 显示打开
int Encoder_A,Encoder_B,Encoder_C,Encoder_D;          //编码器的脉冲计数
long int Position_A,Position_B,Position_C,Position_D,Rate_A,Rate_B,Rate_C,Rate_D; //PID控制相关变量
int Encoder_A_EXTI;                       //通过外部中断读取的编码器数据
long int Motor_A,Motor_B,Motor_C,Motor_D;        //电机PWM变量
long int Target_A,Target_B,Target_C,
	Target_D;     //电机目标值
int Voltage;                             //电池电压采样相关的变量
float Show_Data_Mb;                      //全局显示变量，用于显示需要查看的数据
u8 delay_50,delay_flag,delay_flag1;                          //延时相关变量
u8 Run_Flag=0;  												//蓝牙遥控相关变量和运行状态标志位
u8 rxbuf[8],Urxbuf[8],CAN_ON_Flag=0,Usart_ON_Flag=0,Usart_Flag,PID_Send,Flash_Send;  //CAN和串口控制相关变量
u8 txbuf[8],txbuf2[8],Turn_Flag;             //CAN发送相关变量
float Pitch,Roll,Yaw,Move_X,Move_Y,Move_Z;   //三轴角度和XYZ轴目标速度
u16 PID_Parameter[10],Flash_Parameter[10];  //Flash相关数组
float	Position_KP=40,Position_KI=0,Position_KD=40;  //位置控制PID参数
float Velocity_KP=10,Velocity_KI=10;	          //速度控制PID参数
int RC_Velocity=20,RC_Position=300;         //设置遥控的速度和位置值
//------------------------------------
int cnt=0;

int main()
{
	Stm32_Clock_Init(9);            //=====系统时钟设置
	delay_init(72);                 //=====延时初始化
	ServoInit();
	JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
	LED_Init();                     //=====初始化与 LED 连接的硬件接口
//	KEY_Init();                     //=====按键初始化
	/* 这里预留为跑路或者栽树模式*/
	//if(MODE==0)Run_Flag=1;          //=====启动的过程中，根据模式选择开关确定进入位置模式还是速度模式
	//else Run_Flag=0;                //=====启动的过程中，根据模式选择开关确定进入位置模式还是速度模式
	Run_Flag=0;											//固定为速度模式
	OLED_Init();                    //=====OLED初始化
	uart2_init(36,9600);            //=====串口2初始化
	Encoder_Init_TIM2();            //=====编码器接口
	Encoder_Init_TIM3();            //=====编码器接口
	Encoder_Init_TIM4();            //=====初始化编码器C
	Encoder_Init_TIM5();            //=====初始化编码器D
  Adc_Init();                     //=====adc初始化
	IIC_Init();                     //=====IIC初始化
  MPU6050_initialize();           //=====MPU6050初始化
//  DMP_Init();                     //=====初始化DMP
	MiniBalance_PWM_Init(7199,0);   //=====初始化PWM 10KHZ，用于驱动电机
	if(KEY==0) Flash_Read();        //=====读取Flash里面的参数
  EXTI_Initmm();                    //=====MPU6050 5ms定时中断初始化
	EXTI_InitTree();
	DisInit();
	Camera_Init();

	Ball[0]=1;
	Ball[1]=1;

	delayy(200);
	OLED_ShowString(10,40,"Start");OLED_Refresh_Gram();
	delayy(200);

	while(1)
	{
		//Servo_Right();
		Left(10,400000);

/*		//walk(50,4000);
		//出发
		Go(20,250);

		for	(cnt=0;cnt<5;cnt++)
		{
			walk(50,40000);
			Go(30,200);
			//Stop();
			//SetState(cnt); //到达垄1
			//delayy(400);
			//Go(10,200);
		}		
		Stop();
		Go(10,80);
		TurnRight(20,260);
		walk(50,600);

		for(cnt=0;cnt<6;cnt++)
		{
			strightR();
			strightL();
			while(1);
		}

		Stop();
		while(1);*/
		//walk4(50,400000);
	}

	
	
	
}
