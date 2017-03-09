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

#include <clk.h>
#include <qm_common.h>
#include <qm_gpio.h>
#include <qm_i2c.h>
#include <qm_pinmux.h>
#include <qm_spi.h>
#include "ssd1306.h"

#define SPI_BUS         SSD1306_SPI_BUS
#define SPI_CLOCK_DIV   (32)    /* 1 MHz using 32 MHz system clock */


#if SSD1306_I2C == 1
/* Setup I2C bus */
void setup()
{
	static const qm_i2c_config_t i2c_cfg = {
		.address_mode	= QM_I2C_7_BIT,		/* 7 bit address */
		.mode			= QM_I2C_MASTER,	/* master mode */
		.speed			= QM_I2C_SPEED_STD,	/* ~111 kHz clock */
	};
	/* Setup pin muxes */
	qm_pmux_select(QM_PIN_ID_6, QM_PMUX_FN_2);	/* I2C - SCL */
	qm_pmux_select(QM_PIN_ID_7, QM_PMUX_FN_2);	/* I2C - SDA */

	/*  Enable I2C master 0 clock */
	clk_periph_enable(CLK_PERIPH_I2C_M0_REGISTER | CLK_PERIPH_CLK);

	/* Initialize I2C */
	qm_i2c_set_config(QM_I2C_0, &i2c_cfg);

}
#else
/* Setup GPIOs and SPI bus */
void setup()
{
  	static qm_gpio_port_config_t gpio_cfg = {
		.direction	= 	BIT(SSD1306_GPIO_CSN) |	/* SSD1306 - CS */
						BIT(SSD1306_GPIO_RST) |	/* SSD1306 - RST */
						BIT(SSD1306_GPIO_DC),	/* SSD1306 - D/C */
		.int_en			= 0x0,
		.int_type		= 0x0,
		.int_polarity	= 0x0,
		.int_debounce	= 0x0,
		.int_bothedge	= 0x0,
		.callback		= NULL,
	};
	static qm_spi_config_t spi_cfg = {
		.frame_size		= QM_SPI_FRAME_SIZE_8_BIT,
		.transfer_mode	= QM_SPI_TMOD_TX_RX,
		.bus_mode		= QM_SPI_BMODE_0,
		.clk_divider	= SPI_CLOCK_DIV,
	};
	/* Setup pin muxes */
	/* Use GPIO for slave select due to bug in DesignWare SPI */
	/* qm_pmux_select(QM_PIN_ID_0, QM_PMUX_FN_2);*/	/* SPI - SS0 */
	qm_pmux_select(QM_PIN_ID_16, QM_PMUX_FN_2);	/* SPI - SCK */
	qm_pmux_select(QM_PIN_ID_17, QM_PMUX_FN_2);	/* SPI - MOSI */
	qm_pmux_select(QM_PIN_ID_18, QM_PMUX_FN_2);	/* SPI - MISO */
	qm_pmux_input_en(QM_PIN_ID_18, true);		/* MISO is an input */

  	/* Initialize GPIO pins */
	qm_gpio_set_config(QM_GPIO_0, &gpio_cfg);

	/* Enable SPI master 0 clock */
	clk_periph_enable(CLK_PERIPH_CLK | CLK_PERIPH_SPI_M0_REGISTER);

	/* Initialize SPI */
	qm_spi_set_config(SPI_BUS, &spi_cfg);

	/* Configure SPI chip selects - not really needed since we use GPIOs */
	qm_spi_slave_select(SPI_BUS, SSD1306_SPI_SS);
}
#endif

int main()
{
	int row, column;
	QM_PRINTF("SSD1306 OLED Display Sample\r\n");

#if SSD1306_I2C == 1
	QM_PRINTF("Using I2C interface\r\n");
#else
	QM_PRINTF("Using SPI interface\r\n");
#endif

	/* Configure Quark I/O */
	setup();

	ssd1306_init();
	QM_PRINTF("SSD1306: Display initialized\r\n");

	ssd1306_clear();

	/* Fill the display with digits */
	for (row = 0; row < SSD1306_LCD_HEIGHT / 8; row++) {
		ssd1306_set_cursor(row, 0);
		for (column = 0; column < SSD1306_LCD_WIDTH / 6; column++) {
			ssd1306_putc('0' + (column + row ) % 10);
		}
	}

	/* Position the text on the middle of the display */
	row = ((SSD1306_LCD_HEIGHT / 8) - 4) / 2;
	column = ((SSD1306_LCD_WIDTH / 6) - 10) / 2;
	ssd1306_set_cursor(row, column);
	ssd1306_puts("  SSD1306 ");
	ssd1306_set_cursor(row + 1, column);
	ssd1306_puts("   OLED   ");
	ssd1306_set_cursor(row + 2, column);
	ssd1306_puts("  Display ");
	ssd1306_set_cursor(row + 3, column);
	ssd1306_puts("  Sample  ");

	return 0;
}
