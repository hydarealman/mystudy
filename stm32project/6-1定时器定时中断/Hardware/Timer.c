#include "stm32f10x.h"                  // Device header

extern uint16_t Num;

void Timer_Init(void)
{
	// 使能TIM2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	// 选择内部时钟源
	TIM_InternalClockConfig(TIM2);
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructures;					
	TIM_TimeBaseInitStructures.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频(不分频)
	TIM_TimeBaseInitStructures.TIM_CounterMode = TIM_CounterMode_Up;	//计数模式(向上计数)
	TIM_TimeBaseInitStructures.TIM_Period = 10000 - 1;					//自动重装载值
	TIM_TimeBaseInitStructures.TIM_Prescaler = 7200 - 1;				//预分频值
	TIM_TimeBaseInitStructures.TIM_RepetitionCounter = 0;				//重复计数器
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructures);
	
	// 使能更新中断
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	// 配置NVIC中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructures;
	NVIC_InitStructures.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructures.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructures.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructures.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructures);
	
	// 启动定时器
	TIM_Cmd(TIM2,ENABLE);
}

// 中断函数
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

