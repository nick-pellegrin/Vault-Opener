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
#include <string.h>
#include <stdio.h>


int main(void) {	
	/*
	---------LAB 2----------
	*/
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
		
	RTC_Init();
	RTC_Alarm_Enable();
	RTC_Set_Alarm();

	//DisableAlarmA_EnableAlarmB();
	//DisableAlarmB_EnableAlarmA();
	
	/*
	---------LAB 4----------
	*/
	
	Init_USARTx(2);

	/*
	---------LAB 6----------
	*/
	
	SERVO_Pin_Init();
	TIM5_CH1_Init();
	
	/*
	-------------------
	*/
	
	while(1) {

	}
}
