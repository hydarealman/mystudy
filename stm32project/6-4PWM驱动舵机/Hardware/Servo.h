#ifndef __SERVO_H
#define __SERVO_H

void Servo1_Init(void);       // 舵机1初始化（原舵机）
void Servo1_SetAngle(float Angle);

void Servo2_Init(void);       // 舵机2初始化（PA2引脚）
void Servo2_SetAngle(float Angle);

#endif
