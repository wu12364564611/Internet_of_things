#ifndef _TRACK_H
#define _TRACK_H
#include "headfile.h"
#define H1 PGin(1)
#define H2 PGin(2)
#define H3 PGin(3)
#define R5 PGin(4)
#define R4 PGin(5)
#define R3 PGin(6)
#define R2 PGin(7)
#define R1 PGin(8)

void Track_GPIO_init(void);
void Track_Function(void);


#endif


/**********************
			H1 H2 H3	
								R1
								R2
								R3
								R4
								R5
***********************/

