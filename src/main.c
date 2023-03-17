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
#include "rfid.h"
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


	printf("Application Starting...\n");

	uint8_t rfid_id[4];

	rc522_init();
	
	while(1) {

		if(rc522_checkCard(rfid_id)) {
			char data[20];
			sprintf(data,"0x%x 0x%x 0x%x 0x%x",rfid_id[0],rfid_id[1],rfid_id[2],rfid_id[3]);
			for(int i = 0; i < 1000000; i++);
			printf("Card number is: ", rfid_id[0]);
		}

	}
}
