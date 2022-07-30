#ifndef _PID_CONTROL_H
#define _PID_CONTROL_H
#include "headfile.h"


extern int Target_A,Target_B,Target_C,Target_D;
extern int Encoder_A,Encoder_B,Encoder_C,Encoder_D;
extern int Final_X,Final_Y,Final_Z;
extern int Pulse_Count;



int Incremental_PI_A (int Encoder,int Target);
int Incremental_PI_B (int Encoder,int Target);
int Incremental_PI_C (int Encoder,int Target);
int Incremental_PI_D (int Encoder,int Target);

int Limiting_amplitude(int value,int Amplitude);
void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d);
int myabs(int a);
int Angle_Loop(int Re_Angle, int Ta_Angle);



#endif


