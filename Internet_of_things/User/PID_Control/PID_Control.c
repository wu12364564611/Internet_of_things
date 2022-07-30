#include "PID_Control.h"
/*�����Ŀ���ٶ�*/
int Target_A,Target_B,Target_C,Target_D;
/*��������ٶ�*/
int Motor_A,Motor_B,Motor_C,Motor_D;      
/*��������ֵ*/
int Encoder_A,Encoder_B,Encoder_C,Encoder_D;
/*ƫ����*/
int yaw;
/*��������ٶ�*/
int Final_X=0,Final_Y=0,Final_Z=0;
/*�������*/
int Pulse_Count=0;
/*Ŀ��Ƕ�*/
int Target_Angle=0;


void TIM6_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM6,TIM_FLAG_Update)==SET)
	{
		/*�����ʱ��1�жϱ�־λ*/
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);

		/*�ֱ������Ʒ�������*/
		/*���㵱ǰƫ����*/
		yaw=(float)stcAngle.Angle[2]/32768*180;
		/*�ǶȻ�����*/
		Final_Z=Angle_Loop(yaw,Target_Angle);
		/*����޷�*/
		Final_Z=Limiting_amplitude(Final_Z,50);
		
		
		/*����ʸ���㷨*/		
		mlyd(Final_X,Final_Y,Final_Z,30); 
		
		/*���������������ֵ*/
		Encoder_A=Read_Encoder(2);
	  Encoder_B=-Read_Encoder(3);
	  Encoder_C=-Read_Encoder(4);
	  Encoder_D=Read_Encoder(5);
		
		/*�����ۼ�*/
		Pulse_Count=Pulse_Count+Encoder_A;
		
		
		/*�ٶȻ�PID���� ������������ֵ Ŀ���ٶ� Kp Ki*/
		Motor_A=Incremental_PI_A(Encoder_A,Target_A);                         //===�ٶȱջ����Ƽ�����A����PWM
		Motor_B=Incremental_PI_B(Encoder_B,Target_B);                         //===�ٶȱջ����Ƽ�����B����PWM
		Motor_C=Incremental_PI_C(Encoder_C,Target_C);                         //===�ٶȱջ����Ƽ�����C����PWM
		Motor_D=Incremental_PI_D(Encoder_D,Target_D);                         //===�ٶȱջ����Ƽ�����C����PWM
		/*����޷�*/
		Motor_A=Limiting_amplitude(Motor_A,490);
		Motor_B=Limiting_amplitude(Motor_B,490);
		Motor_C=Limiting_amplitude(Motor_C,490);
		Motor_D=Limiting_amplitude(Motor_D,490);
		
		Set_Pwm(Motor_A,Motor_B,Motor_C,Motor_D);
	} 
  
}
/**************************************************************************
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 /*Kp=20,Ki=1*/
   float Kp=30,Ki=1;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
	
}


int Incremental_PI_B (int Encoder,int Target)
{ 	
   float Kp=30,Ki=1;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}



int Incremental_PI_C (int Encoder,int Target)
{ 	
   float Kp=30,Ki=1;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}

int Incremental_PI_D (int Encoder,int Target)
{ 	
   float Kp=30,Ki=1;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ��
	 return Pwm;                         //�������
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



/*��ֵ��PWM�Ĵ���*/
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
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
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
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a) //ȡ����ֵ
{ 		   
	 int temp;
	 if(a<0)  temp=-a;  
	 else temp=a;
	 return temp;
}
