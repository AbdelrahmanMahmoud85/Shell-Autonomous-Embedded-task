/*
 * uart.h
 *
 *  Created on: Oct 9, 2022
 *      Author: haidy
 */
/****************************************************************************************/
/***********************************DEFINITIONS*****************************************/
#ifndef UART_H_
#define UART_H_
#define Freq_CPU 8000000
#define BAUD_RATE 9600
#include "../Libraries/std_types.h"

/*************************************************************************************/
/**********************************TYPE DECLARATIONS*********************************/
typedef uint32 UART_BaudRate;
typedef enum
{
	FIVE_BIT,SIX_BIT,SEVEN_BIT,EIGHT_BIT,NINE_BIT=7
}UART_BitData;
/*********************************************************************************/

typedef enum
{
	ONE_BIT,TWO_BIT
}UART_StopBit;

/******************************************************************************/

typedef enum
{
	DISABLED,EVEN_PARITY=2,ODD_PARITY}
UART_Parity;

/******************************************************************************/

typedef enum
{
	NORMAL_MODE=16,DOUBLE_SPEED_MODE=8
}UART_operatingMode ;

/******************************************************************************/
/*DESCRIBTION : structure that will be passed to the init function to identifies the frame of uart*/

typedef struct
{
	UART_BitData CHARACTER_SIZE;
	UART_StopBit STOP_BIT_SELECT;
	UART_Parity PARITY_MODE;
	UART_BaudRate  Baud_Rate ;
	UART_operatingMode OPERATING_MODE;

}UART_configStruct;

/******************************************************************************/
/************************FUNCTIONS DECLARATIONS*******************************/
/*
 *DESCRIBTION:
 * DESCRIBTION :
 * this function is called to:
 *  set up the uart frame
 * (to choose the baud rate,number of data bits,number of stop bits,..)
 * enable the uart
 */
void UART_init(const UART_configStruct * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);


/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str);

/*************************************************************************/
#endif /* UART_H_ */
