

#define LED_GREEN   PB5   // LED pin
#define BUTTON      PD7
#define BLINK_DELAY 500 // delay length in ms

#ifndef F_CPU
#define F_CPU 16000000
#endif

//#include <avr/iom328p.h> // Comment out later
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // AVR delay library
#include <stdint.h>

#include "library/gpio.h"   // Custom header file

//#define EXPERIMENTS
#ifndef EXPERIMENTS

int main(void)
{
    // BUTTON is pin number
    GPIO_config_input_pullup(&DDRD, BUTTON);
    // Green LED at port B
    GPIO_config_output(&DDRB, LED_GREEN);

    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);

        if(! GPIO_read(&PIND, BUTTON)) // button is inverted
        {
           GPIO_toggle(&PORTB, LED_GREEN);
        }

    }
    return 0;
}

#else

int main(void)
{
    // Leds on port B 5 to 1 
    GPIO_config_output(&DDRB, 1);
    GPIO_config_output(&DDRB, 2);
    GPIO_config_output(&DDRB, 3);
    GPIO_config_output(&DDRB, 4);
    GPIO_config_output(&DDRB, 5);
    GPIO_write_low(&PORTB, 1);
    GPIO_write_low(&PORTB, 2);
    GPIO_write_low(&PORTB, 3);
    GPIO_write_low(&PORTB, 4);
    GPIO_write_low(&PORTB, 5);

    int state = 0;
    // Infinite loop
    while (1)
    {
        _delay_ms(500);
        // Knight rider - output value sequence 
        switch(state)
        {
            case 0:
                GPIO_write_high(&PORTB, 1);
                GPIO_write_low(&PORTB, 2);
                GPIO_write_low(&PORTB, 3);
                GPIO_write_low(&PORTB, 4);
                GPIO_write_low(&PORTB, 5);
                break;

            case 1:
                GPIO_write_low(&PORTB, 1);
                GPIO_write_high(&PORTB, 2);
                GPIO_write_low(&PORTB, 3);
                GPIO_write_low(&PORTB, 4);
                GPIO_write_low(&PORTB, 5);
                break;

            case 2:
                GPIO_write_low(&PORTB, 1);
                GPIO_write_low(&PORTB, 2);
                GPIO_write_high(&PORTB, 3);
                GPIO_write_low(&PORTB, 4);
                GPIO_write_low(&PORTB, 5);
                break;
            
            case 3:
                GPIO_write_low(&PORTB, 1);
                GPIO_write_low(&PORTB, 2);
                GPIO_write_low(&PORTB, 3);
                GPIO_write_high(&PORTB, 4);
                GPIO_write_low(&PORTB, 5);
                break;
            
            case 4:
                GPIO_write_low(&PORTB, 1);
                GPIO_write_low(&PORTB, 2);
                GPIO_write_low(&PORTB, 3);
                GPIO_write_low(&PORTB, 4);
                GPIO_write_high(&PORTB, 5);
                break;
            
            case 5:
                GPIO_write_low(&PORTB, 1);
                GPIO_write_low(&PORTB, 2);
                GPIO_write_low(&PORTB, 3);
                GPIO_write_high(&PORTB, 4);
                GPIO_write_low(&PORTB, 5);
                break;
            
            case 6:
                GPIO_write_low(&PORTB, 1);
                GPIO_write_low(&PORTB, 2);
                GPIO_write_high(&PORTB, 3);
                GPIO_write_low(&PORTB, 4);
                GPIO_write_low(&PORTB, 5);
                break;
            
            case 7:
                GPIO_write_low(&PORTB, 1);
                GPIO_write_high(&PORTB, 2);
                GPIO_write_low(&PORTB, 3);
                GPIO_write_low(&PORTB, 4);
                GPIO_write_low(&PORTB, 5);
                state = -1;
                break;

            default:
                state = 0;
                GPIO_write_high(&PORTB, 1);
                GPIO_write_low(&PORTB, 2);
                GPIO_write_low(&PORTB, 3);
                GPIO_write_low(&PORTB, 4);
                GPIO_write_low(&PORTB, 5);
                break;
        }
        state++;
    }

    // Will never reach this
    return 0;
}

#endif