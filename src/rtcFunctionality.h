#ifndef RTC_FUNCTIONALITY
#define RTC_FUNCTIONALITY

#include "stm32l476xx.h"
#include "RTC.h"

void RTC_Set_Alarm(int alarmSecondsTime);

void RTC_Alarm_Enable(void);

void RTC_Alarm_IRQHandler(void);

void DisableAlarmA();

void EnableAlarmA();

extern volatile int isTimeoutComplete;

#endif