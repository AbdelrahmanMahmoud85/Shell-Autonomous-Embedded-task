 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_Motor.h
 *
 * Description: Source file for the DC Motor driver
 *
 * Author: Abdelrahman Mahmoud
 *
 *******************************************************************************/

#include "../MCAL/gpio.h"
#include "DC_Motor.h"
#include "../MCAL/Timer0.h"

void DCmotor_init(void){
	PWM_Timer0_Init();
	GPIO_setupPinDirection(DC_MOTOR_IN1_PORT, DC_MOTOR_IN1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN2_PORT, DC_MOTOR_IN2_PIN, PIN_OUTPUT);
	GPIO_WritePin(DC_MOTOR_IN1_PORT, DC_MOTOR_IN1_PIN, LOGIC_LOW);
	GPIO_WritePin(DC_MOTOR_IN2_PORT, DC_MOTOR_IN2_PIN, LOGIC_LOW);
}
void DCmotor_rotate(DCMotor_State state,uint8 speed){
	PWM_Timer0_Set(speed);
	switch(state){
	case Stop:
		GPIO_WritePin(DC_MOTOR_IN1_PORT, DC_MOTOR_IN1_PIN, LOGIC_LOW);
		GPIO_WritePin(DC_MOTOR_IN2_PORT, DC_MOTOR_IN2_PIN, LOGIC_LOW);
		break;
	case CW:
		GPIO_WritePin(DC_MOTOR_IN1_PORT, DC_MOTOR_IN1_PIN, LOGIC_LOW);
		GPIO_WritePin(DC_MOTOR_IN2_PORT, DC_MOTOR_IN2_PIN, LOGIC_HIGH);
		break;
	case ACW:
		GPIO_WritePin(DC_MOTOR_IN1_PORT, DC_MOTOR_IN1_PIN, LOGIC_HIGH);
		GPIO_WritePin(DC_MOTOR_IN2_PORT, DC_MOTOR_IN2_PIN, LOGIC_LOW);
		break;
	}
}
