/*
 *  TP-LINK EAP115 board support
 *
 * Copyright (C) 2016 Henryk Heisig <hyniu@o2.pl>
 * Copiright (C) 2017 Serg Studzinskii <serguzhg@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <asm/mach-ath79/ath79.h>
#include <asm/mach-ath79/ar71xx_regs.h>

#include "common.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "dev-wmac.h"
#include "machtypes.h"

#define EAP115_SSR_CP	11
#define EAP115_SSR_DS	12

#define EAP115_GPIO_LED_ALL	4
#define EAP115_GPIO_LED_YEL	13
#define EAP115_GPIO_LED_GRN	14
#define EAP115_GPIO_LED_RED	16
#define EAP115_GPIO_BTN_RESET	17

#define EAP115_KEYS_POLL_INTERVAL	20 /* msecs */
#define EAP115_KEYS_DEBOUNCE_INTERVAL	(3 * EAP115_KEYS_POLL_INTERVAL)

#define EAP115_LAN_PHYADDR		4

static struct gpio_led eap115_leds_gpio[] __initdata = {
	{
		.name		= "eap115:red:system",
		.gpio		= EAP115_GPIO_LED_RED,
		.active_low	= 0,
	}, {
		.name		= "eap115:yellow:system",
		.gpio		= EAP115_GPIO_LED_YEL,
		.active_low	= 0,
	}, {
		.name		= "eap115:green:system",
		.gpio		= EAP115_GPIO_LED_GRN,
		.active_low	= 0,
	}, {
		.name		= "eap115:all:off",
		.gpio		= EAP115_GPIO_LED_ALL,
		.active_low	= 1,
	}
};

static struct gpio_keys_button eap115_gpio_keys[] __initdata = {
	{
		.desc		= "Reset button",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = EAP115_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= EAP115_GPIO_BTN_RESET,
		.active_low	= 1,
	}
};

static void __init eap_setup(u8 *mac)
{
	ath79_device_reset_clear(QCA953X_RESET_ETH_SWITCH_ANALOG);
	ath79_register_leds_gpio(-1, ARRAY_SIZE(eap115_leds_gpio),
				 eap115_leds_gpio);

	ath79_register_gpio_keys_polled(1, EAP115_KEYS_POLL_INTERVAL,
					ARRAY_SIZE(eap115_gpio_keys),
					eap115_gpio_keys);

	ath79_register_m25p80(NULL);

	ath79_register_mdio(0, 0x0);
	ath79_setup_ar934x_eth_cfg(AR934X_ETH_CFG_SW_ONLY_MODE); //phy4->switch->gmac1
	/* init GMAC1 */
	ath79_init_mac(ath79_eth1_data.mac_addr, mac, 1);
	ath79_eth1_data.phy_if_mode = PHY_INTERFACE_MODE_GMII;
	ath79_register_eth(1);
}

static void __init eap115_setup(void)
{
	u8 *mac = (u8 *) KSEG1ADDR(0x1f030008);
	u8 *ee = (u8 *) KSEG1ADDR(0x1fff1000);

	eap_setup(mac);

	ath79_register_wmac(ee, mac);
}

MIPS_MACHINE(ATH79_MACH_EAP115, "EAP115", "TP-LINK EAP115",
		eap115_setup);

