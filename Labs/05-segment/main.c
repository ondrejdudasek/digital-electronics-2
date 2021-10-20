/***********************************************************************
 * 
 * Decimal counter with 7-segment output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Display decimal counter values on SSD (Seven-segment 
 *           display) when 16-bit Timer/Counter1 overflows.
 * Returns:  none
 **********************************************************************/

#define HEXADECIMAL
#define MINUTES

uint8_t digits[4];
#ifndef MINUTES
uint16_t time = 0;
#else
uint8_t seconds = 0;
uint8_t minutes = 0;
#endif



int main(void)
{

    TIM1_overflow_interrupt_enable();
    TIM0_overflow_interrupt_enable();
    TIM1_overflow_1s();
    TIM0_overflow_1024us();
    
    // Configure SSD signals
    SEG_init();
    sei();
    // Test of SSD: display number '3' at position 0
    

    // Configure 16-bit Timer/Counter1 for Decimal counter
    // Set the overflow prescaler to 262 ms and enable interrupt


    // Enables interrupts by setting the global interrupt mask


    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Increment decimal counter value and display it on SSD.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    #ifndef MINUTES
    #ifndef HEXADECIMAL
    digits[3] = (time / 1000) % 10;
    digits[2] = (time / 100) % 10;
    digits[1] = (time / 10) % 10;
    digits[0] = time % 10;
    #else
    digits[3] = time >> 12;
    digits[2] = (time & 0x0F00) >> 8;
    digits[1] = (time & 0x00F0) >> 4;
    digits[0] = (time & 0x000F) >> 0;
    #endif
    time += 1;
    if(time > 59)
    {
        time = 0;
    }
    
    #else
    #ifndef HEXADECIMAL
    digits[3] = (minutes / 10) % 10;
    digits[2] =  minutes % 10;
    digits[1] = (seconds / 10) % 10;
    digits[0] =  seconds % 10;
    #else
    digits[3] = minutes >> 4;
    digits[2] = minutes & 0x0F;
    digits[1] = seconds >> 4;
    digits[0] = seconds & 0x0F;
    #endif
    seconds++;
    if(seconds >= 60)
    {
        minutes++;
        seconds = 0;
        if(minutes >= 60)
        {
            seconds = 0;
            minutes = 0;
        }
    }
    #endif

}

ISR(TIMER0_OVF_vect)
{
    static uint8_t position = 0; 
    SEG_update_shift_regs(digits[position], position);
    position++;
    if(position > 3)
    {
        position = 0;
    }
}
