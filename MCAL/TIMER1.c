/*
 * TIMER1.c
 *
 *  Created on: Oct 25, 2022
 *      Author: pc
 */
#include <avr/interrupt.h>
#include "TIMER1.h"
#include "avr/io.h" /* To use the UART Registers */
#include "../LIBRARIES/common_macros.h" /* To use the macros like SET_BIT */


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*T1_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_COMPA_vect) //compare interrupt
{
	if(T1_callBackPtr != NULL_PTR)
	{
		(*T1_callBackPtr)();
	}
}
ISR(TIMER1_OVF_vect) //overflow interrupt
{
	if(T1_callBackPtr != NULL_PTR)
	{
		(*T1_callBackPtr)();
	}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr){
TCNT1 = Config_Ptr->initial_value;
TCCR1A = (1<<FOC1A) | (1<<FOC1B); // force non-pwm

if(Config_Ptr->mode == Compare){
TIMSK |= (1<<OCIE1A); // compare flag is active
TCCR1A |= (1<<COM1A0); // toggle on compare value
TCCR1B = (1<<WGM12); // turn on compare mode
OCR1A = (Config_Ptr->compare_value); // set compare value
}

else{// overflow mode
	TIMSK = (1<<TOIE1); //overflow flag is active
}

TCCR1B |= (Config_Ptr->prescaler); // set pre-scaler
SREG  |= (1<<7); // activate interrupts
}

void Timer1_deInit(void){
TCCR1A = 0;
TCCR1B = 0;
TCNT1 = 0;
OCR1A = 0;
TIMSK &= ~(1<<TICIE1);
}

void Timer1_setCallBack(void(*a_ptr)(void)){
	T1_callBackPtr = a_ptr;
}



