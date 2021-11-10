# Lab 7: Ondrej Dudasek

Link to this file in your GitHub repository:

[https://github.com/ondrejdudasek/digital-electronics-2/tree/main/Labs/06-lcd](https://github.com/ondrejdudasek/digital-electronics-2/tree/main/Labs/06-lcd)

### Analog-to-Digital Conversion

1. Complete table with voltage divider, calculated, and measured ADC values for all five push buttons.

   | **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** |
   | :-: | :-: | :-: | :-: |
   | Right  | 0 V | 0   | 0 |
   | Up     | 0.495 V | 101 | 95 |
   | Down   | 1.203 V |  246 | 237 |
   | Left   | 1.970 V |  403 | 423 |
   | Select | 3.182 V |  651 | 632 |
   | none   | 5V      | 1023 | 1023 |
   // 409 

2. Code listing of ACD interrupt service routine for sending data to the LCD/UART and identification of the pressed button. Always use syntax highlighting and meaningful comments:

```c
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
}
```

### UART communication

1. (Hand-drawn) picture of UART signal when transmitting three character data `De2` in 4800 7O2 mode (7 data bits, odd parity, 2 stop bits, 4800&nbsp;Bd).

   ![uart_de2.webp](uart_de2.webp)

2. Flowchart figure for function `uint8_t get_parity(uint8_t data, uint8_t type)` which calculates a parity bit of input 8-bit `data` according to parameter `type`. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![de2-lab7-flowchart1.png](de2-lab7-flowchart1.png)

### Temperature meter

Consider an application for temperature measurement and display. Use temperature sensor [TC1046](http://ww1.microchip.com/downloads/en/DeviceDoc/21496C.pdf), LCD, one LED and a push button. After pressing the button, the temperature is measured, its value is displayed on the LCD and data is sent to the UART. When the temperature is too high, the LED will start blinking.

1. Scheme of temperature meter. The image can be drawn on a computer or by hand. Always name all components and their values.

   ![temperature_meter.png](temperature_meter.png)
