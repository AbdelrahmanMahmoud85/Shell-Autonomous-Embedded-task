#include <avr/io.h>
#include "uart.h"
#include "../Libraries/common_macros.h"
/*
 * DESCRIBTION :
 * this function is called to:
 *  set up the uart frame
 * (to choose the baud rate,number of data bits,number of stop bits,..)
 * enable the uart
 *  */
void UART_init(const UART_configStruct * Config_Ptr)
{

	uint16 ubrr_value=0;
	/* U2X = 1 for double transmission speed */
	UCSRA |= (1<<U2X);
	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	/* enables the uart*/

	UCSRB = (1<<RXEN) | (1<<TXEN);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRB |= (1 << RXCIE);
	// to access UCSRC
	UCSRC |=(1<<URSEL);

	//these two lines to choose number of data bits in your frame

	UCSRC = (UCSRC & 0xF9) | ( ( (Config_Ptr->CHARACTER_SIZE)<< 1) & 0x06);
	UCSRB = (UCSRB & 0xFB) | ( (Config_Ptr->CHARACTER_SIZE) & 0x04);
	//to choose parity mode

	UCSRC = (UCSRC & 0xCF) | ((Config_Ptr->PARITY_MODE )<<4 );

	//to choose number of stop bits
	UCSRC = (UCSRC & 0xF7) | ((Config_Ptr->STOP_BIT_SELECT)<< 3);

	// to access UBRRH

	ubrr_value = (uint16)(((Freq_CPU / (Config_Ptr->Baud_Rate * (Config_Ptr->OPERATING_MODE)))) - 1);
	// to access UBRRH
	UCSRC &=~(1<<URSEL);
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;

}



/***********************************************************************************************************************/

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{

	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE))
	{

	}
	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR=data;


}
/******************************************************************************************************************/

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while (BIT_IS_CLEAR (UCSRA,RXC))
	{

	}
	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;

}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i=0;

	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}

}
/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */

void UART_receiveString(uint8 *Str)
{
	uint8 i=0;
	/* Receive the first byte */
	Str[i]= UART_recieveByte();
	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i]= UART_recieveByte();
	}
	/*put the last element in the string by 0*/
	Str[i]='\0';
}
