#include "Driver.h"

/*��ʼ���������GPIO*/
/*
PE12 PE13 PE14 PE15 
PE8 PE9 PE10 PE11
*/
void Driver_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE,&GPIO_InitStruct);	
}


/*ǰ��*/
void Forward(int speed)
{
	Final_X=speed;
	Final_Y=0;
}

/*����*/
void Back(int speed)
{
	Final_X=-speed;
	Final_Y=0;

}

/*����*/
void Left_Move(int speed)
{
	Final_X=0;
	Final_Y=speed;
}

/*����*/
void Right_Move(int speed)
{
	Final_X=0;
	Final_Y=-speed;

}

/*����*/
void Upper_Left(void)
{
	Final_X=4;
	Final_Y=4;

}

/*����*/
void Upper_Right(void)
{
	Final_X=4;
	Final_Y=-4;

}


/*ֹͣ*/
void stop(void)
{
	Final_X=0;
	Final_Y=0;
}


