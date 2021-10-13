
# Lab 03 - GPIO
## Preparation tasks
### 1. C data types

| Data type | Number of bits |      Range     | Description |
|    :-:    |       :-:      |       :-:      |     :-:     |
|  uint8_t  |        8       |      0 ~ 255   | unsigned 8b integer |
|   int8_t  |        8       |   -127 ~ 255   | signed 8b integer |
| uint16_t  |        16      |      0 ~ 65535 | unsigned 16b integer |
|  int16_t  |        16      | -32767 ~ 32768 | signed 16b integer |
|   float   |        32      | -3.4e+38, ..., 3.4e+38 | Single-precision floating-point |
|    void   |        0       |        ~       |  empty variable, used mostly for defining functions without return values or pointers |

### 2. sample program
````c

#include <avr/io.h>

// Function declaration (prototype)
uint16_t calculate(uint8_t x, uint8_t y);

int main(void)
{
    uint8_t a = 156;
    uint8_t b = 14;
    uint16_t c;

    // Function call
    c = calculate(a, b);

    while (1)
    {
    }
    return 0;
}

// Function definition (body)
uint16_t calculate(uint8_t x, uint8_t y)
{
    uint16_t result;    // result = x^2 + 2xy + y^2

    result = x*x + 2*x*y + y*y; // Possible overflow here
    return result;
}

````

## Library header file