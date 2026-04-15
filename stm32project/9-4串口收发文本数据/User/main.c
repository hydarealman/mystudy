#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"
#include "LED.h"
#include "string.h"

int main(void)
{
	OLED_Init();
	Key_Init();
	LED_Init();
	Serial_Init(); 
	
	OLED_ShowString(1,1,"TxPacket");
	OLED_ShowString(3,1,"RxPacket");
	
	// 输入输出存在竞态条件
	// 因为数据包读取的非原子性,标志位的原子性
	
	// 例如当主函数检测到 Serial_RxFlag被置为,然后开始读取Serial_RxPacket数组时
	// 如果此时发生串口中断,并且中断函数修改了 Serial_RxPacket,那么主函数可能会读取到部分旧数据和部分新数据,导致数据不一致
	// 又或者,在中断服务程序中,当接收到完整的数据包,即接收结束符\n时会设置Serial_RxFlag = 1，主函数在检查并
	// 清除该标志时,如果在检查标志和清除标志之间发生了中断,中断可能再次设置该标志,导致主函数只处理一次数据包,
	// 但中断函数却认为主函数已经处理完毕，而覆盖数据包
	
	// 如果是传输各种传感器的每个独立数据,比如陀螺仪的X,Y,Z轴数据，温湿度数据等等
	// 相邻数据包之间的数据,具有连续性,这样即使相邻数据包混在一起了,也没关系
	while(1)
	{
		if (Serial_RxFlag == 1)
		{
			OLED_ShowString(4,1,"                "); // 相当于擦除第四行了
			OLED_ShowString(4,1,Serial_RxPacket);
			
			if (strcmp(Serial_RxPacket,"LED_ON") == 0)
			{
				LED1_ON();
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(2,1,"                 ");
				OLED_ShowString(2,1,"LED_ON_OK");
			}
			else if (strcmp(Serial_RxPacket,"LED_OFF") == 0)
			{
				LED1_OFF();
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(2,1,"                 ");
				OLED_ShowString(2,1,"LED_OFF_OK");
			}
			else
			{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString(2,1,"                 ");
				OLED_ShowString(2,1,"ERROR_COMMAND");
			}
			
			Serial_RxFlag = 0;
		}
	}
}



