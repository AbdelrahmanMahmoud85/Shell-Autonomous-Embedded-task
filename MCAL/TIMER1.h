/*
 * TIMER1.h
 *
 *  Created on: Oct 25, 2022
 *      Author: pc
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "../LIBRARIES/std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	Normal,Compare
}Timer1_Mode;

typedef enum
{
	NO_PRESCALER,FO1,FO8,FO64,FO256,FO1024,EXT_CLK_FALLING,EXT_CLK_RISING
}Timer1_Prescaler;

typedef struct{
uint16 initial_value;
uint16 compare_value; // it will be used in compare mode only.
Timer1_Prescaler prescaler;
Timer1_Mode mode;
}Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));
#endif /* TIMER1_H_ */
