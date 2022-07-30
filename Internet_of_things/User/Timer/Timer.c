#include "Timer.h"

/*������ʱ����ʼ��*/

void TIM6_Timer_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;     //��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;  //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0; //ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);  //ʹ�ܶ�ʱ���ж�
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM6_IRQn;   //ʹ���ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;   //ʹ���ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;    //��Ӧ���ȼ�3
	NVIC_Init(&NVIC_InitStruct);

	TIM_Cmd(TIM6,ENABLE);	  //ʹ�ܶ�ʱ��3
}

void TIM7_Timer_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;     //��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;  //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0; //ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);  //ʹ�ܶ�ʱ���ж�
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;   //ʹ���ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;   //ʹ���ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;    //��Ӧ���ȼ�3
	NVIC_Init(&NVIC_InitStruct);

}

/*��ʱ���жϷ�����*/
void TIM7_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM7,TIM_FLAG_Update)==SET)
	{

	} 
  
}


