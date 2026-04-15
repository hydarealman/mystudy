#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

/*
设计思路
//
1. 多通道ADC扫描模式:同时采集4个模拟输入通道的数据
2. DMA高效传输: ADC转换后自动将数据搬运到内存,减少CPU负担
3. 单次采集触发:每次调用AD_GetValue启动一次四通道转换
4. 实时显示:主循环中定期获取并刷新OLED显示
*/


int main(void)
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1,1,"AD0:");
	OLED_ShowString(2,1,"AD1:");
	OLED_ShowString(3,1,"AD2:");
	OLED_ShowString(4,1,"AD3:");
	
	while(1) 
	{
	
		AD_GetValue();
		
		OLED_ShowNum(1,5,AD_Value[0],4);
		OLED_ShowNum(2,5,AD_Value[1],4);
		OLED_ShowNum(3,5,AD_Value[2],4);
		OLED_ShowNum(4,5,AD_Value[3],4);

		
		Delay_ms(100);	// 延时0.1秒让它刷新的慢一些
	}	
}

