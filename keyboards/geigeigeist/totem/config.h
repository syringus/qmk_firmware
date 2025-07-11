// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define SERIAL_USART_FULL_DUPLEX  // Enable full duplex operation mode
#define SERIAL_USART_TX_PIN GP0   // USART TX pin
#define SERIAL_USART_RX_PIN GP1   // USART RX pin
#define SERIAL_USART_PIN_SWAP     // Swap TX and RX pins if keyboard is master halve
#define EE_HANDS // Store handedness in EEPROM

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U // Timeout window in ms in which the double tap can occur
