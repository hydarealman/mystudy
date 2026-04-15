#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];					// 全局ADC存储数组 


//DMA转运的3个条件
//1.传输计数器大于0
//2.触发源有触发信号
//3.DMA使能
void AD_Init(void)
{
	// 开启外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);	// 开启ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);// 开启GPIOA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	// 配置ADC时钟分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	// 配置GPIO引脚(将四个GPIO配置未纯模拟输入模式(无上拉/下拉))
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// 模拟输入模式(禁用数字功能)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;			// 时钟PA0引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 速度配置(对模拟输入无效,但需配置)
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// 多通道扫描配置
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	
	
	// 配置ADC工作模式
	ADC_InitTypeDef ADC_InitStructure;				
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						// 独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;							// 禁用扫描模式(单通道)
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;						// 单次转换模式(非连续)
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		// 软件触发(无外部触发)
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					// 数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 4;									// 转换通道数(1个)
	ADC_Init(ADC1,&ADC_InitStructure);
	
	
	// DMA核心配置
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_BufferSize = 4;										// 设置传输缓冲区大小
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;							// 设置数据传输方向
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								// 禁用内存到内存传输模式
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;					// 设置内存基地址
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;		// 设置内存数据宽度
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 					// 启用内存地址递增
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;								// 设置DMA传输模式
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;				// 设置外设基地址 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// 设置外设读取的数据单位大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			// 禁用外设地址递增
	DMA_InitStructure.DMA_Priority =  DMA_Priority_Medium;                      // 设置DMA通道优先级           
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	// 开启ADC到DMA的输出
	ADC_DMACmd(ADC1,ENABLE);
	
	ADC_Cmd(ADC1,ENABLE);	// 使能ADC 
	
	
	// 校准ADC
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);	// 等待复位校准完成
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);		// 等待校准完成
	
}

// ADC数值读取函数
void AD_GetValue(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);						// 暂停DMA
	DMA_SetCurrDataCounter(DMA1_Channel1,4);			// 重设传输计数器
	DMA_Cmd(DMA1_Channel1,ENABLE);						// 启用DMA
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);				// 启动ADC转换
				
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);	// 等待传输完成
	DMA_ClearFlag(DMA1_FLAG_TC1);						// 清除标志位
}


