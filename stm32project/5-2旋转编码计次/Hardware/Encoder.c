#include "stm32f10x.h"                  // Device header

int16_t Encoder_Count;

void Encoder_Init(void)
{
	// 启动时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructures;
	GPIO_InitStructures.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructures.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructures.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructures);
	
	// 配置EXTI外部中断
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

	EXTI_InitTypeDef EXTI_InitStructures;
	
	EXTI_InitStructures.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXTI_InitStructures.EXTI_LineCmd = ENABLE;
	EXTI_InitStructures.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructures.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&EXTI_InitStructures);
	
	// 配置NVIC外设
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitTypeDef NVIC_InitStructures;
	NVIC_InitStructures.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructures.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructures.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructures.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructures); 
	
	NVIC_InitStructures.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructures.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructures.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructures.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructures); 
}

int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp = Encoder_Count;
	Encoder_Count = 0;
	return Temp;
}


// 一些中肯的建议
// 1.中断函数里面最好不要执行耗时过长的代码,中断函数要简短快速,否则主程序会受到严重的阻塞
// 2.最好不要在中断函数和主函数调用相同的函数或者操作同一个硬件,否则硬件会显示错误
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
		{
			Encoder_Count--;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)
		{
			Encoder_Count++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
