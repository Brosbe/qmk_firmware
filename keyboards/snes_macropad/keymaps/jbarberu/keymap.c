// Copyright 2023 John Barbero Unenge (@jbarberu)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum Layer {
    L_Numpad = 0,
    L_Symbols,
    L_EasyEDA,
    L_RGB,
    L_Adjust
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * Macropad Button Order
   * ┌───┬───┬───┬───┐
   * │ 7 │ 8 │ 9 │ - │
   * ├───┼───┼───┼───┤
   * │ 4 │ 5 │ 6 │ + │
   * ├───┼───┼───┼───┤
   * │ 1 │ 2 │ 3 │ 0 │
   * └───┴───┴───┴───┘
   *
   * SNES Button Order
   * ┌────────┬────────┬────────┬────────┐
   * │   LT   │   RT   │ START  │ SELECT │
   * ├────────┼────────┼────────┼────────┤
   * │   UP   │  DOWN  │  LEFT  │ RIGHT  │
   * ├────────┼────────┼────────┼────────┤
   * │   A    │   B    │   X    │   Y    │
   * └────────┴────────┴────────┴────────┘
   *
   */
  [L_Numpad] = LAYOUT(
      KC_P7,   KC_P8,   KC_P9,       TO(L_EasyEDA)
    , KC_P4,   KC_P5,   KC_P6,       LT(L_Symbols, KC_PCMM)
    , KC_P1,   KC_P2,   KC_P3,       KC_P0

    , KC_A,    KC_S,    KC_ENT,      KC_BSPC
    , KC_UP,   KC_DOWN, KC_LEFT,     KC_RIGHT
    , KC_X,    KC_Z,    LSFT(KC_F1), KC_TAB
  ),
  [L_EasyEDA] = LAYOUT(
      KC_COMM, KC_DOT,  KC_K,    TO(L_RGB)
    , KC_LSFT, KC_M,    KC_N,    TO(L_Numpad)
    , KC_LCTL, KC_SPC,  KC_DEL,  KC_BSPC

    , KC_A,    KC_B,    KC_C,    KC_D
    , QK_BOOT, KC_TRNS, KC_G,    KC_H
    , KC_I,    KC_J,    KC_K,    KC_L
  ),
  [L_RGB] = LAYOUT(
      RGB_M_P,  RGB_M_B, RGB_TOG, TO(L_Adjust)
    , RGB_MOD,  RGB_HUI, RGB_VAI, TO(L_Numpad)
    , RGB_RMOD, RGB_HUD, RGB_VAD, KC_NO

    , KC_A,    KC_B,    KC_C,    KC_D
    , KC_E,    KC_F,    KC_G,    KC_H
    , KC_I,    KC_J,    KC_K,    KC_L
  ),
  [L_Adjust] = LAYOUT(
      KC_NO,   KC_P8,   KC_NO,   KC_NO
    , KC_NO,   RGB_HUD, KC_NO,   TO(L_Numpad)
    , RGB_HUI, KC_NO,   KC_TRNS, KC_NO

    , KC_A,    KC_B,    KC_C,    KC_D
    , KC_E,    KC_F,    KC_G,    KC_H
    , KC_I,    KC_J,    KC_K,    KC_L
  ),
  [L_Symbols] = LAYOUT(
      KC_PPLS, KC_PMNS, KC_PEQL, KC_NO
    , KC_PAST, KC_PSLS, KC_ENT,  KC_TRNS
    , KC_NUM,  KC_NO,   KC_NO,   QK_BOOT

    , KC_A,    KC_B,    KC_C,    KC_D
    , KC_E,    KC_F,    KC_G,    KC_H
    , KC_I,    KC_J,    KC_K,    KC_L
  )
};
// clang-format on

const char * get_layer_name_user(int layer) {
    switch (layer) {
        case L_Numpad:
            return "Numpad";
        case L_EasyEDA:
            return "EasyEDA";
        case L_RGB:
            return "RGB Controls";
        case L_Adjust:
            return "Adjust";
        case L_Symbols:
            return "Symbols";
        default:
            return "Undef";
    }
}
