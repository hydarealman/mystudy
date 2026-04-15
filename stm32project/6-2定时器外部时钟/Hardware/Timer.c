#include "stm32f10x.h"                  // Device header

extern uint16_t Num;

void Timer_Init(void)
{
	// 使能TIM2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructures;
	GPIO_InitStructures.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructures.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructures.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructures);
	
	// 选择时钟源
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x00);
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructures;					
	TIM_TimeBaseInitStructures.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频(不分频)
	TIM_TimeBaseInitStructures.TIM_CounterMode = TIM_CounterMode_Up;	//计数模式(向上计数)
	TIM_TimeBaseInitStructures.TIM_Period = 10 - 1;					//自动重装载值
	TIM_TimeBaseInitStructures.TIM_Prescaler = 1 - 1;				//预分频值
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

uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
}

// 中断函数
/*
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
*/

