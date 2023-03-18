#include "rtcFunctionality.h"
#include "servoFunctionality.h"
#include <stdio.h>

extern volatile int isTimeoutComplete = 0;

void RTC_Set_Alarm(int alarmSecondsTime) {
	
	uint32_t secondTens = alarmSecondsTime / 10;
	uint32_t secondUnits = alarmSecondsTime % 10;
	
	RTC_Disable_Write_Protection();
	
	RTC->CR &= ~RTC_CR_ALRAE;
	RTC->CR &= ~RTC_CR_ALRAIE;
	
	while(((RTC->ISR & RTC_ISR_ALRAWF) == 0));
	
	RTC->ALRMAR &= ~RTC_ALRMAR_ST;
	RTC->ALRMAR &= ~RTC_ALRMAR_SU;
	RTC->ALRMAR |= (secondTens << 4) | (secondUnits);
	RTC->ALRMAR |= RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2;
	
	RTC_Enable_Write_Protection();

}

void RTC_Alarm_Enable(void) {
	EXTI->RTSR1 |= EXTI_RTSR1_RT18;
	EXTI->IMR1 |= EXTI_IMR1_IM18;
	EXTI->EMR1 |= EXTI_EMR1_EM18;
	EXTI->PR1 |= EXTI_PR1_PIF18;
	NVIC_EnableIRQ(RTC_Alarm_IRQn);
	NVIC_SetPriority(RTC_Alarm_IRQn, 0);
}

void RTC_Alarm_IRQHandler(void) {
	EXTI->PR1 |= EXTI_PR1_PIF18;
	
	isTimeoutComplete = 1;
	
	RTC->ISR &= ~RTC_ISR_ALRAF;
	Servo_Move_Right_90_Degree();
}

void DisableAlarmA() {
	RTC_Disable_Write_Protection();
	
	RTC->CR &= ~RTC_CR_ALRAE;
	RTC->CR &= ~RTC_CR_ALRAIE;
	
	RTC_Enable_Write_Protection();
}

void EnableAlarmA() {
	RTC_Disable_Write_Protection();
	
	RTC->CR |= RTC_CR_ALRAE;
	RTC->CR |= RTC_CR_ALRAIE;
	
	RTC_Enable_Write_Protection();
}
