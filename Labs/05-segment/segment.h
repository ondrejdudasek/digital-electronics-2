
#ifndef SEGMENT_H
#define SEGMENT_H


/**
 * @name Definition of SSD interface 
 * @note Multi-function shield based pins
 **/

#define SEGMENT_LATCH   PD4
#define SEGMENT_CLK     PD7
#define SEGMENT_DATA    PB0

/**
 * @file    segment.h
 * @brief   7segment library for arduino multi-shield
 **/

/**
 * @brief   Configure SSD signals LATCH, CLK, and DATA as output
 * @arg     void
 * @return  void
 **/
void SEG_init(void);

/**
 * @brief  	Display segments at one position of the SSD
 * @arg segments 
 * @arg position
 **/
void SEG_update_shift_regs(uint8_t segments, uint8_t position);

/**
 * @brief 	Turn off all segments at all positions of the SSD
 **/
void SEG_clear(void);

/**
 * @brief 	Generate one CLK signal period with a duration of 2 us
 **/
void SEG_clk_2us(void);


#endif