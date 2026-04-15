#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

/*
按键未按下时通过上拉电阻连接Vcc,读取电平高电平
按键按下时按键接通GND(地线),形成到地的低阻抗路径,读取到的低电平
*/

/*
一个典型的按键扫描函数,用于检测两个独立按键的按压事件，采用消抖处理并返回按键编号
*/
uint8_t Key_GetNum(void)
{
	//按键1优先级高于按键2
	//若同事按下两键,只会识别到按键1(因其判断顺序在前)
	uint8_t KeyNum = 0;//初始化按键值为0表示无按键
	//由于按键刚按下会有一点抖动,需要Delay一段时间
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)//检测到PB1是否为低电平 
	{
		Delay_ms(20);//延时20ms消除抖动
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)//持续检测按键是否释放 
		{
			Delay_ms(20);//保持消除抖动,防止抖动干扰
		}
		KeyNum = 1;//确认按键1按下
	}
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0) 
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0) 
		{
			Delay_ms(20);
		}
		KeyNum = 2;
	}
	
	return KeyNum;
}
