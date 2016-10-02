/*
 * LP55XX Platform Data Header
 *
 * Copyright (C) 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * Derived from leds-lp5521.h, leds-lp5523.h
 */

#ifndef _LEDS_LP55XX_H
#define _LEDS_LP55XX_H

/* Clock configuration */
#define LP55XX_CLOCK_AUTO	0
#define LP55XX_CLOCK_INT	1
#define LP55XX_CLOCK_EXT	2

struct lp55xx_led_config {
	const char *name;
	const char *default_trigger; //NBQ - MaoyiChou - [NBQ-775] - [Cloud LED] Implement LP5523 driver.
	u8 chan_nr;
	u8 led_current; /* mA x10, 0 if led is not connected */
	u8 max_current;
};

struct lp55xx_predef_pattern {
	const u8 *r;
	const u8 *g;
	const u8 *b;
	u8 size_r;
	u8 size_g;
	u8 size_b;
};

/*  NBQ - MaoyiChou - [NBQ-775] - [Cloud LED] Implement LP5523 driver. */
enum lp8501_pwr_sel {
	LP8501_ALL_VDD,		/* D1~9 are connected to VDD */
	LP8501_6VDD_3VOUT,	/* D1~6 with VDD, D7~9 with VOUT */
	LP8501_3VDD_6VOUT,	/* D1~6 with VOUT, D7~9 with VDD */
	LP8501_ALL_VOUT,	/* D1~9 are connected to VOUT */
};

#define MAX_TRIGGER_PINES 6
/* end  NBQ - MaoyiChou - [NBQ-775] */

/*
 * struct lp55xx_platform_data
 * @led_config        : Configurable led class device
 * @num_channels      : Number of LED channels
 * @label             : Used for naming LEDs
 * @clock_mode        : Input clock mode. LP55XX_CLOCK_AUTO or _INT or _EXT
 * @setup_resources   : Platform specific function before enabling the chip
 * @release_resources : Platform specific function after  disabling the chip
 * @enable            : EN pin control by platform side
 * @patterns          : Predefined pattern data for RGB channels
 * @num_patterns      : Number of patterns
 * @update_config     : Value of CONFIG register
 */
struct lp55xx_platform_data {

	/* LED channel configuration */
	struct lp55xx_led_config *led_config;
	u8 num_channels;
	const char *label;

	/* Clock configuration */
	u8 clock_mode;

/*  NBQ - MaoyiChou - [NBQ-775] - [Cloud LED] Implement LP5523 driver. */
	/* optional enable GPIO */
	int enable_gpio;
//FIH, Hubert, 20151027, config trig_gpio and int_gpio {
	int trig_gpio;
	int int_gpio;
//} FIH, Hubert, 20151027, config trig_gpio and int_gpio

	/* optional trigger GPIOs */
	int trigger_gpio[MAX_TRIGGER_PINES];
/* end  NBQ - MaoyiChou - [NBQ-775] */

	/* Platform specific functions */
	int (*setup_resources)(void);
	void (*release_resources)(void);
	void (*enable)(bool state);

	/* Predefined pattern data */
	struct lp55xx_predef_pattern *patterns;
	unsigned int num_patterns;

/*  NBQ - MaoyiChou - [NBQ-775] - [Cloud LED] Implement LP5523 driver. */
	/* LP8501 specific */
	enum lp8501_pwr_sel pwr_sel;
/* end  NBQ - MaoyiChou - [NBQ-775] */
};

#endif /* _LEDS_LP55XX_H */
