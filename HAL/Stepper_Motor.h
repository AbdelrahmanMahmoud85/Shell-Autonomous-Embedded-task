/*
 * Stepper_Motor.h
 *
 *  Created on: 22 Aug 2023
 *      Author: pc
 */

#ifndef HAL_STEPPER_MOTOR_H_
#define HAL_STEPPER_MOTOR_H_

#include "../Libraries/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Stepper_MOTOR_IN1_PORT                        PORTC_ID
#define Stepper_MOTOR_IN1_PIN                         PIN2_ID
#define Stepper_MOTOR_IN2_PORT                        PORTC_ID
#define Stepper_MOTOR_IN2_PIN                         PIN3_ID
#define Stepper_MOTOR_IN3_PORT                        PORTC_ID
#define Stepper_MOTOR_IN3_PIN                         PIN4_ID
#define Stepper_MOTOR_IN4_PORT                        PORTC_ID
#define Stepper_MOTOR_IN4_PIN                		  PIN5_ID
#define Stepper_MOTOR_DEFAULT_POSITION                6
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

uint8 Stepper_steps[9] = {6,2,3,1,9,8,12,4,6};
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Stepper_Start(uint16 *stepsPerRevolution, uint8 direction);
void Stepper_Init(void);

#endif /* HAL_STEPPER_MOTOR_H_ */
