/*
 * ECE 153B - Winter 2023
 *
 * Name(s): Jake Greenbaum, Nicholas Pellegrin
 * Section: Tuesday 7-9:50pm
 * Final Project
 */
 
#include "stm32l476xx.h"
#include "RTC.h"
#include "SysClock.h"
#include "UART.h"
#include "servoFunctionality.h"
#include "rtcFunctionality.h"
#include "EXTI.h"
#include <string.h>
#include <stdio.h>


int main(void) {	

	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	RTC_Init();
	RTC_Alarm_Enable();
	RTC_Set_Alarm();

	//DisableAlarmA_EnableAlarmB();
	//DisableAlarmB_EnableAlarmA();
	
	Init_USARTx(2);
	
	SERVO_Pin_Init();
	TIM5_CH1_Init();
	EXTI_Init();	
	
	/*
	-------------------
	*/
	printf("Starting code...");
	
	while(1) {
		
		printf("%d\n", isAuthorized);
		
		if (isAuthorized) {
			printf("Working\n");
			isAuthorized = 0;
		}
		for(int i=0; i < 10000000; i++);
	}
}
