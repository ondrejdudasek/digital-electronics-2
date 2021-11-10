# Lab 5: Ondrej Dudasek

Link to my `Digital-electronics-2` GitHub repository:

[https://github.com/ondrejdudasek/digital-electronics-2](https://github.com/ondrejdudasek/digital-electronics-2)

### 7-segment library

1. Describe difference between CC and CA SSD
   * Common cathode SSD: Common cathode 7-segment display has common negative voltage and each segment is activated by pulling anode to higher voltage than anode. 
   * Common anode SSD: Common anode 7-segment display has common positive voltage and each segment is activated by pulling cathode to the ground or lower-than-anode voltage.
2. Code listing with syntax highlighting of two interrupt service routines from counter application with at least two digits, ie. values from 00 to 59:

```c
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Increment counter value from 00 to 59.
 **********************************************************************/
uint8_t digit[2];
ISR(TIMER1_OVF_vect)
{
    static uint8_t timer;
    digit[1] = (timer/10) % 10;
    digit[0] = timer % 10;
    timer++;
    if(timer >= 60)
    {
        timer = 0;
    }

}
```

```c
/**********************************************************************
 * Function: Timer/Counter0 overflow interrupt
 * Purpose:  Display tens and units of a counter at SSD.
 **********************************************************************/
ISR(TIMER0_OVF_vect)
{
    static uint8_t position = 0; 
    SEG_update_shift_regs(digits[position], position);
    position++;
    if(position > 3)
    {
        position = 0;
    }
}
```

3. Flowchart figure for function SEG_clk_2us() which generates one clock period on SEG_CLK pin with a duration of 2 us. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.


![SEG.png](SEG.png)


### Kitchen alarm

Consider a kitchen alarm with a 7 segment display, one led and three push buttons: start, +1m, -1m. 
![kitchen_alarm.png](kitchen_alarm.png)
