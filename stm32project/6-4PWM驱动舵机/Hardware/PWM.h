#ifndef __PWM_H
#define __PWM_H


void PWM_Init(void);
void PWM_SetCompare2(uint16_t Compare);
void PWM_Init_TIM3_CH2(void);
void PWM_Init_TIM2_CH3(void);
void PWM_SetCompare3_TIM2(uint16_t Compare);
void PWM_SetCompare2_TIM3(uint16_t Compare); 

#endif
