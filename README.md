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

It is likely that it will work with other SSD1306-based displays with no or little modifications

### Wiring - I2C Interface
* OLED **GND** goes to Quark D2000 board **GND**
* OLED **VCC** or **Vin** goes to Quark D2000 board **5V**
* (MikroElektronika OLED click only) OLED **3.3V** goes to Quark D2000 board **3.3V**
* OLED **SDA** or **Data** goes to Quark D2000 board pin **A4** or **SDA**
* OLED **SCL** or **Clk** goes to Quark D2000 board pin **A5** or **SCL**

Note that Adafruit 128x64 OLED and MikroElektronika OLED Click displays come preconfigured to work in SPI mode. It is needed to re-configure them for I2C mode by soldering jumpers (Adafruit) or moving 0 ohm resistors (MikroElektronika OLED Click).

### Wiring - SPI Interface
* OLED **GND** goes to Quark D2000 board **GND**
* OLED **VCC** or **Vin** goes to Quark D2000 board **5V**
* (MikroElektronika OLED click only) OLED **3.3V** goes to Quark D2000 board **3.3V**
* OLED **SDI** or **Data** goes to Quark D2000 board pin **11 (MOSI)**
* OLED **SCK** or **Clk** goes to Quark D2000 board pin **13 (SCK)**
* OLED **CS** goes to Quark D2000 board pin **10 (SS0)**
* OLED **RST** or **Rst** goes to Quark D2000 board pin **8**
* OLED **D/C** or **DC** goes to Quark D2000 board pin **9 (PWM1)**

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
