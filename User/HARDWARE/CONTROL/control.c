#include "control.h"	
#include "filter.h"	
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_it.h"
#include "stm32f10x_tim.h"


u8 Flag_Target,Flag_Change;                             //相关标志位
u8 temp1;                                               //临时变量
float Voltage_Count,Voltage_All; 											 //电压采样相关变量
float Gyro_K=0.004;     				  											//陀螺仪比例系数
int j;

extern int delay_5ms1;
extern u8 delay_flag1;
int x;
int delay_5ms=0;



#define a_PARAMETER          (0.095f)               
#define b_PARAMETER          (0.086f)         
/**************************************************************************
函数功能：小车运动数学模型
入口参数：X Y Z 三轴速度或者位置
返回  值：无
**************************************************************************/
void Kinematic_Analysis(float Vx,float Vy,float Vz)
{
        Target_A   = -Vx+Vy-Vz*(a_PARAMETER+b_PARAMETER);
        Target_B   = +Vx+Vy-Vz*(a_PARAMETER+b_PARAMETER);
	      Target_C   = -Vx+Vy+Vz*(a_PARAMETER+b_PARAMETER);
				Target_D   = +Vx+Vy+Vz*(a_PARAMETER+b_PARAMETER);
}
/**************************************************************************
函数功能：获取位置控制过程速度值
入口参数：X Y Z 三轴位置变化量
返回  值：无
**************************************************************************/
void Kinematic_Analysis2(float Vx,float Vy,float Vz)
{
	      Rate_A   = -Vx+Vy-Vz*(a_PARAMETER+b_PARAMETER);
        Rate_B   = +Vx+Vy-Vz*(a_PARAMETER+b_PARAMETER);
	      Rate_C   = -Vx+Vy+Vz*(a_PARAMETER+b_PARAMETER);
				Rate_D   = +Vx+Vy+Vz*(a_PARAMETER+b_PARAMETER);
}
/**************************************************************************
函数功能：所有的控制代码都在这里面
         5ms定时中断由MPU6050的INT引脚触发
         严格保证采样和数据处理的时间同步				 
**************************************************************************/


int EXTI15_10_IRQHandler(void) //5ms
{    
	 if(INT==0)		
	{    		 
		  EXTI->PR=1<<15;                                                      //清除LINE5上的中断标志位  		
		   Flag_Target=!Flag_Target;
		  if(delay_flag==1)
			 {
				 //if(++delay_50==10)	 delay_50=0,delay_flag=0;                     //给主函数提供50ms的精准延时
			//	 if(++delay_50==200)	 delay_50=0,delay_flag=0;                     //给主函数提供50*20ms的精准延时
				 ++delay_5ms;                     //给主函数提供50*20ms的精准延时
			 }
			 if(delay_flag1==1)
			 {
				 //if(++delay_50==10)	 delay_50=0,delay_flag=0;                     //给主函数提供50ms的精准延时
			//	 if(++delay_50==200)	 delay_50=0,delay_flag=0;                     //给主函数提供50*20ms的精准延时
				 ++delay_5ms1;                     //给主函数提供50*20ms的精准延时
			 }
     	//===10ms控制一次，为了保证M法测速的时间基准，首先读取编码器数据
			Encoder_A=Read_Encoder(2);                                          //===读取编码器的值
			Position_A+=Encoder_A;                                                 //===积分得到速度   
			Encoder_B=Read_Encoder(3);                                          //===读取编码器的值
			Position_B+=Encoder_B;                                                 //===积分得到速度   
			Encoder_C=-Read_Encoder(4);                                         //===读取编码器的值
			Position_C+=Encoder_C;                                                 //===积分得到速度   
			Encoder_D=-Read_Encoder(5);                                         //===读取编码器的值
			Position_D+=Encoder_D;                                                 //===积分得到速度   
  		Led_Flash(100);                                                        //===LED闪烁;常规模式 1s改变一次指示灯的状态	
			Voltage_All+=Get_battery_volt();                                       //多次采样累积
			if(++Voltage_Count==100) Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;//求平均值 获取电池电压	       
			if(RC_Velocity>0&&RC_Velocity<15)  RC_Velocity=15;                   //避免电机进入低速非线性区

		 if(Turn_Off(Voltage)==0)               //===如果电池电压不存在异常
		 { 			 
		  if(Run_Flag==0)//速度模式
			{		
				Motor_A=Incremental_PI_A(Encoder_A,Target_A);                         //===速度闭环控制计算电机A最终PWM
				Motor_B=Incremental_PI_B(Encoder_B,Target_B);                         //===速度闭环控制计算电机B最终PWM
				Motor_C=Incremental_PI_C(Encoder_C,Target_C);                         //===速度闭环控制计算电机C最终PWM
				Motor_D=Incremental_PI_D(Encoder_D,Target_D);                         //===速度闭环控制计算电机C最终PWM
			}
		 Xianfu_Pwm(6900);                     //===PWM限幅
		 Set_Pwm(Motor_A,Motor_B,Motor_C,Motor_D);     //===赋值给PWM寄存器  
		 }
 }
	
 
	 return 0;	 
} 


/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d)
{
	    int siqu=0;
    	if(motor_a>0)			PWMA=motor_a+siqu, INA=0;
			else  	          PWMA=7200+motor_a-siqu,INA=1;
		
		  if(motor_b>0)			PWMB=7200-motor_b-siqu,INB=1;
			else 	            PWMB=-motor_b+siqu,INB=0;
	
	    if(motor_c>0)			PWMC=7200-motor_c-siqu,INC=1;
			else 	            PWMC=-motor_c+siqu,INC=0;
	
	   if(motor_d>0)			PWMD=motor_d+siqu,IND=0;
			else 	            PWMD=7200+motor_d-siqu,IND=1;
}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：幅值
返回  值：无
**************************************************************************/
void Xianfu_Pwm(int amplitude)
{	
    if(Motor_A<-amplitude) Motor_A=-amplitude;	
		if(Motor_A>amplitude)  Motor_A=amplitude;	
	  if(Motor_B<-amplitude) Motor_B=-amplitude;	
		if(Motor_B>amplitude)  Motor_B=amplitude;		
	  if(Motor_C<-amplitude) Motor_C=-amplitude;	
		if(Motor_C>amplitude)  Motor_C=amplitude;		
	  if(Motor_D<-amplitude) Motor_D=-amplitude;	
	  if(Motor_D>amplitude)  Motor_D=amplitude;		
}
/**************************************************************************
函数功能：位置PID控制过程中速度的设置
入口参数：无、幅值
返回  值：无
**************************************************************************/
void Xianfu_Velocity(int amplitude_A,int amplitude_B,int amplitude_C,int amplitude_D)
{	
    if(Motor_A<-amplitude_A) Motor_A=-amplitude_A;	//位置控制模式中，A电机的运行速度
		if(Motor_A>amplitude_A)  Motor_A=amplitude_A;	  //位置控制模式中，A电机的运行速度
	  if(Motor_B<-amplitude_B) Motor_B=-amplitude_B;	//位置控制模式中，B电机的运行速度
		if(Motor_B>amplitude_B)  Motor_B=amplitude_B;		//位置控制模式中，B电机的运行速度
	  if(Motor_C<-amplitude_C) Motor_C=-amplitude_C;	//位置控制模式中，C电机的运行速度
		if(Motor_C>amplitude_C)  Motor_C=amplitude_C;		//位置控制模式中，C电机的运行速度
	  if(Motor_D<-amplitude_D) Motor_D=-amplitude_D;	//位置控制模式中，C电机的运行速度
		if(Motor_D>amplitude_D)  Motor_D=amplitude_D;		//位置控制模式中，C电机的运行速度
}
/**************************************************************************
函数功能：按键修改小车运行状态 
入口参数：无
返回  值：无
**************************************************************************/
void Key(void)
{	
	u8 tmp;
	tmp=click_N_Double(100); 
	if(tmp==2)Flag_Show=!Flag_Show;//双击控制显示模式                  
}

/**************************************************************************
函数功能：异常关闭电机
入口参数：电压
返回  值：1：异常  0：正常
**************************************************************************/
u8 Turn_Off( int voltage)
{
	    u8 temp;
			if(voltage<1110)//电池电压过低关闭电机
			{	                                                
      temp=1;      
      PWMA=0;
      PWMB=0;
      PWMC=0;
			PWMD=0;
      INA=0;
      INB=0;
      INC=0;		
			IND=0;								
      }
			else
      temp=0;
      return temp;			
}

/**************************************************************************
函数功能：绝对值函数
入口参数：long int
返回  值：unsigned int
**************************************************************************/
u32 myabs(long int a)
{ 		   
	  u32 temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_C (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_D (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
/**************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
int Position_PID_A (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 if(Integral_bias>100000)Integral_bias=10000;
	 if(Integral_bias<-100000)Integral_bias=-10000;
	 Pwm=Position_KP*Bias+Position_KI/100*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
int Position_PID_B (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 if(Integral_bias>100000)Integral_bias=10000;
	 if(Integral_bias<-100000)Integral_bias=-10000;
	 Pwm=Position_KP*Bias+Position_KI/100*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
int Position_PID_C (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 if(Integral_bias>100000)Integral_bias=10000;
	 if(Integral_bias<-100000)Integral_bias=-10000;
	 Pwm=Position_KP*Bias+Position_KI/100*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
int Position_PID_D (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 if(Integral_bias>100000)Integral_bias=10000;
	 if(Integral_bias<-100000)Integral_bias=-10000;
	 Pwm=Position_KP*Bias+Position_KI/100*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}

/**************************************************************************
函数功能：每个电机位置控制过程速度计算
入口参数：无
返回  值：无
**************************************************************************/
void Count_Velocity(void)
{
	static double Last_Target_X,Last_Target_Y,Last_Target_Z,Divider;
	double Bias_X,Bias_Y,Bias_Z;
	Bias_X=(Move_X-Last_Target_X);  //求X轴位移量
	Bias_Y=(Move_Y-Last_Target_Y);	//求Y轴位移量
	Bias_Z=(Move_Z-Last_Target_Z);	//求Z轴位移量
	if(Bias_X!=0||Bias_Y!=0||Bias_Z!=0)Divider=sqrt(Bias_X*Bias_X+Bias_Y*Bias_Y+Bias_Z*Bias_Z);
	if(Bias_X!=0||Bias_Y!=0||Bias_Z!=0) Kinematic_Analysis2(Bias_X,Bias_Y,Bias_Z);

	Xianfu_Velocity(RC_Velocity*myabs(Rate_A)/Divider,RC_Velocity*myabs(Rate_B)/Divider,RC_Velocity*myabs(Rate_C)/Divider,RC_Velocity*myabs(Rate_D)/Divider); 
	Last_Target_X=Move_X;   //保存X轴上一次的位置信息，便于调用
	Last_Target_Y=Move_Y;   //保存Y轴上一次的位置信息，便于调用
	Last_Target_Z=Move_Z;   //保存Z轴上一次的位置信息，便于调用
}
