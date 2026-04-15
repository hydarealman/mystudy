#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"

int main(void)
{
    // 初始化外设
    OLED_Init();
    Servo1_Init();  // 初始化舵机1（原舵机）
    Servo2_Init();  // 初始化舵机2（PA2引脚）
    
    OLED_ShowString(1, 1, "Servo1:");
    OLED_ShowString(2, 1, "Servo2:");
    OLED_ShowString(3, 1, "Speed: 150ms");
    
    // 提高舵机速度的参数
    const uint8_t step = 10;       // 角度步长增加到10度
    const uint16_t delay = 20;     // 每次延时减少到20ms
    uint8_t direction = 1;        // 旋转方向：1=正向，0=反向
    uint8_t angle = 0;             // 当前角度
    
    while(1)
    {
        // 根据方向设置角度
        if(direction) {
            angle += step;
            if(angle >= 180) {
                angle = 180;
                direction = 0;  // 反转方向
            }
        } else {
            angle -= step;
            if(angle <= 0) {
                angle = 0;
                direction = 1;  // 反转方向
            }
        }
        
        // 设置两个舵机的角度
        Servo1_SetAngle(angle);
        Servo2_SetAngle(angle);
        
        // OLED显示当前角度
        OLED_ShowNum(1, 8, angle, 3);
        OLED_ShowNum(2, 8, angle, 3);
        
        Delay_ms(delay);  // 较短的延时提高速度
    }
}
