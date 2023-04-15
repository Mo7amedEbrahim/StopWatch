/*
 * APP.h
 *
 *  Created on: Apr 15, 2023
 *      Author: Mohammed
 */

#ifndef APP_APP_H_
#define APP_APP_H_

/*	Seven Segment Macros	*/
#define S0		PIN0
#define S1		PIN1
#define M0		PIN2
#define M1		PIN3
#define H0		PIN4
#define H1		PIN5
#define _7SegControlPORT PORTA
/********************************/
/*	ISRs Prototypes	*/
void TimerFunction(void);
void StartTimerISR(void);
void ResumeTimerISR(void);
void StopTimerISR(void);
/*******************************/



#endif /* APP_APP_H_ */
