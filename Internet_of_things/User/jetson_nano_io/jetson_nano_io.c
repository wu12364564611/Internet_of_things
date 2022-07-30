#include "jetson_nano_io.h"

/*初始化与jetson nano通讯的io口*/
void Jetson_nano_io_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	/*设置pd9为输出(黑)*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD,&GPIO_InitStruct);	
	/*设置pd10为输入(白)*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	
	/*pd9输出初始化低电平*/
	GPIO_WriteBit(GPIOD,GPIO_Pin_8,Bit_RESET);
}
