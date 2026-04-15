#include "stm32f10x.h"//stm32标准外设库核心头文件

// 简单的毫秒延时函数（精度一般）
void Delay_ms(uint32_t ms) {
    for(uint32_t i = 0; i < ms * 5000; i++) {
        __NOP(); // 空操作指令（不会被编译器优化掉）
    }
}


int main(void)
{
	//时钟使能寄存器
	//启动GPIOC的时钟,stm32中任何外设使用前必须开启时钟
	//RCC->APB2ENR = 0x00000010;
	//端口配置寄存器 
	//配置PC13引脚的工作模式
	//GPIOC->CRH = 0X00300000;
	//输出数据寄存器
	//配置PC13引脚的输出电平
	//GPIOC->ODR = 0x00002000;
	
	//启用使能GPIOC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//配置GPIOC引脚
	GPIO_InitTypeDef GPIO_InitStructure;//定义配置结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//操作13引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//输出速度50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);//应用配置
	//设置初始电平
	GPIO_SetBits(GPIOC,GPIO_Pin_13);//高电平(灯灭)
	//GPIO_ResetBits(GPIOC,GPIO_Pin_13);//低电平(灯亮)
	while(1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13); // 亮
		Delay_ms(500);                     // 延时500ms
		GPIO_SetBits(GPIOC, GPIO_Pin_13);   // 灭
		//Delay_ms(500);
	}
}
