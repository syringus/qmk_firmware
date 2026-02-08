// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define SERIAL_USART_FULL_DUPLEX  // Enable full duplex operation mode
#define SERIAL_USART_TX_PIN GP0   // USART TX pin
#define SERIAL_USART_RX_PIN GP1   // USART RX pin
#define SERIAL_USART_PIN_SWAP     // Swap TX and RX pins if keyboard is master halve
#define EE_HANDS // Store handedness in EEPROM
#define SPLIT_WATCHDOG_ENABLE

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U // Timeout window in ms in which the double tap can occur

// TAP_CODE_DELAY for LT taps to work in games
#define TAP_CODE_DELAY 50

// RGB Light - underglow
// https://docs.qmk.fm/features/rgblight
#define WS2812_DI_PIN GP12 // Neopixel LED DIN (https://wiki.seeedstudio.com/XIAO-RP2040/)
#define RGBLIGHT_LED_COUNT 1
#define RGBLIGHT_DEFAULT_ON false
#define RGBLIGHT_DEFAULT_VAL 0
#define RGBLIGHT_DEFAULT_SAT 0
#define RGBLIGHT_DEFAULT_HUE 169
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL // meni farbu pekne pomaly
// #define RGBLIGHT_EFFECT_TWINKLE // pulzovanie s roznymi farbami a periodami
#define RGBLIGHT_SPLIT
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_RETAIN_VAL // retain brightness when changing layers
#define SPLIT_LAYER_STATE_ENABLE
