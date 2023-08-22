################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GPIO.c \
../MCAL/TIMER1.c \
../MCAL/Timer0.c \
../MCAL/uart.c 

OBJS += \
./MCAL/GPIO.o \
./MCAL/TIMER1.o \
./MCAL/Timer0.o \
./MCAL/uart.o 

C_DEPS += \
./MCAL/GPIO.d \
./MCAL/TIMER1.d \
./MCAL/Timer0.d \
./MCAL/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


