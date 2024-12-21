// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

const uint16_t PROGMEM nextPage[] = {KC_MPRV, KC_MNXT, COMBO_END};
const uint16_t PROGMEM prevPage[] = {KC_MPLY, KC_MSTP, COMBO_END};
const uint16_t PROGMEM devmodePage[] = {KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, COMBO_END};

uint_fast8_t currentLayer = 0;
uint_fast8_t max_layer;
bool devmode = false;

enum combos {
  NEXT_PAGE,
  PREV_PAGE,

  DEV_PAGE,
};

enum layers {
    _1,
    _2,
    _3,

    _DEV
};

combo_t key_combos[] = {
    [NEXT_PAGE] = COMBO(nextPage, KC_NO),
    [PREV_PAGE] = COMBO(prevPage, KC_NO),
    [DEV_PAGE] = COMBO(devmodePage, KC_NO)
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
    [_3] = LAYOUT(
        MS_BTN3, KC_NO,
        MS_BTN1, MS_BTN2
    ),
    [_DEV] = LAYOUT(
        QK_BOOT, KC_NO,
        KC_NO  , KC_NO
    )
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case NEXT_PAGE:
      if(devmode)
      {
        devmode = false;
      }
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
      if(devmode)
      {
        devmode = false;
      }
      if (pressed) {
          currentLayer--;
          if(currentLayer > max_layer)
          {
              currentLayer = max_layer;
          }
          layer_move(currentLayer);
      }
      break;
    case DEV_PAGE:
      if(pressed)
      {
          if(devmode)
          {
              devmode = false;
              layer_move(currentLayer);
          }
          else
          {
              devmode = true;
              layer_move(_DEV);
          }
      }
      break;
  }
}

void keyboard_post_init_user(void) {
    //automatic calculation of matrix size.
    //I could do this with a constant, but I'm lazy as all hell so nah
    max_layer = sizeof(keymaps) >> 3;
    max_layer -= 2;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    //Host Keyboard Layer Status
    #include "image.c"
    int layer = get_highest_layer(layer_state);

    if(layer == _DEV)
    {
        int above = currentLayer == _1 ? max_layer : currentLayer - 1;
        int below = currentLayer == max_layer ? _1 : currentLayer + 1;
        show_oled(_DEV, above, below);
        return false;
    }

    int above = layer == _1 ? max_layer : layer - 1;
    int below = layer == max_layer ? _1 : layer + 1;

    show_oled(layer, above, below);

    //oled_write_P(PSTR("Layer"), false);

    //switch (get_highest_layer(layer_state)) {
    //    case _1:
    //        oled_write_P(PSTR("media\n"), false);
    //        break;
    //    case _2:
    //        oled_write_P(PSTR("audio\n"), false);
    //        break;
    //    case _3:
    //        oled_write_P(PSTR("mouse\n"), false);
    //        break;
    //    default:
    //        // Or use the write_ln shortcut over adding '\n' to the end of your string
    //        oled_write_ln_P(PSTR("dev"), false);
    //}
    return false;
}
#endif

