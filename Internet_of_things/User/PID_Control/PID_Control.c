#include "PID_Control.h"
/*电机的目标速度*/
int Target_A,Target_B,Target_C,Target_D;
/*电机最终速度*/
int Motor_A,Motor_B,Motor_C,Motor_D;      
/*编码器的值*/
int Encoder_A,Encoder_B,Encoder_C,Encoder_D;
/*偏航角*/
int yaw;
/*三个轴的速度*/
int Final_X=0,Final_Y=0,Final_Z=0;
/*脉冲计数*/
int Pulse_Count=0;
/*目标角度*/
int Target_Angle=0;


void TIM6_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM6,TIM_FLAG_Update)==SET)
	{
		/*清除定时器1中断标志位*/
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);

		/*手柄不控制方向则开启*/
		/*计算当前偏航角*/
		yaw=(float)stcAngle.Angle[2]/32768*180;
		/*角度环运算*/
		Final_Z=Angle_Loop(yaw,Target_Angle);
		/*输出限幅*/
		Final_Z=Limiting_amplitude(Final_Z,50);
		
		
		/*麦轮矢量算法*/		
		mlyd(Final_X,Final_Y,Final_Z,30); 
		
		/*捕获各个编码器得值*/
		Encoder_A=Read_Encoder(2);
	  Encoder_B=-Read_Encoder(3);
	  Encoder_C=-Read_Encoder(4);
	  Encoder_D=Read_Encoder(5);
		
		/*脉冲累计*/
		Pulse_Count=Pulse_Count+Encoder_A;
		
		
		/*速度环PID运算 参数：编码器值 目标速度 Kp Ki*/
		Motor_A=Incremental_PI_A(Encoder_A,Target_A);                         //===速度闭环控制计算电机A最终PWM
		Motor_B=Incremental_PI_B(Encoder_B,Target_B);                         //===速度闭环控制计算电机B最终PWM
		Motor_C=Incremental_PI_C(Encoder_C,Target_C);                         //===速度闭环控制计算电机C最终PWM
		Motor_D=Incremental_PI_D(Encoder_D,Target_D);                         //===速度闭环控制计算电机C最终PWM
		/*输出限幅*/
		Motor_A=Limiting_amplitude(Motor_A,490);
		Motor_B=Limiting_amplitude(Motor_B,490);
		Motor_C=Limiting_amplitude(Motor_C,490);
		Motor_D=Limiting_amplitude(Motor_D,490);
		
		Set_Pwm(Motor_A,Motor_B,Motor_C,Motor_D);
	} 
  
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
	 /*Kp=20,Ki=1*/
   float Kp=30,Ki=1;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
	
}


int Incremental_PI_B (int Encoder,int Target)
{ 	
   float Kp=30,Ki=1;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}



int Incremental_PI_C (int Encoder,int Target)
{ 	
   float Kp=30,Ki=1;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}

int Incremental_PI_D (int Encoder,int Target)
{ 	
   float Kp=30,Ki=1;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差
	 return Pwm;                         //增量输出
}




int Angle_Loop(int Re_Angle, int Ta_Angle)
{
	float Kp=0.8,Ki=2;	
	static float aBias, aPWM_out, aLast_bias;
	aBias = Ta_Angle-Re_Angle;	
	aPWM_out = Kp*(aBias- aLast_bias)+Ki*aBias;
	aLast_bias = aBias;			
	return aPWM_out;			
}



/*赋值给PWM寄存器*/
void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d)
{
	int PWMA,PWMB,PWMC,PWMD;
  if(motor_a>0) 	AIN1=0,   AIN2=1;			
	else 						AIN1=1,   AIN2=0;             
	PWMA=myabs(motor_a);
	TIM_SetCompare1(TIM1,PWMA);
   
	if(motor_b>0)    BIN1=0,   BIN2=1;
	else             BIN1=1,   BIN2=0;
	PWMB=myabs(motor_b);
	TIM_SetCompare2(TIM1,PWMB);
   
	if(motor_c>0)    CIN1=0,   CIN2=1;
	else             CIN1=1,   CIN2=0;
	PWMC=myabs(motor_c);
	TIM_SetCompare3(TIM1,PWMC);
   
	if(motor_d>0)    DIN1=0,   DIN2=1;
	else             DIN1=1,   DIN2=0;
	PWMD=myabs(motor_d);
	TIM_SetCompare4(TIM1,PWMD);
}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
int Limiting_amplitude(int value,int Amplitude)
{	
	int temp;
	if(value>Amplitude) temp = Amplitude;
	else if(value<-Amplitude) temp = -Amplitude;
	else temp = value;
	return temp;
}

/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a) //取绝对值
{ 		   
	 int temp;
	 if(a<0)  temp=-a;  
	 else temp=a;
	 return temp;
}
