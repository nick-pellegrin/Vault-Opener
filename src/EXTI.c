#include "EXTI.h"

volatile int isAuthorized = 0;

void EXTI_Init(void) {
	// Initialize User Button
	GPIOA->MODER &= ~GPIO_MODER_MODE1;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1;
	
	// Configure SYSCFG EXTI
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PA;
	
	// Configure EXTI Trigger
	EXTI->RTSR1 |= EXTI_RTSR1_RT1;
	
	// Enable EXTI
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	
	// Configure and Enable in NVIC
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_SetPriority(EXTI1_IRQn, 0);
}

void EXTI1_IRQHandler(void) {
	NVIC_ClearPendingIRQ(EXTI1_IRQn);
	
	if (EXTI->PR1 & EXTI_PR1_PIF1) {
		// Clear interrupt pending bit
		EXTI->PR1 |= EXTI_PR1_PIF1;
	
		// Define behavior that occurs when interrupt occurs
		if (GPIOA->IDR & GPIO_IDR_ID1)		// arduino gives random noise so this fixes that issue
			isAuthorized = 1;						
	}
}
