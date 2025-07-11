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
#define LT_BSPC LT(U_NUM, KC_BSPC)
#define LT_ENT LT(U_SYM, KC_ENT)
#define LT_Z LT(U_BUTTON, KC_Z)
#define LT_SLSH LT(U_BUTTON, KC_SLSH)

// LAYERS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [U_BASE] = LAYOUT(
                 KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
                 MT_A,    MT_S,    MT_D,    MT_F,    KC_G,                          KC_H,    MT_J,    MT_K,    MT_L,    MT_SCLN,
        KC_NO,   LT_Z,    MT_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, MT_DOT,  LT_SLSH, KC_NO,
                                            LT_ESC,  LT_SPC,  LT_TAB,     LT_ENT,   LT_BSPC, KC_DEL
    ),
    [U_NAV] = LAYOUT(
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                         KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,CW_TOGG,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_NO,
                                            KC_NO,   KC_NO,   KC_NO,      KC_ENT,   KC_BSPC, KC_DEL
    ),
    [U_MOUSE] = LAYOUT(
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                         MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO,   KC_NO,
                                            KC_NO,   KC_NO,   KC_NO,      MS_BTN2,  MS_BTN1, MS_BTN3
    ),
    [U_MEDIA] = LAYOUT(
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                         KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                            KC_NO,   KC_NO,   KC_NO,      KC_MSTP,  KC_MPLY, KC_MUTE
    ),
    [U_BUTTON] = LAYOUT(
                 U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO,                         U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                         KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_NO,   U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO,                         U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   KC_NO,
                                            MS_BTN3, MS_BTN1, MS_BTN2,    MS_BTN2,  MS_BTN1, MS_BTN3
    ),
    [U_NUM] = LAYOUT(
                 KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                        KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_NO,   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS,                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                            KC_DOT,  KC_0,    KC_MINS,    KC_NO,    KC_NO,   KC_NO
    ),
    [U_SYM] = LAYOUT(
                 KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                       KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_NO,   KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                            KC_LPRN, KC_RPRN, KC_UNDS,    KC_NO,    KC_NO,   KC_NO
    )
};
