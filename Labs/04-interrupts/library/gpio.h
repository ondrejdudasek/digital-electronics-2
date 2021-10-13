/**
 * @file 
 * @code #include "gpio.h" @endcode
 *
 * @brief GPIO library for AVR-GCC.
 */

#ifndef GPIO_GPIO_H
#define GPIO_GPIO_H

#include <stdint.h>

/**
 * @name Functions
 */


/**
 * @brief  Configure one output pin in Data Direction Register.
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  pin_num  Pin designation in the interval 0 to 7
 * @return none
 */
void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num);


/**
 * @brief Configure one input pin in DDR without pull-up resistor
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  pin_num Pin number in register, such as 3
 * @return none
 */
void GPIO_config_input_nopull(volatile uint8_t *reg_name, uint8_t pin_num);

/**
 * @brief Configure one input pin in DDR and enable pull-up resistor
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  pin_num Pin number in register, such as 3
 * @return none
 */
void GPIO_config_input_pullup(volatile uint8_t *reg_name, uint8_t pin_num);

/**
 * @brief Set one output pin in PORT register to low
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  pin_num Pin number in register, such as 3
 * @return none
 */
void GPIO_write_low(volatile uint8_t *reg_name, uint8_t pin_num);

/**
 * @brief Set one output pin in PORT register to high
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  pin_num Pin number in register, such as 3
 * @return none
 */
void GPIO_write_high(volatile uint8_t *reg_name, uint8_t pin_num);

/**
 * @brief  Toggle one output pin value in PORT register
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  pin_num Pin number in register, such as 3
 * @return none
 */
void GPIO_toggle(volatile uint8_t *reg_name, uint8_t pin_num);

/**
 * @brief Get input pin value from PIN register
 * @param  reg_name Address of Data Direction Register, such as &DDRB
 * @param  pin_num Pin number in register, such as 3
 * @return Masked value of register
 */
uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num);

#endif