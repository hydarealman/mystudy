#include "stm32f10x.h"
#include "Delay.h"

int main(void)
{
    // 初始化GPIOA时钟和引脚
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 初始状态：所有LED熄灭
    GPIO_Write(GPIOA, 0xFFFF);
    
    while(1)
    {
        // 使用for循环控制LED流水灯效果
        for(int i = 0; i < 8; i++)
        {
            // 设置当前引脚为低电平（点亮LED）
            GPIO_Write(GPIOA, ~(1 << i));
            Delay_ms(500);
            
            // 额外效果：流水灯尾部淡出
            if(i > 0) 
            {
                GPIO_Write(GPIOA, ~((1 << i) | (1 << (i-1))));
                Delay_ms(100);
            }
        }
    }
}