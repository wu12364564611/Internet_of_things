#include "Track.h"
int R_FALG[5]={0,0,0,0,0};

/*Ñ­¼£´úÂë*/
void Track_GPIO_init(void)
{
	/*PG1 2 3 4 5 6 7 8*/
	GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG,&GPIO_InitStruct);	
	
}

/*ºÚÉ«£º1
	°×É«£º0
*/
void Track_Function(void)
{
	
	
	
}

