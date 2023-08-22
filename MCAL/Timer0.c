 /******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: Timer0.h
 *
 * Description: Source file for the AVR Timer driver
 *
 * Author: Abdelrahman Mahmoud
 *
 *******************************************************************************/
#include "Timer0.h"
#include "../MCAL/gpio.h"
#include <avr/io.h>
void PWM_Timer0_Init(void){
	    TCNT0 = 0; //Set Timer Initial value

		GPIO_setupPinDirection(Timer0_OC_PORT_ID,Timer0_OC_PIN_ID,PIN_OUTPUT);

		/* Configure timer control register
		 * 1. Fast PWM mode FOC0=0
		 * 2. Fast PWM Mode WGM01=1 & WGM00=1
		 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
		 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
		 */
		TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

PWM_Timer0_Set(uint8 duty_cycle){
	OCR0  = (((duty_cycle)*255)/100); // Set Compare Value
}
void Timer0_deInit(void){
TCNT0 = 0;
OCR0 = 0;
TCCR0 = 0;
}

