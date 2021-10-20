
#include <stdint.h>
#include <avr/io.h>

#include "segment.h"
#include "gpio.h"
#include "util/delay.h"



/* Variables ---------------------------------------------------------*/
// Active-low digit 0 to 9
const uint8_t segment_value[] = {
    // abcdefgDP
    0b00000011,     // Digit 0
    0b10011111,     // Digit 1
    0b00100101,     // Digit 2
    0b00001101,     // Digit 3
    0b10011001,     // Digit 4
    0b01001001,     // Digit 5
    0b01000001,     // Digit 6
    0b00011111,     // Digit 7
    0b00000001,     // Digit 8
    0b00001001,     // Digit 9
    0b00010001,     // A
    0b11000001,     // b
    0b01100011,     // C
    0b10000101,     // d
    0b01100001,     // E
    0b01110001,     // F
    0b11111111      // off, [0x10]
};

// Active-high position 0 to 3
const uint8_t segment_position[] = {
    // p3p2p1p0....
    0b00010000,     // Position 0
    0b00100000,     // Position 1
    0b01000000,     // Position 2
    0b10000000      // position 3
};

void SEG_init(void)
{
    GPIO_config_output(&DDRD, SEGMENT_CLK);
    GPIO_config_output(&DDRB, SEGMENT_DATA);
    GPIO_config_output(&DDRD, SEGMENT_LATCH);
}

/*--------------------------------------------------------------------*/
/**
 * @brief Write segment value to position
 **/
void SEG_update_shift_regs(uint8_t segments, uint8_t position)
{
    uint8_t bit_number;
    segments = segment_value[segments];     // 0, 1, ..., 9
    position = segment_position[position];  // 0, 1, 2, 3

    GPIO_write_low(&PORTD, SEGMENT_LATCH);
    GPIO_write_low(&PORTD, SEGMENT_CLK);
    GPIO_write_low(&PORTB, SEGMENT_DATA);

    // control segments

    for (bit_number = 0; bit_number < 8; bit_number ++)
    {
        if((segments & 0b1) == 0)
        {
            // Segment bit is 0
            GPIO_write_low(&PORTB, SEGMENT_DATA);
        } else {
            // Segment bit is not zero
            GPIO_write_high(&PORTB, SEGMENT_DATA);
        }
        SEG_clk_2us();
        segments = segments >> 1;
    }

    for (bit_number = 0; bit_number < 8; bit_number ++)
    {
        if((position & 0b1) == 0)
        {
            // Segment bit is 0
            GPIO_write_low(&PORTB, SEGMENT_DATA);
        } else {
            // Segment bit is not zero
            GPIO_write_high(&PORTB, SEGMENT_DATA);
        }
        SEG_clk_2us();
        position = position >> 1;
    }

    GPIO_write_high(&PORTD, SEGMENT_LATCH);

    

}

void SEG_clear(void)
{
    SEG_update_shift_regs(0x10, 0);
}

void SEG_clk_2us(void)
{
    GPIO_write_low(&PORTD, SEGMENT_CLK);
    _delay_us(1);
    GPIO_write_high(&PORTD, SEGMENT_CLK);
    _delay_us(1);
    GPIO_write_low(&PORTD, SEGMENT_CLK);

}