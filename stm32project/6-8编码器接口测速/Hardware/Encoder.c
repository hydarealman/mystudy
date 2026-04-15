#include "stm32f10x.h"                  // Device header

//#include "Encoder.h"

void Encoder_Init(void)
{
	// 启动定时器
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	// 配置GPIO口	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//因为编码器接口会托管时钟,编码器接口就是一个带方向控制的外部时钟
	//TIM_InternalClockConfig(TIM3);
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructure;
	Tim_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 时钟分频设置
	Tim_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 计数模式
	Tim_TimeBaseInitStructure.TIM_Period = 65536 - 1;					// 自动重载值
	Tim_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;					// 预分频系数
	Tim_TimeBaseInitStructure.TIM_RepetitionCounter = 0;				// 重复计数器
	TIM_TimeBaseInit(TIM3,&Tim_TimeBaseInitStructure);		

	//IC输入捕获
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	//TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	// 高低电平极性不反转
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	//TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	// 配置编码器接口
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12, TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	TIM_Cmd(TIM3,ENABLE);
}

int16_t Encoder_Get(void)
{
	// 借用补码的特性快速完成负数转换
	/*
	在二进制补码表示法中:
	当数值 < 32768时,其二进制表示与无符号数完全相同
	当数值 >= 32768时,硬件自动将其解释为负数(最高位为符号位) 
	不需要if判断或公式转换 负数CPU的算术指令天然支持补码,后续计算能正确处理负数
	*/
	
	
	int16_t Temp;
	Temp = TIM_GetCounter(TIM3);	// 步骤1: 读取TIM3计数器的值
	TIM_SetCounter(TIM3,0);			// 步骤2: 将TIM3计数器重置为0
	return Temp;	// 步骤3: 再次读取TIM3
}

