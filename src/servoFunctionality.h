#ifndef SERVO_FUNCTIONALITY
#define SERVO_FUNCTIONALITY

#include "stm32l476xx.h"

void SERVO_Pin_Init();

void TIM5_CH1_Init();

void Servo_Move_Left_90_Degree();

void Servo_Move_Center();

void Servo_Move_Right_90_Degree();

#endif