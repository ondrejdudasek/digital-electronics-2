#ifndef LIBRARY_TIMER_H
#define LIBRARY_TIMER_H

/* Includes */
#include <avr/io.h>

/* Defines -----------------------------------------------------------*/
/**
 * @brief Defines prescaler CPU frequency values for Timer/Counter1.
 * @note  F_CPU = 16 MHz
 */

#define TIM0_stop()              TCCR0B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));          // 000 --> STOP
#define TIM0_overflow_16us()     TCCR0B &= ~((1<<CS12) | (1<<CS11)); TCCR0B |= (1<<CS10); // 001 --> 1
#define TIM0_overflow_128us()    TCCR0B &= ~((1<<CS12) | (1<<CS10)); TCCR0B |= (1<<CS11); // 010 --> 8
#define TIM0_overflow_1024us()   TCCR0B &= ~(1<<CS12);               TCCR0B |= (1<<CS11) | (1<<CS10);  // 011 --> 64
#define TIM0_overflow_4096us()   TCCR0B &= ~((1<<CS11) | (1<<CS10)); TCCR0B |= (1<<CS12); // 100 --> 256
#define TIM0_overflow_16384us()  TCCR0B &= ~(1<<CS11);               TCCR0B |= (1<<CS12) | (1<<CS10);  // 101 --> 1024

#define TIM1_stop()             TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));         // 000 --> STOP
#define TIM1_overflow_4ms()     TCCR1B &= ~((1<<CS12) | (1<<CS11)); TCCR1B |= (1<<CS10);// 001 --> 1
#define TIM1_overflow_33ms()    TCCR1B &= ~((1<<CS12) | (1<<CS10)); TCCR1B |= (1<<CS11);// 010 --> 8
#define TIM1_overflow_262ms()   TCCR1B &= ~(1<<CS12); TCCR1B |= (1<<CS11) | (1<<CS10);  // 011 --> 64
#define TIM1_overflow_1s()      TCCR1B &= ~((1<<CS11) | (1<<CS10)); TCCR1B |= (1<<CS12);// 100 --> 256
#define TIM1_overflow_4s()      TCCR1B &= ~(1<<CS11); TCCR1B |= (1<<CS12) | (1<<CS10);  // 101 --> 1024

/**
 * @brief Defines interrupt enable/disable modes for Timer/Counter1.
 */

#define TIM0_overflow_interrupt_enable()    TIMSK0 |= (1<<TOIE1);   // 1 --> enable
#define TIM0_overflow_interrupt_disable()   TIMSK0 &= ~(1<<TOIE1);  // 0 --> disable

#define TIM1_overflow_interrupt_enable()    TIMSK1 |= (1<<TOIE1);   // 1 --> enable
#define TIM1_overflow_interrupt_disable()   TIMSK1 &= ~(1<<TOIE1);  // 0 --> disable



#endif