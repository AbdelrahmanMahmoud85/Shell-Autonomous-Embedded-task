/*
 * Stepper_Motor.c
 *
 *  Created on: 22 Aug 2023
 *      Author: pc
 */

#include "../MCAL/gpio.h"
#include "Stepper_Motor.h"
#include <util/delay.h>

void Stepper_Init(void){
	GPIO_setupPinDirection(Stepper_MOTOR_IN1_PORT, Stepper_MOTOR_IN1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(Stepper_MOTOR_IN2_PORT, Stepper_MOTOR_IN2_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(Stepper_MOTOR_IN3_PORT, Stepper_MOTOR_IN3_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(Stepper_MOTOR_IN4_PORT, Stepper_MOTOR_IN4_PIN, PIN_OUTPUT);
	GPIO_WritePin(Stepper_MOTOR_IN1_PORT, Stepper_MOTOR_IN1_PIN, (Stepper_MOTOR_DEFAULT_POSITION >> 3) & 0x01);
	GPIO_WritePin(Stepper_MOTOR_IN2_PORT, Stepper_MOTOR_IN2_PIN, (Stepper_MOTOR_DEFAULT_POSITION >> 2) & 0x01);
	GPIO_WritePin(Stepper_MOTOR_IN3_PORT, Stepper_MOTOR_IN3_PIN, (Stepper_MOTOR_DEFAULT_POSITION >> 1) & 0x01);
	GPIO_WritePin(Stepper_MOTOR_IN4_PORT, Stepper_MOTOR_IN4_PIN, (Stepper_MOTOR_DEFAULT_POSITION >> 0) & 0x01);
}



void Stepper_Start(uint16 *stepsPerRevolution, uint8 direction) {
	static int i = 0;
	if(*stepsPerRevolution > 0){
		switch(direction){
		case 'L':
			(*stepsPerRevolution)--;
			GPIO_WritePin(Stepper_MOTOR_IN1_PORT, Stepper_MOTOR_IN1_PIN, (Stepper_steps[i] >> 3) & 0x01);
			GPIO_WritePin(Stepper_MOTOR_IN2_PORT, Stepper_MOTOR_IN2_PIN, (Stepper_steps[i] >> 2) & 0x01);
			GPIO_WritePin(Stepper_MOTOR_IN3_PORT, Stepper_MOTOR_IN3_PIN, (Stepper_steps[i] >> 1) & 0x01);
			GPIO_WritePin(Stepper_MOTOR_IN4_PORT, Stepper_MOTOR_IN4_PIN, (Stepper_steps[i] >> 0) & 0x01);
			_delay_ms(20);
			if(i<=7){
			i++;
			}
			else{
			i = 0;
			}
			break;

		case 'R':
			(*stepsPerRevolution)--;
			GPIO_WritePin(Stepper_MOTOR_IN1_PORT, Stepper_MOTOR_IN1_PIN, (Stepper_steps[7-i] >> 3) & 0x01);
			GPIO_WritePin(Stepper_MOTOR_IN2_PORT, Stepper_MOTOR_IN2_PIN, (Stepper_steps[7-i] >> 2) & 0x01);
			GPIO_WritePin(Stepper_MOTOR_IN3_PORT, Stepper_MOTOR_IN3_PIN, (Stepper_steps[7-i] >> 1) & 0x01);
			GPIO_WritePin(Stepper_MOTOR_IN4_PORT, Stepper_MOTOR_IN4_PIN, (Stepper_steps[7-i] >> 0) & 0x01);
			_delay_ms(20);
			if(i<=7){
			i++;
			}
			else{
			i = 0;
			}
			break;}
	}
}

