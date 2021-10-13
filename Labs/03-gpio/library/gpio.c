

#include "gpio.h"
#include "avr/io.h"

void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name | (1 << pin_num);
}

void GPIO_config_input_nopull(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name & ~(1 << pin_num); // 0 in DDR register
    reg_name++; // PORTx register is 1 byte above DDRx register
    *reg_name = *reg_name & ~(1 << pin_num);
}


void GPIO_config_input_pullup(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name & ~(1 << pin_num); // 0 in DDR register
    reg_name++; // PORTx register is 1 byte above DDRx register
    *reg_name = *reg_name | (1 << pin_num);
}


void GPIO_write_low(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name & ~(1 << pin_num);
}


void GPIO_write_high(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name | (1 << pin_num);
}


void GPIO_toggle(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name ^ (1 << pin_num);

}   


uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num)
{
    return (*reg_name & (1 << pin_num));
}

