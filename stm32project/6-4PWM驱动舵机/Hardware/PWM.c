#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	// 使能TIM2时钟(相当于接通电源)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	// 使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	// 配置GPIO引脚
	GPIO_InitTypeDef GPIO_InitStructures;
	GPIO_InitStructures.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
	GPIO_InitStructures.GPIO_Pin = GPIO_Pin_1;			// 选择pa0引脚
	GPIO_InitStructures.GPIO_Speed = GPIO_Speed_50MHz;	// 输出速度50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructures);				// 初始化GPIOA
	 
	TIM_InternalClockConfig(TIM2);						// 选择定时器时钟源(选职责内部时钟源)
	
	// 配置时基单元 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructures;				
	TIM_TimeBaseInitStructures.TIM_ClockDivision = TIM_CKD_DIV1;		 // 时钟不分频 
	TIM_TimeBaseInitStructures.TIM_CounterMode = TIM_CounterMode_Up;	 // 向上计数模式
	TIM_TimeBaseInitStructures.TIM_Period = 20000 - 1;					 // 自动重装载值
	TIM_TimeBaseInitStructures.TIM_Prescaler = 72 - 1;					 // 预分频系数
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
	TIM_OC1Init(TIM2,&TIM_OCInitStructures);	
	TIM_OC2Init(TIM2,&TIM_OCInitStructures);
	TIM_OC3Init(TIM2,&TIM_OCInitStructures);
	TIM_OC4Init(TIM2,&TIM_OCInitStructures);
	
	TIM_Cmd(TIM2,ENABLE); // 使能TIM2(相当于按下开关)
}

// TIM3通道2初始化 (PA7)
void PWM_Init_TIM3_CH2(void)
{
    // 使能TIM3时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
    // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // 配置GPIO引脚 PA7
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 时基单元初始化
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;     // 20ms周期
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;     // 72MHz -> 1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    
    // 仅初始化通道2
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 1500;  // 默认1.5ms居中位置
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  // 仅初始化OC2
    
    // 使能TIM3
    TIM_Cmd(TIM3, ENABLE);
}

// TIM2通道3初始化 (PA2)
void PWM_Init_TIM2_CH3(void)
{
    // 使能TIM2时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // 配置GPIO引脚 PA2
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 时基单元初始化
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;     // 20ms周期
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;     // 72MHz -> 1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
    // 仅初始化通道3
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 1500;  // 默认1.5ms居中位置
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);  // 仅初始化OC3
    
    // 使能TIM2
    TIM_Cmd(TIM2, ENABLE);
}

// 为两个通道分别添加设置函数
void PWM_SetCompare2_TIM3(uint16_t Compare)
{
    TIM3->CCR2 = Compare;
}

void PWM_SetCompare3_TIM2(uint16_t Compare)
{
    TIM2->CCR3 = Compare;
}
