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
#include <stdlib.h>


int main(void) {	

	System_Clock_Init(); // Switch System Clock = 80 MHz
	RTC_Init();
	RTC_Alarm_Enable();
	Init_USARTx(2);
	SERVO_Pin_Init();
	TIM5_CH1_Init();
	SERVO_Init();
	EXTI_Init();	
	
	/*
	-------------------
	*/
	char rxByte;
	char strTime[12] = {0};
	char strDate[12] = {0};
	Get_RTC_Calendar(strTime, strDate);
	
	while(1) {
		
		if (isAuthorized) {
			printf("ACCESS REQUESTED. ALLOW ACCESS? (Y/N)\n");
			while (scanf("%c", &rxByte) == 0);
			if (rxByte == 'Y'){
				Get_RTC_Calendar(strTime, strDate);
				char timeoutSecondsStr[3];
				timeoutSecondsStr[0] = strTime[6];
				timeoutSecondsStr[1] = strTime[7];
				timeoutSecondsStr[2] = '\0'; // Null-terminate the string
				int timeoutSeconds = atoi(timeoutSecondsStr);
				RTC_Set_Alarm((timeoutSeconds + 15) % 60);
				EnableAlarmA();
				printf("\n\tACCESS GRANTED.\t---\tEntry logged at: %s on %s\n\n\n\n", strTime, strDate);
				Servo_Move_Center();
				while(isTimeoutComplete == 0);
				DisableAlarmA();
			} 
			
			else if (rxByte == 'N'){
				Get_RTC_Calendar(strTime, strDate);
				printf("\n\tACCESS DENIED.\t---\tEntry logged at: %s on %s\n\n\n\n", strTime, strDate);
			} 
			
			else {
				printf("\nWARNING: Please enter a valid character. Rescan card and try again.\n\n\n\n");
			}
			
			isAuthorized = 0;
			rxByte = 0;
			isTimeoutComplete = 0;
			
		}
		
	}
}
