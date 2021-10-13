

#define LED1        PORTB5   // LED pin
#define LED2        PORTB4
#define LED3        PORTB3
#define LED4        PORTB2

#define BUTTON      PORTC1

#ifndef F_CPU
#define F_CPU 16000000
#endif

//#include <avr/iom328p.h> // Comment out later
#include <avr/io.h>     // AVR device-specific IO definitions
#include <avr/interrupt.h> // AVR interrupt library
#include <stdint.h>

#include "library/gpio.h"   // Custom header file
#include "library/timer.h"

int main(void)
{
    GPIO_config_output(&DDRB, PORTB2); // LED 4
    GPIO_config_output(&DDRB, PORTB3); // LED 3
    GPIO_config_output(&DDRB, PORTB4); // LED 2
    GPIO_config_output(&DDRB, PORTB5); // LED 1

    GPIO_config_input_nopull(&DDRC, PORTC1); // S1-A1
    GPIO_config_input_nopull(&DDRC, PORTC2); // S2-A2
    GPIO_config_input_nopull(&DDRC, PORTC3); // S3-A3
    GPIO_write_high(&PORTB, LED1);
    GPIO_write_high(&PORTB, LED2);
    GPIO_write_high(&PORTB, LED3);
    GPIO_write_high(&PORTB, LED4);

    // Disable all interrupts except timers
    //External interrupt
    EIMSK = 0;
    EECR &= ~(1<<EERIE); // Disable eeprom ready interrupt
    //XFDCSR &= ~(1<<XFDIE); // XOSC failure detection interrupt
    WDTCSR &= ~(1<<WDIE); // Watchdog timer interrupt disable
    PCICR &= ~( (1<<PCIE0) | (1<<PCIE1) | (1<<PCIE2) /*|  (1<<PCIE3) */);
    // Pin change interrupt control register
    TIMSK0 = 0; // Disable all interrupts on timer 0
    TIMSK2 = 0; // Disable all interrupts on timer 2
    // SPI interface interrupt
    SPCR &= ~(1<<SPIE);
    // UART interface interrupt
    UCSR0B &= ~((1<<RXCIE0) | (1<<TXCIE0) | (1<<UDRIE0) );
    // Two-wire interface interrupt
    TWCR &= ~(1<<TWIE);
    // ADC interrupt
    ADCSRA &= ~(1<<ADIE);
    // Store program memory interrupt
    SPMCSR &= ~(1<<SPMIE);

    // setup timer 
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();



    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        
        if(GPIO_read(&PINC, BUTTON))
        {
            TIM1_overflow_1s();
        } else {
            TIM1_overflow_262ms();
        }
    }

    // Will never reach this
    return 0;
}

ISR(TIMER1_OVF_vect)
{
    static uint8_t leds_state = 0;
    switch (leds_state)
    {
        case 0:
            GPIO_write_low(&PORTB, LED1);
            break;

        case 1:
            GPIO_write_high(&PORTB, LED1);
            GPIO_write_low(&PORTB, LED2);
            break;
        
        case 2:
            GPIO_write_high(&PORTB, LED2);
            GPIO_write_low(&PORTB, LED3);
            break;
        
        case 3:
            GPIO_write_high(&PORTB, LED3);
            GPIO_write_low(&PORTB, LED4);
            break;
        
        case 4:
            GPIO_write_high(&PORTB, LED4);
            GPIO_write_low(&PORTB, LED3);
            break;
        
        case 5:
            GPIO_write_high(&PORTB, LED3);
            GPIO_write_low(&PORTB, LED2);
            break;
        
        case 6:
            leds_state = 0; // jumps to one because of leds_state increment
            // Reinitialize to be safe
            GPIO_write_low(&PORTB, LED1);
            GPIO_write_high(&PORTB, LED2);
            GPIO_write_high(&PORTB, LED3);
            GPIO_write_high(&PORTB, LED4);
            break; 

        default:
            leds_state = 0; // jumps to one because of leds_state increment
            break;
    }
    leds_state++;


}