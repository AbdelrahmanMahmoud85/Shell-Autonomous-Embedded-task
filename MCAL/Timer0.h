 /******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: Timer0.h
 *
 * Description: Header file for the AVR Timer driver
 *
 * Author: Abdelrahman Mahmoud
 *
 *******************************************************************************/
#ifndef TIMER0_H_
#define TIMER0_H_

#include "../LIBRARIES/std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Timer0_OC_PORT_ID                 PORTB_ID
#define Timer0_OC_PIN_ID                   PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void PWM_Timer0_Init(void);
void PWM_Timer0_Set(uint8 duty_cycle);
void Timer0_deInit(void);

#endif /* TIMER0_H_ */
