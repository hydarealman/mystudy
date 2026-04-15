#include "stm32f10x.h"                  // Device header

void MySPI_W_SS(uint8_t BitValue) {
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
	
}

void MySPI_Init(void) {
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SPI_InitTypeDef SPI_InitStructures;
	SPI_InitStructures.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStructures.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructures.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructures.SPI_CRCPolynomial = 7;
	SPI_InitStructures.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructures.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructures.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructures.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructures.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1,&SPI_InitStructures);
	
	SPI_Cmd(SPI1,ENABLE);
	
	MySPI_W_SS(1);
}

void MySPI_Start(void) {
	MySPI_W_SS(0);
}

void MySPI_Stop(void) {
	MySPI_W_SS(1);
}

uint8_t MYSPI_SwapByte(uint8_t ByteSend) {
	// 等待发送缓冲区为空
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) != SET); 
	// 写入发送数据
	SPI_I2S_SendData(SPI1,ByteSend);
	// 等待接收完成
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) != SET); 
	// 读取接收数据
	return SPI_I2S_ReceiveData(SPI1);
}

