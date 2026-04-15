#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

char Serial_RxPacket[100];
char Serial_RxFlag;			

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;												// 定义初始化结构体
	USART_InitStructure.USART_BaudRate = 9600;											// 波特率设为9600 bps
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		// 禁用硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;						// 同时使能发送(Tx)和接收(Rx)模式
	USART_InitStructure.USART_Parity = USART_Parity_No;									// 无奇偶校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;								// 1位停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;							// 数据位长度8位
	USART_Init(USART1,&USART_InitStructure);											// 应用配置到USART1
	
	
	// USAT1中断启用和NVIC中断控制器配置
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);										// 启用USART1的特定中断类型								// 使能USTRA1的接收中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);										// 设置中断优先级分组
	
	// 配置NVIC中断通道
	NVIC_InitTypeDef NVIC_InitStructure;				
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		   // 中断通道:USART1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			   // 使能该中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  // 抢占优先级=1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		   // 响应优先级=1
	NVIC_Init(&NVIC_InitStructure);							   // 应用配置
	
	
	USART_Cmd(USART1,ENABLE);								   // 使能USART外设 
}

// 阻塞之串口单字节发送函数(调用后等待发送完成才返回)
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





// 中断服务函数
// 当USART1接收发数据时,自动触发此中断函数

// 中断处理
// 当串口接收到数据时,硬件自动触发USART_IQRHandler中断函数
// 中断函数读取接收到的数据,存储到全局变量,并设置接收标志位
// 中断处理完成后,主循环检测到标志位变化,进行相应处理

// 中断触发机制
// 每次USART1接收到一个字节的数据时,硬件会自动触发USART1_IRQHandler中断函数
// 因此,每收到一个新字节,中断函数就被调用一次,每次处理一个字节
// 但依靠stativ变量,状态机记住了上一次中断后的状态和进度

// 中断是异步执行的
// 主函数正常执行时,当串口接收到数据,硬件会自动打断主函数的执行
// CPU立即暂停当前工作,转而执行这个中断服务函数
// 中断函数执行完成后,CPU恢复主函数从被打断的位置继续执行
void USART1_IRQHandler(void)
{
	static uint8_t RxState = 0;			// 状态机的当前状态
	static uint8_t pRxPacket = 0;		// 数据包存储位置索引
	if (USART_GetFlagStatus(USART1,USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if (RxState == 0)
		{
								 // 防止数据错位(加锁)
			if (RxData == '@' && Serial_RxFlag == 0)
			{
				RxState = 1;
				pRxPacket = 0;
			}
		}
		else if (RxState == 1)
		{
			if (RxData == '\r')
			{
				RxState = 2;
			}
			else
			{
				Serial_RxPacket[pRxPacket] = RxData;
				pRxPacket++;
			}
		}
		else if (RxState == 2)
		{
			if (RxData == '\n')
			{
				RxState = 0;
				Serial_RxPacket[pRxPacket] = '\0';
				Serial_RxFlag = 1;
			}
		}
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	// 清除中断标志
	}
}
 

