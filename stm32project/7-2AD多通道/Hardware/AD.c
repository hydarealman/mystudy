#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	// 开启外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);	// 开启ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);// 开启GPIOA时钟

	// 配置ADC时钟分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	// 配置GPIO引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// 模拟输入模式(禁用数字功能)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;			// 时钟PA0引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 速度配置(对模拟输入无效,但需配置)
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	// 配置ADC工作模式
	ADC_InitTypeDef ADC_InitStructure;				
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						// 独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;							// 禁用扫描模式(单通道)
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;						// 单次转换模式(非连续)
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		// 软件触发(无外部触发)
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					// 数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;									// 转换通道数(1个)
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);	// 使能ADC 
	
	// 校准ADC
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);	// 等待复位校准完成
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);		// 等待校准完成
	
}

// ADC数值读取函数
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	// 配置ADC通道参数
	/*
	ADC_Channel_0 通道0
	1 -> 规则组转换序列中的位置
	ADC_SampleTime_55Cycles -> 采样时间55.5周期
	*/
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);					// 软件触发转换
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);	// 等待转换完成
	return ADC_GetConversionValue(ADC1);					// 读取转换结果
}


