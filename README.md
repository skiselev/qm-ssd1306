# qm-ssd1306
SSD1306 OLED Display Driver for Intel(r) QMSI 

## Introduction
This driver provides support for OLED displays based on SSD1306 controller
for projects developed using Intel(r) Quark(tm) Microcontroller Software Interface (aka QMSI).
The driver supports text output using 6x8 font. Graphics output is not supported yet.
The driver supports displays with SPI and I2C interfaces.

## Hardware Configuration

### Supported OLED displays
This driver has been tested with the following displays:
* [Adafruit Monochrome 1.3" 128x64 OLED graphic display; Product ID: 938](https://www.adafruit.com/product/938)
* [MikroElektronika OLED W click (96x39 resolution); Product ID: MIKROE-1649](https://shop.mikroe.com/click/display/oled-w)
* A generic 0.96" 128x64 OLED display with 4-pin I2C header from a Chinese eBay seller
* A generic 0.96" 128x64 OLED display (blue and yellow) with 7-pin SPI header from a Chinese eBay seller

It is likely that it will work with other SSD1306-based displays with no or little modifications

### Wiring - I2C Interface
| Signal Name        | OLED Pin Name | Intel(r) Quark(tm) D2000 Board Pin Name | Notes                            |
|--------------------|---------------|-----------------------------------------|----------------------------------|
| Ground             | GND           | GND                                     |                                  |
| Power Supply, 5V   | VCC, Vin      | 5V                                      |                                  |
| Power Supply, 3.3V | 3.3V          | 3.3V                                    | MikroElektronika OLED Click only |
| I2C Data           | SDA, Data     | A4 or SDA                               |                                  |
| I2C Clock          | SCL, Clk      | A5 or SCL                               |                                  |

Note that Adafruit 128x64 OLED and MikroElektronika OLED Click displays come preconfigured to work in SPI mode. It is needed to re-configure them for I2C mode by soldering jumpers (Adafruit) or moving 0 ohm resistors (MikroElektronika OLED Click).

### Wiring - SPI Interface
| Signal Name        | OLED Pin Name | Intel(r) Quark(tm) D2000 Board Pin Name | Notes                            |
|--------------------|---------------|-----------------------------------------|----------------------------------|
| Ground             | GND           | GND                                     |                                  |
| Power Supply, 5V   | VCC, Vin      | 5V                                      |                                  |
| Power Supply, 3.3V | 3.3V          | 3.3V                                    | MikroElektronika OLED Click only |
| SPI MOSI           | SDI, Data, D1 | 11 (MOSI)                               |                                  |
| SPI Clock          | SCK, Clk, D0  | 13 (SCK)                                |                                  |
| SPI Chip Select    | CS            | 10 (SS0)                                |                                  |
| OLED Reset         | RST, Rst, RES | 8                                       |                                  |
| OLED Data/Control  | D/C, DC       | 9 (PWM1)                                |                                  |

## Using the Driver

### Building the Sample Application
1. Create a new QMSI based project, for example using Intel(r) System Studio for Microcontrollers
2. Copy *main.c*, *ssd1306.h*, and *ssd1306.c* files to your project directory
3. Build and run the project

### Integrating the Driver in Your Application

1. Create a new QMSI based project, for example using Intel(r) System Studio for Microcontrollers
2. Copy *ssd1306.h* and *ssd1306.c* files to your project directory
3. Add `include "ssd1306.h"` line in your main.c
4. Edit *ssd1306.h*.
..* Set `SSD1306_I2C` to '1' if using I2C interface, or to '0' if using SPI interface
..* Set display resolution - `SSD1306_LCD_WIDTH` and `SSD1306_LCD_HEIGHT` to match your display configuration
5. Add I2C or SPI initialization code. Refer to `setup()` function in *main.c* included with this driver.
6. From your code call `ssd1306_init()`, and then use other `ssd1306_*()` functions in your application as needed. Refer to *main.c* for usage example.
