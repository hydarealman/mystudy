#include "stm32f10x.h"                  // Device header

void IC_Init(void)
{
	// 使能TIM2时钟(相当于接通电源)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	// 使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	// 配置GPIO引脚
	GPIO_InitTypeDef GPIO_InitStructures;
	GPIO_InitStructures.GPIO_Mode = GPIO_Mode_IPU;	// 复用推挽输出
	GPIO_InitStructures.GPIO_Pin = GPIO_Pin_6;			// 选择pa0引脚
	GPIO_InitStructures.GPIO_Speed = GPIO_Speed_50MHz;	// 输出速度50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructures);				// 初始化GPIOA
	 
	TIM_InternalClockConfig(TIM3);						// 选择定时器时钟源(选职责内部时钟源)
	
	// 配置时基单元 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructures;				
	TIM_TimeBaseInitStructures.TIM_ClockDivision = TIM_CKD_DIV1;		 // 时钟不分频 
	TIM_TimeBaseInitStructures.TIM_CounterMode = TIM_CounterMode_Up;	 // 向上计数模式
	TIM_TimeBaseInitStructures.TIM_Period = 65536 - 1;					 // 自动重装载值
	TIM_TimeBaseInitStructures.TIM_Prescaler = 72 - 1;					 // 预分频系数
	TIM_TimeBaseInitStructures.TIM_RepetitionCounter = 0;				 // 重复计数器(高级定时器用)
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructures);
	
	
	// 初始化输入捕获单元
	TIM_ICInitTypeDef TIM_ICInitStructures;
	TIM_ICInitStructures.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructures.TIM_ICFilter = 0xF;
	TIM_ICInitStructures.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructures.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructures.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructures);
	
	// TIM_ICInit(TIM3,&TIM_ICInitStructures);
	
	
	/*
	TIM_ICInitStructures.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructures.TIM_ICFilter = 0xF;
	TIM_ICInitStructures.TIM_ICPolarity = TIM_ICPolarity_Falling;
	TIM_ICInitStructures.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructures.TIM_ICSelection = TIM_ICSelection_IndirectTI;
	TIM_ICInit(TIM3,&TIM_ICInitStructures);
	*/
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);	   // 触发源
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset); // 配置从模式

	TIM_Cmd(TIM3,ENABLE);
	
}

uint32_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM3)) - 1;
}

uint32_t IC_GetDuty(void)
{
	return  (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1);
}



