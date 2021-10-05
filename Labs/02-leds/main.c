

#define LED_RED   PC0   // AVR pin where green LED is connected
#define LED_GREEN PB5
#define BUTTON    PC1

#define LED_RED_OFF()     PORTC = PORTC | (1<<LED_RED)
#define LED_RED_ON()      PORTC = PORTC & ~(1<<LED_RED)
#define LED_GREEN_ON()    PORTB = PORTB | (1<<LED_GREEN)
#define LED_GREEN_OFF()   PORTB = PORTB & ~(1<<LED_GREEN)

#define DEBOUNCE_FILTER_VALUE_MAX 100
#define DEBOUNCE_FILTER_SAMPLE_FREQ 1000


#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h>

// Define only one part! 
#define PART_2_LEDS
//#define PART_3_BUTTON
//#define PART_4_DEBOUNCE



#if defined(PART_2_LEDS) || defined(PART_3_BUTTON)

int main(void)
{
    DDRC = DDRC | (1<<LED_RED);
    DDRB = DDRB | (1<<LED_GREEN);

    #ifdef PART_3_BUTTON
        DDRC = DDRC & ~(1<<BUTTON);
        PORTC = PORTC | (1<<BUTTON);
    #endif    
    

    while (1)
    {
        #ifdef PART_3_BUTTON
            loop_until_bit_is_clear(PINC, BUTTON);
        #endif

        LED_RED_ON();
        LED_GREEN_OFF();
        _delay_ms(500);

        #ifdef PART_3_BUTTON
            loop_until_bit_is_clear(PINC, BUTTON);
        #endif

        
        LED_RED_OFF();
        LED_GREEN_ON();
        _delay_ms(500);

    }

    return 0;
}

#elif defined(PART_4_DEBOUNCE)

int main(void)
{
    // Setup registers
    DDRC = DDRC | (1<<LED_RED);
    DDRC = DDRC & ~(1<<BUTTON);
    PORTC = PORTC | (1<<BUTTON);

    int filter_value = 1;

    while(1)
    {
        if(bit_is_set(PINC, BUTTON))
        {   
            if(filter_value < DEBOUNCE_FILTER_VALUE_MAX)
            {
                filter_value++;
                if(filter_value == DEBOUNCE_FILTER_VALUE_MAX)
                {
                    LED_RED_ON();
                }
            }
        }
        else /* BUTTON is down */
        {
            if(filter_value > 0)
            {
                filter_value--;
                if(filter_value == 0)
                {
                    LED_RED_OFF();
                }
            }
        }
        _delay_ms(1000/DEBOUNCE_FILTER_SAMPLE_FREQ);
    }

}
#else
#error No main function specified
#endif