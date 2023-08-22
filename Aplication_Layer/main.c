#include "../HAL/LCD.h"
#include "../MCAL/UART.h"
#include "../MCAL/GPIO.h"
#include "../MCAL/TIMER1.h"
#include "../MCAL/Timer0.h"
#include "../HAL/DC_Motor.h"
#include "util/delay.h"
#include <avr/interrupt.h>
#include <avr/io.h>

uint16 Stepper_Angle;             // Variable to store the stepper motor angle
uint8 Stepper_Direction;          // Variable to store the stepper motor direction

#define PRINT_TIME(type,location) LCD_moveCursor(1,location); LCD_intgerToString(type)

// Function to validate the received input frame
void Validate_Input(uint8 arr[]) {
    // Check if the frame obeys the protocol
    if (arr[7] != 'E' || (arr[0] - '0') > 1 || (arr[0] - '0') < 0 ||
        (arr[3] != 'F' && arr[3] != 'B') ||
        (arr[4] > '4') || (arr[4] == '4' && arr[5] > '5') ||
        (arr[6] != 'R' && arr[6] != 'L')) {
        LCD_displayStringRowColumn(0, 0, "Wrong input, re-enter the frame");
        return;
    }

    // Convert ASCII to integer for DC motor speed
    uint8 DC_Motor_Speed = (arr[0] - '0') * 100 + (arr[1] - '0') * 10 + (arr[2] - '0');

    uint8 DC_Motor_Direction = 0;

    // Determine DC motor direction based on the input
    switch (arr[3]) {
        case 'F':
            DC_Motor_Direction = ACW;
            break;
        case 'B':
            DC_Motor_Direction = CW;
            break;
    }

    // Rotate the DC motor based on the direction and speed
    DCmotor_rotate(DC_Motor_Direction, DC_Motor_Speed);

    // Convert ASCII to integer for stepper motor angle
    Stepper_Angle = (arr[4] - '0') * 10 + (arr[5] - '0');

    Stepper_Direction = arr[6]; // Store the stepper motor direction

    // Display DC motor speed and stepper motor angle on LCD
    LCD_displayStringRowColumn(0, 0, "   Speed: ");
    LCD_intgerToString(DC_Motor_Speed);
    LCD_displayString("%");

    LCD_displayString("  Direction: ");
    if (Stepper_Direction == 'L') {
        LCD_displayString("-");
    }
    LCD_intgerToString(Stepper_Angle);
    LCD_displayString("       ");
}

void Clock(void) { // Function to Display Time on LCD

    static uint8 seconds_0 = 0;    // Static variable for the units digit of seconds
    static uint8 seconds_1 = 0;    // Static variable for the tens digit of seconds
    static uint8 minutes_0 = 0;    // Static variable for the units digit of minutes
    static uint8 minutes_1 = 0;    // Static variable for the tens digit of minutes
    static uint8 hours_0 = 0;      // Static variable for the units digit of hours
    static uint8 hours_1 = 0;      // Static variable for the tens digit of hours
    static uint8 time = 'A';       // Static variable to represent AM or PM

    if (seconds_0 < 9) { // If units digit of seconds is less than 9
        seconds_0++; // Increment units digit of seconds
        PRINT_TIME(seconds_0, 20); // Display updated seconds on LCD
    } else if (seconds_1 < 5) { // If tens digit of seconds is less than 5
        seconds_0 = 0; // Reset units digit of seconds
        seconds_1++; // Increment tens digit of seconds
        PRINT_TIME(seconds_0, 20); // Display updated seconds on LCD
        PRINT_TIME(seconds_1, 19); // Display updated seconds on LCD
    } else if (minutes_0 < 9) { // If units digit of minutes is less than 9
        seconds_0 = 0; // Reset units digit of seconds
        seconds_1 = 0; // Reset tens digit of seconds
        minutes_0++; // Increment units digit of minutes
        PRINT_TIME(seconds_0, 20); // Display updated seconds on LCD
        PRINT_TIME(seconds_1, 19); // Display updated seconds on LCD
        PRINT_TIME(minutes_0, 17); // Display updated minutes on LCD
    } else if (minutes_1 < 5) { // If tens digit of minutes is less than 5
        seconds_0 = 0; // Reset units digit of seconds
        seconds_1 = 0; // Reset tens digit of seconds
        minutes_0 = 0; // Reset units digit of minutes
        minutes_1++; // Increment tens digit of minutes
        PRINT_TIME(seconds_0, 20); // Display updated seconds on LCD
        PRINT_TIME(seconds_1, 19); // Display updated seconds on LCD
        PRINT_TIME(minutes_0, 17); // Display updated minutes on LCD
        PRINT_TIME(minutes_1, 16); // Display updated minutes on LCD
    } else if (hours_0 < 9 && (hours_1 != 1 && hours_0 < 2)) {
        // If units digit of hours is less than 9 and the time is before 3:00
        seconds_0 = 0; // Reset units digit of seconds
        seconds_1 = 0; // Reset tens digit of seconds
        minutes_0 = 0; // Reset units digit of minutes
        minutes_1 = 0; // Reset tens digit of minutes
        hours_0++; // Increment units digit of hours
        PRINT_TIME(seconds_0, 20); // Display updated seconds on LCD
        PRINT_TIME(seconds_1, 19); // Display updated seconds on LCD
        PRINT_TIME(minutes_0, 17); // Display updated minutes on LCD
        PRINT_TIME(minutes_1, 16); // Display updated minutes on LCD
        PRINT_TIME(hours_0, 14);   // Display updated hours on LCD
    } else if (hours_1 <= 1 && hours_0 < 1) {
        // If tens digit of hours is less than or equal to 1 and units digit of hours is less than 2
        seconds_0 = 0; // Reset units digit of seconds
        seconds_1 = 0; // Reset tens digit of seconds
        minutes_0 = 0; // Reset units digit of minutes
        minutes_1 = 0; // Reset tens digit of minutes
        hours_0 = 0;   // Reset units digit of hours
        hours_1++;     // Increment tens digit of hours
        PRINT_TIME(seconds_0, 20); // Display updated seconds on LCD
        PRINT_TIME(seconds_1, 19); // Display updated seconds on LCD
        PRINT_TIME(minutes_0, 17); // Display updated minutes on LCD
        PRINT_TIME(minutes_1, 16); // Display updated minutes on LCD
        PRINT_TIME(hours_0, 14);   // Display updated hours on LCD
        PRINT_TIME(hours_1, 13);   // Display updated hours on LCD
    } else {
        // When the time exceeds 11:59, reset the time
        seconds_0 = 0; // Reset units digit of seconds
        seconds_1 = 0; // Reset tens digit of seconds
        minutes_0 = 0; // Reset units digit of minutes
        minutes_1 = 0; // Reset tens digit of minutes
        hours_0 = 0;   // Reset units digit of hours
        hours_1 = 0;   // Reset tens digit of hours

        // Toggle between AM and PM
        if (time == 'A') {
            time = 'P';
            LCD_moveCursor(1, 22);
            LCD_displayCharacter(time); // Display PM on LCD
        } else {
            time = 'A';
            LCD_moveCursor(1, 22);
            LCD_displayCharacter(time); // Display AM on LCD
        }

        // Display all time components on LCD
        PRINT_TIME(seconds_0, 20);
        PRINT_TIME(seconds_1, 19);
        PRINT_TIME(minutes_0, 17);
        PRINT_TIME(minutes_1, 16);
        PRINT_TIME(hours_0, 14);
        PRINT_TIME(hours_1, 13);
    }
}

void Input_Read(void) {
    static uint8 arr[8] = {0}; // Static array to store the received input frame
    static uint8 i = 0; // Static variable to keep track of the array index

    if (i == 0) {
        LCD_displayStringRowColumn(0, 0, "   Please enter a valid frame            ");
        // Display a message on the LCD when reading the first character
    }

    arr[i] = UART_recieveByte(); // Receive a byte from UART and store in the array
    if(arr[i] == 'E' && i != 7){
    	LCD_displayStringRowColumn(0, 0, "       Wrong frame length!      ");
    	i = 0;
    }
    else{
        i++; // Increment the array index
    }

    if (i > 7) {
        i = 0; // Reset the array index when all characters are read
        Validate_Input(arr); // Validate the received input frame
    }
}

// Interrupt Service Routine for USART Receive Complete
ISR(USART_RXC_vect) {
    Input_Read(); // Call the input reading function when USART receives a byte
}


int main(void) {
    // Enable global interrupts
    sei();

    // Initialize UART, LCD, DC motor, stepper, and timer configurations
    UART_configStruct UART_Configuration = { EIGHT_BIT , ONE_BIT ,DISABLED , 9600, DOUBLE_SPEED_MODE} ;
    UART_init(&UART_Configuration);
    LCD_init();
    DCmotor_init();
    Stepper_Init();
    Timer1_ConfigType timer1 = {0,7812,FO1024,Compare}; //CTC value for 1 second = 8 MHz/1024 = 7812.5
    Timer1_init(&timer1);

    // Display welcome message and initial time on LCD
    LCD_displayString(" Welcome, good to see you again.");
    _delay_ms(250);
    LCD_displayStringRowColumn(1, 0, "       Time: 00:00:00 AM");

    // Set clock update function as Timer1 callback
    Timer1_setCallBack(Clock);

    // Main loop
    while(1) {
        // Start stepper motor motion based on given angle and direction
        Stepper_Start(&Stepper_Angle, Stepper_Direction);
    }
}
