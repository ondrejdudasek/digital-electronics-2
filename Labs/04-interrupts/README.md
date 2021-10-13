
# Lab 04 - Interrupts
## Preparation tasks

![equation](timer_overflow.png)

|   Module  |   Number of bits  |   1   |   8   |   32  |   64  |  128  |  256  |  1024  |
|    :=:    |         :=:       |  :=:  |  :=:  |  :=:  |  :=:  |  :=:  |  :=:  |   :=:  |
|    TC0    |          8        |  16u  |  128u |  512u | 1024u | 2048u | 4096u | 16384u |
|    TC1    |          16       | 4096u | 32.768m | 131.072m | 262.144m | 524.288m | 1.048576s | 4.194304s | 
|    TC2    |          8        |  16u  |  128u |  512u | 1024u | 2048u | 4096u | 16384u |

### Multi function shield

|  Device  | pin | Notes |
|    :=:   | :=: |  :=:  |
|   D1      |  PB5  | Inverted |
|   D2      |  PB4  | Inverted |
|   D3      |  PB3  | Inverted |
|   D4      |  PB2  | Inverted |
| S1-A1     |  PC1  | High = open |
| S2-A2     |  PC2  | High = open |
| S3-A3     |  PC3  | High = open |

## Pooling and interrupts

| **Program address** | **Source** | **Vector name** | **Description** |
| :-: | :-- | :-- | :-- |
| 0x0000 | RESET | -- | Reset of the system |
| 0x0002 | INT0  | `INT0_vect` | External interrupt request number 0 |
| 0x0004 | INT1 |  |  |
| 0x0006 | PCINT0 |  |  |
| 0x0008 | PCINT1 |  |  |
| 0x000A | PCINT2 |  |  |
| 0x000C | WDT |  |  |
| 0x0012 | TIMER2_OVF |  |  |
| 0x0018 | TIMER1_COMPB | `TIMER1_COMPB_vect` | Compare match between Timer/Counter1 value and channel B compare value |
| 0x001A | TIMER1_OVF | `TIMER1_OVF_vect` | Overflow of Timer/Counter1 value |
| 0x0020 | TIMER0_OVF |  |  |
| 0x0028 | USART_RX |  |  |
| 0x002A | ADC |  |  |
| 0x0030 | TWI |  |  |

## PWM

| **Module** | **Description** | **MCU pin** | **Arduino pin** |
| :-: | :-: | :-: | :-: |
| Timer/Counter0 | OC0A | PD6 | 6 |
|                | OC0B | PD5 | 5 |
| Timer/Counter1 | OC1A | PB1 | 9 |
|                | OC1B | PB2 | 10 |
| Timer/Counter2 | OC2A | PB3 | 11 |
|                | OC2B | PD3 | 3 |
