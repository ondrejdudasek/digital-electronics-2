
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "library/lcd.h"
#include "library/uart.h"
#include "library/timer.h"

// KEYS

#define SELECT_  "SELECT"
#define LEFT_    "LEFT  "
#define UP_      "UP    "
#define DOWN_    "DOWN  "
#define RIGHT_   "RIGHT "
#define NONE_    "NONE  "

#define SELECT  "SELECT"
#define LEFT    "LEFT"
#define UP      "UP"
#define DOWN    "DOWN"
#define RIGHT   "RIGHT"
#define NONE    "NONE"
 
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
    lcd_gotoxy(1, 0); lcd_puts("value:");
    lcd_gotoxy(3, 1); lcd_puts("key:");
    lcd_gotoxy(8, 0); lcd_puts("a");    // Put ADC value in decimal
    //lcd_gotoxy(13,0); lcd_puts("b");    // Put ADC value in hexadecimal
    lcd_gotoxy(8, 1); lcd_puts("c");    // Put button name here

    // Configure ADC to convert PC0[A0] analog value

    // Set ADC reference to AVcc

    ADMUX &= 0b00101111; // zero out unwanted values
    ADMUX |= (1 << REFS0);

    // Set input channel to ADC0

    ADMUX &= 0b11100000; // channel 0 is enabled by zeros on 4 LSB's

    // Enable ADC module

    ADCSRA |= (1<<ADEN);

    // Enable conversion complete interrupt
    ADCSRA |= (1<<ADIE) + (1<<ADATE);


    // Set clock prescaler to 128
    ADCSRA |= 0b111; 

    // Configure 16-bit Timer/Counter1 to start ADC conversion
    ADCSRB |= 0b110;
    ADCSRB &= ~(0b00000001);

    // Set prescaler to 262 ms and enable overflow interrupt
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    // Initialize UART to asynchronous, 8N1, 9600
    //UART_BAUD_SELECT(9600, 16000000UL);
    uart_init(UART_BAUD_SELECT(9600, F_CPU));
    

    // Enables interrupts by setting the global interrupt mask
    sei();

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
 * Purpose:  Use single conversion mode and start conversion four times
 *           per second.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    // Not required now;
    static uint8_t counter; 
    if(counter > 9) counter = 0;
    char a[4];
    lcd_gotoxy(14, 1);
    sprintf(&a[0], "%01d", counter);
    //lcd_puts(&a[0]);
    counter ++;
}

/**********************************************************************
 * Function: ADC complete interrupt
 * Purpose:  Display value on LCD and send it to UART.
 **********************************************************************/
ISR(ADC_vect)
{
    uint16_t adc_result;
    char result[6];
    // Order matters! 
    adc_result = ADCL;
    adc_result += (ADCH << 8);

    lcd_gotoxy(8, 1);
    uart_putc(0x0D);
    

    if(adc_result > 1010){
        lcd_puts(NONE_);
        uart_puts(NONE);
    } else if (adc_result > 600)
    {
        lcd_puts(SELECT_);
        uart_puts(SELECT);
    } else if (adc_result > 400)
    {
        lcd_puts(LEFT_);
        uart_puts(LEFT);
    } else if (adc_result > 200)
    {
        lcd_puts(DOWN_);
        uart_puts(DOWN);
    } else if (adc_result > 90)
    {
        lcd_puts(UP_);
        uart_puts(UP);
    } else
    {
        lcd_puts(RIGHT_);
        uart_puts(RIGHT);
    }

    uart_putc('\t');
    lcd_gotoxy(8, 0);
    
    sprintf(&result[0], "%04d", adc_result);
    lcd_puts(&result[0]);
    uart_puts(&result[0]);

    lcd_gotoxy(13, 0);
    uart_putc('\t');

    sprintf(&result[0], "%03x", adc_result);
    lcd_puts(&result[0]);
    uart_puts(&result[0]);


    //uart_putc(0x0D);



}