#include "UART.h"

void UART1_Init(void) {
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	RCC->CCIPR &= ~(RCC_CCIPR_USART1SEL);
	RCC->CCIPR |= RCC_CCIPR_USART1SEL_0;
}

void UART2_Init(void) {
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

	RCC->CCIPR &= ~(RCC_CCIPR_USART2SEL);	
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_0;
}

void UART1_GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	
	GPIOB->MODER &= ~(GPIO_MODER_MODE6);
	GPIOB->MODER |= GPIO_MODER_MODE6_1;        
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6);		
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_2 | GPIO_AFRL_AFSEL6_1 | GPIO_AFRL_AFSEL6_0;	

	GPIOB->MODER &= ~(GPIO_MODER_MODE7);     
	GPIOB->MODER |= GPIO_MODER_MODE7_1;        
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL7);	
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_2 | GPIO_AFRL_AFSEL7_1 | GPIO_AFRL_AFSEL7_0;		

	GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEED6); 	
	GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEED7);

	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT6); 	
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT7);

	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD6);
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD6_0;
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD7);
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD7_0;
}

void UART2_GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE2);     
	GPIOA->MODER |= GPIO_MODER_MODE2_1;   
	
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2);		
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_0 | GPIO_AFRL_AFSEL2_1 | GPIO_AFRL_AFSEL2_2;
	
	GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED2);
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT2); 
	
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD2);	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_0;

	GPIOA->MODER &= ~(GPIO_MODER_MODE3);        
	GPIOA->MODER |= GPIO_MODER_MODE3_1; 
	
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL3);		
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL3_0 | GPIO_AFRL_AFSEL3_1 | GPIO_AFRL_AFSEL3_2;
	
	GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED3);
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT3);

	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD3);
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_0;
}

void USART_Init(USART_TypeDef* USARTx) {
	USARTx->CR1 &= ~(USART_CR1_UE);

	USARTx->CR1 &= USART_CR1_M1;
	USARTx->CR1 &= USART_CR1_M0;
	
	USARTx->CR1 &= ~USART_CR1_OVER8; 
	USARTx->CR2 &= ~USART_CR2_STOP;
	
	USARTx->BRR = 8333;
					
	USARTx->CR1 |= USART_CR1_TE;
	USARTx->CR1 |= USART_CR1_RE;

	USARTx->CR1 |= USART_CR1_UE;
}

uint8_t USART_Read (USART_TypeDef * USARTx) {
	// SR_RXNE (Read data register not empty) bit is set by hardware
	while (!(USARTx->ISR & USART_ISR_RXNE));  // Wait until RXNE (RX not empty) bit is set
	// USART resets the RXNE flag automatically after reading DR
	return ((uint8_t)(USARTx->RDR & 0xFF));
	// Reading USART_DR automatically clears the RXNE flag 
}

void USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes) {
	int i;
	// TXE is cleared by a write to the USART_DR register.
	// TXE is set by hardware when the content of the TDR 
	// register has been transferred into the shift register.
	for (i = 0; i < nBytes; i++) {
		while (!(USARTx->ISR & USART_ISR_TXE));   	// wait until TXE (TX empty) bit is set
		// Writing USART_DR automatically clears the TXE flag 	
		USARTx->TDR = buffer[i] & 0xFF;
		USART_Delay(500);
	}
	while (!(USARTx->ISR & USART_ISR_TC));   		  // wait until TC bit is set
	USARTx->ISR &= ~USART_ISR_TC;
}   

void USART_Delay(uint32_t us) {
	uint32_t time = 100*us/7;    
	while(--time);   
}

// Initializes USARTx
// USART2: UART Communication with Termite
// USART1: Bluetooth Communication with Phone
void Init_USARTx(int x) {
	if(x == 1) {
		UART1_Init();
		UART1_GPIO_Init();
		USART_Init(USART1);
	} else if(x == 2) {
		UART2_Init();
		UART2_GPIO_Init();
		USART_Init(USART2);
	} else {
		// Do nothing...
	}
}