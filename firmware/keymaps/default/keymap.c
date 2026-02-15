#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    _BASE = 0,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_A, KC_B, KC_C
    ),
    [_FN] = LAYOUT(
        KC_F1, KC_F2, KC_F3
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_highest_layer(layer_state) == _BASE) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
static void oled_render_layer(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FN\n"), false);
            break;
        default:
            oled_write_P(PSTR("??\n"), false);
    }
}

bool oled_task_user(void) {
    oled_clear();
    oled_render_layer();
    return false;
}
#endif
