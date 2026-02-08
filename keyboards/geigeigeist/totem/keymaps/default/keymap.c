// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Miryoku QWERTY layout with shifted navigation keys as in vim.
//   https://github.com/manna-harbour/miryoku

#include QMK_KEYBOARD_H

// LED pins on XIAO RP2040
#define LED_USER_BLUE       GP25
#define LED_USER_GREEN      GP16
#define LED_USER_RED        GP17
#define LED_NEOPIX_PWR      GP11  // Neopixel LED power (https://wiki.seeedstudio.com/XIAO-RP2040/)

static bool is_suspended;

// Layers definition
#if !defined(LAYERS)
    #define LAYERS \
        LAYER_X(BASE) \
        LAYER_X(NAV) \
        LAYER_X(MOUSE) \
        LAYER_X(BUTTON) \
        LAYER_X(MEDIA) \
        LAYER_X(NUM) \
        LAYER_X(SYM) \
        LAYER_X(FUN) \
        LAYER_X(TILE) \
        LAYER_X(GAME) \
        LAYER_X(GAME2)
#endif
enum layers {
#define LAYER_X(LAYER) U_##LAYER,
    LAYERS
#undef LAYER_X
};

// KEY DEFINITIONS
// Home mod
#define MT_S MT(MOD_LALT, KC_S)
#define MT_D MT(MOD_LCTL, KC_D)
#define MT_F MT(MOD_LSFT, KC_F)
#define MT_J MT(MOD_RSFT, KC_J)
#define MT_K MT(MOD_LCTL, KC_K)
#define MT_L MT(MOD_LALT, KC_L)
#define MT_X MT(MOD_RALT, KC_X)
#define MT_DOT MT(MOD_RALT, KC_DOT)
// Custom
#define MT_BSPC MT(MOD_LSFT, KC_BSPC)
#define U_RDO LCTL(KC_Y) // Redo
#define U_PST LCTL(KC_V) // Paste
#define U_CPY LCTL(KC_C) // Copy
#define U_CUT LCTL(KC_X) // Cut
#define U_UND LCTL(KC_Z) // Undo
#define U_CTD LCTL(KC_D) // Ctrl+D
// Layer switching
#define LT_ESC LT(U_MEDIA, KC_ESC)
#define LT_SPC LT(U_NAV, KC_SPC)
#define LT_TAB LT(U_MOUSE, KC_TAB)
#define LT_BSPC LT(U_NUM, KC_BSPC)
#define LT_ENT LT(U_SYM, KC_ENT)
#define LT_DEL LT(U_FUN, KC_DEL)
#define LT_Z LT(U_BUTTON, KC_Z)
#define LT_SLSH LT(U_BUTTON, KC_SLSH)
#define MO_GAME2 MO(U_GAME2)
// Tap dance
#define TD_BASE TD(TD_U_BASE)
#define TD_NAV TD(TD_U_NAV)
#define TD_MOUSE TD(TD_U_MOUSE)
#define TD_BUTTON TD(TD_U_BUTTON)
#define TD_MEDIA TD(TD_U_MEDIA)
#define TD_NUM TD(TD_U_NUM)
#define TD_SYM TD(TD_U_SYM)
#define TD_FUN TD(TD_U_FUN)
#define TD_GAME TD(TD_U_GAME)

// COMBOS
// Send GUI when LT_SPC+A or LT_BSPC+' is pressed.
const uint16_t PROGMEM gui_combo_left[] = {LT_SPC, KC_A, COMBO_END};
const uint16_t PROGMEM gui_combo_right[] = {LT_BSPC, KC_QUOT, COMBO_END};
combo_t key_combos[] = {
    COMBO(gui_combo_left, KC_LGUI),
    COMBO(gui_combo_right, KC_LGUI),
};

// TAP DANCE
enum {
#define LAYER_X(LAYER) TD_U_##LAYER,
    LAYERS
#undef LAYER_X
};
// The TD_<layer> key needs to be pressed twice to switch layer.
#define LAYER_X(LAYER) \
    void td_u_##LAYER(tap_dance_state_t *state, void *user_data) { \
        if (state->count == 2) { \
            default_layer_set((layer_state_t)1 << U_##LAYER); \
        } \
    }
    LAYERS
#undef LAYER_X
tap_dance_action_t tap_dance_actions[] = {
#define LAYER_X(LAYER) \
    [TD_U_##LAYER] = ACTION_TAP_DANCE_FN(td_u_##LAYER),
    LAYERS
#undef LAYER_X
};

// CUSTOM KEYCODES
enum custom_keycodes {
    CK_TILE = SAFE_RANGE,
    CK_ALT_F4,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CK_TILE:
        if (record->event.pressed) {
            layer_on(U_TILE);
            register_code(KC_F24);
        } else {
            unregister_code(KC_F24);
            layer_off(U_TILE);
        }
        break;
    case CK_ALT_F4:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(SS_TAP(X_F4)));
        }
        break;
    }
    return true;
}

// LAYERS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [U_BASE] = LAYOUT(
                 KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
                 KC_A,    MT_S,    MT_D,    MT_F,    KC_G,                          KC_H,    MT_J,    MT_K,    MT_L,    KC_QUOT,
        CK_TILE, LT_Z,    MT_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, MT_DOT,  LT_SLSH, CK_TILE,
                                            LT_ESC,  LT_SPC,  LT_TAB,     LT_ENT,   LT_BSPC, LT_DEL
    ),
    [U_NAV] = LAYOUT(
                 KC_NO,   KC_NO,   KC_NO,   TD_BASE, KC_NO,                         U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                         KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,CW_TOGG,
        KC_NO,   KC_NO,   KC_NO,   TD_NUM,  TD_NAV,  KC_NO,                         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_NO,
                                            KC_NO,   KC_NO,   KC_NO,      KC_ENT,   KC_BSPC, KC_DEL
    ),
    [U_MOUSE] = LAYOUT(
                 KC_NO,   KC_NO,   KC_NO,   TD_BASE, KC_NO,                         U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                         MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, KC_NO,
        KC_NO,   CK_ALT_F4, KC_NO, TD_SYM,  TD_MOUSE,KC_NO,                         MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO,   KC_NO,
                                            KC_NO,   KC_NO,   KC_NO,      MS_BTN2,  MS_BTN1, MS_BTN3
    ),
    [U_MEDIA] = LAYOUT(
                 UG_TOGG, UG_NEXT, UG_HUEU, TD_BASE, UG_SPDU,                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                         KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO,
        KC_NO,   UG_SATU, UG_VALU, TD_FUN,  TD_MEDIA,KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                            KC_NO,   KC_NO,   KC_NO,      KC_MSTP,  KC_MPLY, KC_MUTE
    ),
    [U_BUTTON] = LAYOUT(
                 U_UND,   DM_REC1, DM_RSTP, DM_PLY1, U_RDO,                         U_RDO,   DM_PLY2, DM_RSTP, DM_REC2, U_UND,
                 KC_LGUI, KC_LALT, U_CTD,   KC_LSFT, KC_NO,                         KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_NO,   U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO,                         U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   KC_NO,
                                            MS_BTN3, MS_BTN1, MS_BTN2,    MS_BTN2,  MS_BTN1, MS_BTN3
    ),
    [U_NUM] = LAYOUT(
                 KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                       TD_GAME, TD_BASE, KC_NO,   KC_NO,   KC_NO,
                 KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                        KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        MT_BSPC, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS,                       KC_NO,   TD_NUM,  TD_NAV,  KC_NO,   KC_NO,   KC_NO,
                                            KC_DOT,  KC_0,    KC_MINS,    KC_NO,    KC_NO,   KC_NO
    ),
    [U_SYM] = LAYOUT(
                 KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                       KC_NO,   TD_BASE, KC_NO,   KC_NO,   KC_NO,
                 KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                       KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_NO,   KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,                       KC_NO,   TD_SYM,  TD_MOUSE,KC_NO,   KC_NO,   KC_NO,
                                            KC_LPRN, KC_RPRN, KC_UNDS,    KC_NO,    KC_NO,   KC_NO
    ),
    [U_FUN] = LAYOUT(
                 KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                       KC_NO,   TD_BASE, KC_NO,   KC_NO,   KC_NO,
                 KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,                       KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_NO,   KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS,                       KC_NO,   TD_FUN,  TD_MEDIA,KC_NO,   KC_NO,   KC_SLEP,
                                            KC_APP,  KC_SPC,  KC_TAB,     KC_NO,    KC_NO,   KC_NO
    ),
    [U_TILE] = LAYOUT(
                 KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
                 KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,
        CK_TILE, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, CK_TILE,
                                            KC_LSFT, KC_LALT, KC_LCTL,    KC_LCTL,  KC_LALT, KC_LSFT
    ),
    [U_GAME] = LAYOUT(
                 KC_TAB,  KC_Q,    KC_V,    KC_E,    KC_R,                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TAB,
                 KC_LSFT, KC_A,    KC_W,    KC_D,    KC_F,                          KC_NO,   KC_LEFT, KC_UP,   KC_RIGHT,KC_LSFT,
        KC_ESC,  KC_LCTL, KC_Z,    KC_S,    KC_X,    KC_C,                          KC_NO,   KC_NO,   KC_DOWN, KC_NO,   KC_LCTL, TD_BASE,
                                            KC_LALT, KC_SPC,  MO_GAME2,   MO_GAME2, KC_SPC,  KC_LALT
    ),
    [U_GAME2] = LAYOUT(
                 KC_HOME, KC_J,    KC_I,    KC_M,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
                 KC_ENT,  KC_4,    KC_5,    KC_6,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,
        KC_H,    KC_BSPC, KC_1,    KC_2,    KC_3,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LGUI,
                                            KC_NO,   KC_NO,   MO_GAME2,   MO_GAME2, KC_BSPC, KC_DEL
    )
};

void board_init(void) {
    gpio_set_pin_output(LED_NEOPIX_PWR);
    gpio_write_pin_high(LED_NEOPIX_PWR);
}

void suspend_power_down_user(void) {
    if (!is_suspended) {
        is_suspended = true;
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1); // sets mode to medium breathing without saving
    }
}

void suspend_wakeup_init_user(void) {
    is_suspended = false;
    rgblight_reload_from_eeprom();
}

const rgblight_segment_t PROGMEM rgb_left_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_TEAL}
);

const rgblight_segment_t PROGMEM rgb_right_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GOLD}
);

const rgblight_segment_t PROGMEM rgb_game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PURPLE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_left_layer,
    rgb_right_layer,
    rgb_game_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    if (layer_state_cmp(state, U_SYM) || (layer_state_cmp(state, U_NUM))
        || (layer_state_cmp(state, U_FUN))) {
        rgblight_set_layer_state(0, true);
    } else {
        rgblight_set_layer_state(0, false);
    }
    if (layer_state_cmp(state, U_MOUSE) || (layer_state_cmp(state, U_NAV))
        || (layer_state_cmp(state, U_MEDIA))) {
        rgblight_set_layer_state(1, true);
    } else {
        rgblight_set_layer_state(1, false);
    }
    rgblight_set_layer_state(2, layer_state_cmp(state, U_GAME));
    return state;
}
