#ifndef _DRIVER_H
#define _DRIVER_H
#include "headfile.h"

#define AIN1   PEout(8)
#define AIN2   PEout(9)
#define BIN1   PEout(10)
#define BIN2   PEout(11)
#define CIN1   PEout(12)
#define CIN2   PEout(13)
#define DIN1   PEout(14)
#define DIN2   PEout(15)

void Driver_Init(void);
void Forward(int speed);
void Back(int speed);
void Left_Move(int speed);
void Right_Move(int speed);
void stop(void);
void Upper_Left(void);
void Upper_Right(void);





#endif


