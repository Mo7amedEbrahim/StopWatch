/*
 * main.c
 *
 *  Created on: Dec 8, 2022
 *      Author: Mohammed
 */
#include "util/delay.h"
/****	Libraries Includes	****/
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
/****	MCAL Layer Includes	****/
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/PORT/PORT_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/TIMER0/TMR0_interface.h"
/****	Hardware Layer Includes	****/
#include "../HAL/BUTTON/BUTTON.h"
#include "../HAL/7SEG/7SEG.h"
#include "../HAL/LCD/LCD.h"
/***************************************/
#include "APP.h"

u8 seconds,minutes,hours;

int main(void){
	EXTI_INT0Init(FALLING_EDGE);
	EXTI_INT1Init(FALLING_EDGE);
	EXTI_INT2Init(FALLING_EDGE);
	GIE_Enable();
	TMR0_t Timer0Configuration ={
			.TIMER0_Mode = CTC_MODE,
			.TIMER0_Prescaler = TMR0_DIV_BY_8,
			.TMR0_OCR0 = 250,
			.ActionFunction = TimerFunction

	};
	PORT_Init();
	_7SEG_Init(PORTC);
	TMR0_Init(&Timer0Configuration);
	TMR0_CTCInterruptDisable();
	TMR0_CTCSetCallBack(&Timer0Configuration);
	EXTI_SetCallBackINT0(&StartTimerISR);
	EXTI_SetCallBackINT1(&ResumeTimerISR);
	EXTI_SetCallBackINT2(&StopTimerISR);
	while(1){
		DIO_SetPortValue(_7SegControlPORT,LOW);
		_7SEG_Display(PORTC,seconds%10);
		DIO_SetPinValue(_7SegControlPORT,S0,HIGH);
		_delay_ms(10);
		DIO_SetPinValue(_7SegControlPORT,S0,LOW);
		_7SEG_Display(PORTC,seconds/10);
		DIO_SetPinValue(_7SegControlPORT,S1,HIGH);
		_delay_ms(10);
		DIO_SetPinValue(_7SegControlPORT,S1,LOW);
		_7SEG_Display(PORTC,minutes%10);
		DIO_SetPinValue(_7SegControlPORT,M0,HIGH);
		_delay_ms(10);
		DIO_SetPinValue(_7SegControlPORT,M0,LOW);
		_7SEG_Display(PORTC,minutes/10);
		DIO_SetPinValue(_7SegControlPORT,M1,HIGH);
		_delay_ms(10);
		DIO_SetPinValue(_7SegControlPORT,M1,LOW);
		_7SEG_Display(PORTC,hours%10);
		DIO_SetPinValue(_7SegControlPORT,H0,HIGH);
		_delay_ms(10);
		DIO_SetPinValue(_7SegControlPORT,H0,LOW);
		_7SEG_Display(PORTC,hours/10);
		DIO_SetPinValue(_7SegControlPORT,H1,HIGH);
		_delay_ms(10);
	}
	return 0;
}

void TimerFunction(void){
	static u16 Counter = 0;
	Counter++;
	if(Counter == 4000){
		if(seconds<59){
			seconds++;
		}
		else if(seconds == 59) {
			seconds = 0;
			if(minutes <59){
				minutes++;
			}
			else if(minutes == 59){
				minutes = 0;
				if(hours < 23){
					hours++;
				}
				else if(hours == 23){
					seconds = 0;
					minutes = 0;
					hours = 0;

				}
			}
		}
		Counter = 0;
	}
}
void StartTimerISR(void){
	seconds = 0;
	minutes = 0;
	hours = 0;
	TMR0_CTCInterruptEnable();
}
void ResumeTimerISR(void){
	TMR0_CTCInterruptEnable();
}
void StopTimerISR(void){
	TMR0_CTCInterruptDisable();
}
