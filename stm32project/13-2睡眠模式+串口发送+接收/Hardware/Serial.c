#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

void Serial_Init(void)
{
	// 时钟使能
	// 使能USART1和GPIOA的时钟(USART1挂在APB2总线上)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// TX引脚配置
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// RX引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// USART1参数配置
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	// 中断配置部分
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	// NVIC嵌套向量中断控制器配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				// 优先级分组2
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			// USART1中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				// 使能中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	// 抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			// 子优先级1
	NVIC_Init(&NVIC_InitStructure);
	
	
	USART_Cmd(USART1,ENABLE);									// 使能USART
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array,uint16_t length)
{
	uint16_t i;
	for (i = 0; i < length; i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result = 1;
	while(Y--)
	{
		Result *= X;
	}
	return Result;
}
 
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)
	{
		Serial_SendByte(Number / Serial_Pow(10,Length - i - 1) % 10 + '0');
	}
		
}

// printf函数重定向,调用printf函数重定向到串口
// fputc是printf的底层
// printf函数在打印的时候,就是不断嗲用fputc函数一个个打印的
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];				// 定义输出缓冲区
	va_list arg;					// 声明可变参数列表变量(定义用于访问可变参数的对象)
	va_start(arg,format);			// 初始化可变参数列表(初始化arg,使其指向format参数之后的第一个可变参数)
	vsprintf(String,format,arg);	// 将格式化字符串写入缓冲区
	va_end(arg);					// 清理可变参数列表(清理工作,确保函数正确返回)
	Serial_SendString(String);		// 通过串口发送字符串
}

// 标志位获取函数
uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;	// 清除标志位
		return 1;			// 返回1表示有数据接收
	}
	return 0;				// 返回0表示没有数据接收
}

// 数据获取函数
uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;	// 返回接收到的数据
}

// 中断服务函数
// 当USART1接收发哦数据时,自动触发此中断函数

// 中断处理
// 当串口接收到数据时,硬件自动触发USART_IQRHandler中断函数
// 中断函数读取接收到的数据,存储到全局变量,并设置接收标志位
// 中断处理完成后,主循环检测到标志位变化,进行相应处理
void USART1_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART1,USART_IT_RXNE) == SET)
	{
		Serial_RxData = USART_ReceiveData(USART1);      // 拂去接收到的数据
 		Serial_RxFlag = 1;								// 设置接收标志位
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	// 清除中断标志
	}
}
