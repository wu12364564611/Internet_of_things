#include "jetson_nano_io.h"

/*��ʼ����jetson nanoͨѶ��io��*/
void Jetson_nano_io_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	/*����pd9Ϊ���(��)*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD,&GPIO_InitStruct);	
	/*����pd10Ϊ����(��)*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	
	/*pd9�����ʼ���͵�ƽ*/
	GPIO_WriteBit(GPIOD,GPIO_Pin_8,Bit_RESET);
}
