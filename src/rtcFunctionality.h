#ifndef RTC_FUNCTIONALITY
#define RTC_FUNCTIONALITY

#include "stm32l476xx.h"
#include "RTC.h"

void RTC_Set_Alarm(void);

void RTC_Alarm_Enable(void);

void RTC_Alarm_IRQHandler(void);

void DisableAlarmA_EnableAlarmB();

void DisableAlarmB_EnableAlarmA();

#endif