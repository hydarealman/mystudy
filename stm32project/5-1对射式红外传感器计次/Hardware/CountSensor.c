#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	// 启动时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructures;
	GPIO_InitStructures.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructures.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructures.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructures);
	
	// 配置EXTI外部中断
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	EXTI_InitTypeDef EXTI_InitStructures;
	
	EXTI_InitStructures.EXTI_Line = EXTI_Line14;
	EXTI_InitStructures.EXTI_LineCmd = ENABLE;
	EXTI_InitStructures.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructures.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&EXTI_InitStructures);
	
	// 配置NVIC外设
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitTypeDef NVIC_InitStructures;
	NVIC_InitStructures.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructures.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructures.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructures.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructures); 
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}

// 中断函数(无参无返回值)
// 中断函数不需要声明,因为中断函数不需要调用,它是自动执行的
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		CountSensor_Count++;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}


