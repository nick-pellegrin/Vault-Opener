#include "rtcFunctionality.h"

void RTC_Set_Alarm(void) {
	RTC_Disable_Write_Protection();
	
	RTC->CR &= ~RTC_CR_ALRAE;
	RTC->CR &= ~RTC_CR_ALRBE;
	RTC->CR &= ~RTC_CR_ALRAIE;
	RTC->CR &= ~RTC_CR_ALRBIE;
	
	while(((RTC->ISR & RTC_ISR_ALRAWF) == 0) && (((RTC->ISR & RTC_ISR_ALRBWF) >> 1) == 0));
	
	RTC->ALRMAR |= (0x3 << 4);
	RTC->ALRMAR |= RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2;
	RTC->ALRMBR |= RTC_ALRMBR_MSK4 | RTC_ALRMBR_MSK3 | RTC_ALRMBR_MSK2 | RTC_ALRMBR_MSK1;
	
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
	RTC->ISR &= ~RTC_ISR_ALRAF;
	RTC->ISR &= ~RTC_ISR_ALRBF;
	
	//Green_LED_Toggle();
	
}

void DisableAlarmA_EnableAlarmB() {
	RTC_Disable_Write_Protection();
	
	RTC->CR &= ~RTC_CR_ALRAE;
	RTC->CR &= ~RTC_CR_ALRAIE;
	RTC->CR |= RTC_CR_ALRBE;
	RTC->CR |= RTC_CR_ALRBIE;
	
	RTC_Enable_Write_Protection();
	
}

void DisableAlarmB_EnableAlarmA() {
	RTC_Disable_Write_Protection();
	
	RTC->CR &= ~RTC_CR_ALRBE;
	RTC->CR &= ~RTC_CR_ALRBIE;
	RTC->CR |= RTC_CR_ALRAE;
	RTC->CR |= RTC_CR_ALRAIE;
	
	RTC_Enable_Write_Protection();
	
}