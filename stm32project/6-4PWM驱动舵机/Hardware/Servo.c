#include "stm32f10x.h"
#include "PWM.h"

// 舵机1（原舵机，使用TIM3_CH2）
void Servo1_Init(void)
{
    PWM_Init_TIM3_CH2();  // 初始化TIM3通道2
}

void Servo1_SetAngle(float Angle)
{
    PWM_SetCompare2_TIM3(Angle / 180 * 2000 + 500);
}

// 舵机2（PA2引脚，使用TIM2_CH3）
void Servo2_Init(void)
{
    PWM_Init_TIM2_CH3();  // 初始化TIM2通道3
}

void Servo2_SetAngle(float Angle)
{
    PWM_SetCompare3_TIM2(Angle / 180 * 2000 + 500);
}