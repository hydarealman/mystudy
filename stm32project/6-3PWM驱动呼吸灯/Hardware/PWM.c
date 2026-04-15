#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	// 使能TIM2时钟(相当于接通电源)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	// 使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// 打开AFIO时钟,重映射引脚，接触调试端口 
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	
	// 配置GPIO引脚
	GPIO_InitTypeDef GPIO_InitStructures;
	GPIO_InitStructures.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
	GPIO_InitStructures.GPIO_Pin = GPIO_Pin_0;			// 选择pa0引脚
	GPIO_InitStructures.GPIO_Speed = GPIO_Speed_50MHz;	// 输出速度50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructures);				// 初始化GPIOA
	 
	TIM_InternalClockConfig(TIM2);						// 选择定时器时钟源(选职责内部时钟源)
	
	// 配置时基单元 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructures;				
	TIM_TimeBaseInitStructures.TIM_ClockDivision = TIM_CKD_DIV1;		 // 时钟不分频 
	TIM_TimeBaseInitStructures.TIM_CounterMode = TIM_CounterMode_Up;	 // 向上计数模式
	TIM_TimeBaseInitStructures.TIM_Period = 100 - 1;					 // 自动重装载值
	TIM_TimeBaseInitStructures.TIM_Prescaler = 720 - 1;					 // 预分频系数
	TIM_TimeBaseInitStructures.TIM_RepetitionCounter = 0;				 // 重复计数器(高级定时器用)
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructures);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);				// 清除更新中断标志
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);			// 使能更新中断
	
	TIM_OCInitTypeDef TIM_OCInitStructures;
	TIM_OCStructInit(&TIM_OCInitStructures);
	TIM_OCInitStructures.TIM_OCMode = TIM_OCMode_PWM1;			// 设置输出比较的模式(PWM模式1)
	TIM_OCInitStructures.TIM_OCPolarity = TIM_OCPolarity_High;     // 设置输出比较的极性(高电平有效)
	TIM_OCInitStructures.TIM_OutputState = TIM_OutputState_Enable;	// 设置输出使能(使能输出)
	TIM_OCInitStructures.TIM_Pulse = 0;			// 设置CCR(初始化占空比0%)
	TIM_OC1Init(TIM2,&TIM_OCInitStructures);	// 初始化通道1
	 
	TIM_Cmd(TIM2,ENABLE); // 使能TIM2(相当于按下开关)
}

// PWM设置函数
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare); // 设置通道1的比较值
}
