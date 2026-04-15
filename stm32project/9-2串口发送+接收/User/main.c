#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(void)
{
	OLED_Init();
	OLED_ShowString(1,1,"RxData");
	
	Serial_Init();
	
	
	Serial_Printf("Num=%d\r\n",666);
	
	
//	while(1) 
//	{
//		// 1.查询方法
//		if (USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)
//		{
//			RxData = USART_ReceiveData(USART1);
//			OLED_ShowHexNum(1,1,RxData,2);
//		}
//	}	
	
	// 持续检查是否有串口数据到达
	// 如果收到数据(标志位为1),则:
	//a.读取接收到的数据
	//b.将数据原样发送会串口i
	//c.在OLEDP屏幕上以十六进制形式显示接收到的数据
	while(1)
	{
		if (Serial_GetRxFlag() == 1)
		{
			RxData = Serial_GetRxData();
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1,8,RxData,2);
		}
	}
}

