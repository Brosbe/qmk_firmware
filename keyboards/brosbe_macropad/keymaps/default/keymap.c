// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

const uint16_t PROGMEM nextPage[] = {KC_MPRV, KC_MNXT, COMBO_END};
const uint16_t PROGMEM prevPage[] = {KC_MPLY, KC_MSTP, COMBO_END};
uint_fast8_t currentLayer = 0;
uint_fast8_t max_layer;

enum combos {
  NEXT_PAGE,
  PREV_PAGE,
};

enum layers {
    _1,
    _2,
    _DEV
};

combo_t key_combos[] = {
    [NEXT_PAGE] = COMBO(nextPage, KC_NO),
    [PREV_PAGE] = COMBO(prevPage, KC_NO)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┐
     * │ 1 │ 2 │
     * ├───┼───┤
     * │ 3 │ 4 │
     * └───┴───┘
     */
    [_1] = LAYOUT(
        KC_MPLY, KC_MSTP,
        KC_MPRV, KC_MNXT
    ),
    [_2] = LAYOUT(
        KC_MUTE, KC_NO,
        KC_VOLD, KC_VOLU
    ),
    [_DEV] = LAYOUT(
        QK_BOOT, KC_E,
        KC_3,    KC_5
    )
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case NEXT_PAGE:
      if (pressed) {
          currentLayer++;
          if(currentLayer > max_layer)
          {
              currentLayer = 0;
          }
          layer_move(currentLayer);
      }
      break;
    case PREV_PAGE:
      if (pressed) {
          currentLayer--;
          if(currentLayer > max_layer)
          {
              currentLayer = max_layer;
          }
          layer_move(currentLayer);
      }
      break;
  }
}

void keyboard_post_init_user(void) {
    //automatic calculation of matrix size.
    //I could do this with a constant, but I'm lazy as all hell so nah
    max_layer = sizeof(keymaps) >> 3;
    max_layer--;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer"), false);

    switch (get_highest_layer(layer_state)) {
        case _1:
            oled_write_P(PSTR("1\n"), false);
            break;
        case _2:
            oled_write_P(PSTR("2\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("dev"), false);
    }
    return false;
}
#endif

