/*
 * Copyright (c) 2017, Sergey Kiselev
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* SSD1306_I2C == 1 - use I2C, SSD1306_I2C == 0 - use SPI */
#define SSD1306_I2C		0

/* Display resolution - modify according to the display type */
#define SSD1306_LCD_WIDTH	96 /* 128 */
#define SSD1306_LCD_HEIGHT	40 /* 64 */

/* I2C settings */
#define SSD1306_I2C_ADDR	0x3C
#define SSD1306_I2C_RETRY_COUNT	5

/* SPI settings */
#define SSD1306_SPI_BUS		QM_SPI_MST_0
#define SSD1306_SPI_SS		QM_SPI_SS_0

/* GPIO settings */
#define SSD1306_GPIO_CSN	0	/* D2000 - F0,  D2000 CRB pin #10 (SS0) */
#define SSD1306_GPIO_RST	9	/* D2000 - F9,  D2000 CRB pin #8  */
#define SSD1306_GPIO_DC		24	/* D2000 - F24, D2000 CRB pin #9 (PWM1) */

#define SSD1306_MODE_CMD	0x80
#define SSD1306_MODE_DATA	0x40

#define SSD1306_CMD_ADDR_MODE		0x20
#define SSD1306_CMD_SET_COLUMN_ADDR	0x21
#define SSD1306_CMD_SET_PAGE_ADDR	0x22
#define SSD1306_CMD_SET_START_LINE	0x40
#define SSD1306_CMD_SET_CONTRAST	0x81
#define SSD1306_CMD_SET_CHARGEPUMP	0x8D
#define SSD1306_CMD_SET_SEGMENT_REMAP	0xA1
#define SSD1306_CMD_DISPLAY_ALL_ON_RES	0xA4
#define SSD1306_CMD_NORMAL		0xA6
#define SSD1306_CMD_SET_MUX		0xA8
#define SSD1306_CMD_DISPLAY_OFF		0xAE
#define SSD1306_CMD_DISPLAY_ON		0xAF
#define SSD1306_CMD_SET_COM_SCAN_INC	0xC0
#define SSD1306_CMD_SET_COM_SCAN_DEC	0xC8
#define SSD1306_CMD_SET_OFFSET		0xD3
#define SSD1306_CMD_SET_CLK_DIV		0xD5
#define SSD1306_CMD_SET_PRECHARGE	0xD9
#define SSD1306_CMD_SET_COM_PINS	0xDA
#define SSD1306_CMD_SET_VCOM_DESELECT	0xDB
#define SSD1306_CMD_PAGE_START_ADDR	0xB0
#define SSD1306_CMD_COLUMN_LOW_ADDR	0x00
#define SSD1306_CMD_COLUMN_HIGH_ADDR	0x10
#define SSD1306_ADDR_MODE_HORIZ	0
#define SSD1306_ADDR_MODE_VERT	1
#define SSD1306_ADDR_MODE_PAGE	2

int ssd1306_init();

int ssd1306_set_addr_mode(uint8_t);

int ssd1306_set_cursor(uint8_t row, uint8_t column);

int ssd1306_clear();

int ssd1306_putc(uint8_t c);

int ssd1306_puts(char string[]);
