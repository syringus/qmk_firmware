// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Miryoku QWERTY layout with shifted navigation keys as in vim.
//   https://github.com/manna-harbour/miryoku

#include QMK_KEYBOARD_H

// Layers definition
enum totem_layers {
    U_BASE,
    U_NAV,
    U_MOUSE,
    U_BUTTON,
    U_MEDIA,
    U_NUM,
    U_SYM,
    U_FUN,
    U_ADD,
};

// DEFINITIONS
// Home mod
#define MT_A MT(MOD_LGUI, KC_A)
#define MT_S MT(MOD_LALT, KC_S)
#define MT_D MT(MOD_LCTL, KC_D)
#define MT_F MT(MOD_LSFT, KC_F)
#define MT_J MT(MOD_RSFT, KC_J)
#define MT_K MT(MOD_LCTL, KC_K)
#define MT_L MT(MOD_LALT, KC_L)
#define MT_SCLN MT(MOD_LGUI, KC_SCLN)
#define MT_X MT(MOD_RALT, KC_X)
#define MT_DOT MT(MOD_RALT, KC_DOT)
// Custom
#define U_RDO LCTL(KC_Y) // Redo
#define U_PST LCTL(KC_V) // Paste
#define U_CPY LCTL(KC_C) // Copy
#define U_CUT LCTL(KC_X) // Cut
#define U_UND LCTL(KC_Z) // Undo
// Layer switching
#define LT_ESC LT(U_MEDIA, KC_ESC)
#define LT_SPC LT(U_NAV, KC_SPC)
#define LT_TAB LT(U_MOUSE, KC_TAB)

// LAYERS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [U_BASE] = LAYOUT(
                 KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
                 MT_A,    MT_S,    MT_D,    MT_F,    KC_G,                         KC_H,    MT_J,    MT_K,    MT_L,    MT_SCLN,
        KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, MT_DOT,  KC_SLSH, KC_NO,
                                            KC_ESC,  LT_SPC, LT_TAB,     KC_ENT,   KC_BSPC, KC_DEL
    ),
    [U_NAV] = LAYOUT(
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                        KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,CW_TOGG,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_NO,
                                            KC_NO,   KC_NO,  KC_NO,      KC_ENT,   KC_BSPC, KC_DEL
    ),
    [U_MOUSE] = LAYOUT(
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                        MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO,   KC_NO,
                                            KC_NO,   KC_NO,  KC_NO,      MS_BTN2,  MS_BTN1, MS_BTN3
    )
};
