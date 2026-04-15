#include "stm32f10x.h"  
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t KeyNum;

//优先使用自己的局部变量,如果没有才会使用外部的局部变量
int main(void)
{
	
	LED_Init();
	Key_Init();
	
//	while(1)
//	{
//		KeyNum = Key_GetNum();
//		if (KeyNum == 1)
//		{
//			LED1_ON();
//		}
//		if (KeyNum)
//		{
//			LED1_OFF();
//		}
//	}
	
	while(1) 
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1) 
		{
			LED1_Turn();
		}
		if (KeyNum)
		{
			LED2_Turn();
		}
	}
	
}
