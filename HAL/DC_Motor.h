 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_Motor.h
 *
 * Description: Header file for the DC Motor driver
 *
 * Author: Abdelrahman Mahmoud
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../LIBRARIES/std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_IN1_PORT                PORTC_ID
#define DC_MOTOR_IN1_PIN                 PIN0_ID
#define DC_MOTOR_IN2_PORT                PORTC_ID
#define DC_MOTOR_IN2_PIN                 PIN1_ID
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	Stop,CW,ACW
}DCMotor_State;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void DCmotor_init(void);
void DCmotor_rotate(DCMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
