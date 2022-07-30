#include "Timer.h"

/*基本定时器初始化*/

void TIM6_Timer_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;     //重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;  //预分频系数
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0; //时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);  //使能定时器中断
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM6_IRQn;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;    //响应优先级3
	NVIC_Init(&NVIC_InitStruct);

	TIM_Cmd(TIM6,ENABLE);	  //使能定时器3
}

void TIM7_Timer_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;     //重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;  //预分频系数
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0; //时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);  //使能定时器中断
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;    //响应优先级3
	NVIC_Init(&NVIC_InitStruct);

}

/*定时器中断服务函数*/
void TIM7_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM7,TIM_FLAG_Update)==SET)
	{

	} 
  
}


