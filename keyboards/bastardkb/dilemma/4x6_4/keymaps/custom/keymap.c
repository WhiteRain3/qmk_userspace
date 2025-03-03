/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <qp.h>
#include "generated/logo.qgf.h"

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_QWERTY,
    LAYER_LOWER,
    LAYER_RAISE,
};

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define MT_CTES MT(MOD_LCTL, KC_ESC)
#define MT_ATDE MT(MOD_LALT, KC_DEL)
#define LOCK G(KC_L)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif  // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    LOCK,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        MT_CTES,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,       KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,   DF(1),
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                         KC_LGUI, MT_ATDE,  KC_SPC,   LOWER,      RAISE,  KC_ENT, KC_BSPC, KC_MPLY
  //                    ╰───────────────────────────────────╯ ╰───────────────────────────────────╯
  ),

  [LAYER_QWERTY] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    LOCK,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,   DF(0),
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                         KC_LGUI, KC_LALT,  KC_SPC,   LOWER,      RAISE,  KC_ENT, KC_BSPC, KC_MPLY
  //                    ╰───────────────────────────────────╯ ╰───────────────────────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, RGB_TOG, RGB_RMOD,    RGB_MOD,    RGB_VAD,    RGB_VAI,    RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, XXXXXXX, QK_BOOT,
  // ├────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, S(KC_1),  S(KC_2), S(KC_LBRC), S(KC_RBRC),    S(KC_7),    KC_PMNS,   KC_P7,   KC_P8,   KC_P9, KC_PAST, XXXXXXX,
  // ├────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, S(KC_3),  S(KC_4),    S(KC_9),    S(KC_0), S(KC_BSLS),    KC_PPLS,   KC_P4,   KC_P5,   KC_P6,  KC_EQL, KC_CAPS,
  // ├────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, S(KC_5),  S(KC_6),    KC_LBRC,    KC_RBRC, S(KC_MINS),    KC_PDOT,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_CALC,
  // ╰────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                          XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,    XXXXXXX, _______,   KC_P0, XXXXXXX
  //                     ╰────────────────────────────────────────────╯ ╰───────────────────────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,       KC_F2,         KC_F3,       KC_F4,      KC_F5,         KC_F6,       KC_F7,     KC_F8,      KC_F9,    KC_F10,    KC_F11,
  // ├───────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────┤
       _______, XXXXXXX,     XXXXXXX,       XXXXXXX, RCS(KC_ESC),  LSG(KC_S),       KC_HOME,     KC_PGUP,   KC_PGDN,     KC_END, RCS(KC_E),   C(KC_1),
  // ├───────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────┤
       _______, KC_LEFT, KC_MS_WH_UP, KC_MS_WH_DOWN,  KC_MS_BTN1, KC_MS_BTN2,       KC_LEFT,     KC_DOWN,     KC_UP,    KC_RGHT, RCS(KC_F), C(KC_GRV),
  // ├───────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────┤
       _______, C(KC_Z),     C(KC_X),       C(KC_C),     C(KC_Y),    C(KC_V),    A(KC_LEFT), RCS(KC_TAB), C(KC_TAB), A(KC_RGHT), RCS(KC_G),   C(KC_2),
  // ╰───────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────╯
                             _______,       _______,     _______,    XXXXXXX,       _______,     XXXXXXX,   XXXXXXX,    XXXXXXX
  //                        ╰────────────────────────────────────────────────╯ ╰───────────────────────────────────────────────╯
  )
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif  // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif  // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif  // RGB_MATRIX_ENABLE

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_BASE]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU),            ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_QWERTY]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU),            ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_LOWER]   = {ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP),  ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP)},
    [LAYER_RAISE]   = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT),            ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
};
// clang-format on
#endif  // ENCODER_MAP_ENABLE

painter_device_t display;
static painter_image_handle_t my_image;
static deferred_token my_anim;

void keyboard_post_init_kb(void) {
    // https://imageresizer.com/
    // https://ezgif.com/resize
    // https://msys.qmk.fm/  -- for the cli to run commands on
    // qmk painter-convert-graphics -f pal2 -i pics/logo.png -o ./generated/
    display = qp_gc9a01_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 2, 0);
    qp_init(display, QP_ROTATION_0);
    my_image = qp_load_image_mem(gfx_logo);
    if (my_image != NULL) {
        // qp_clear(display);
        // qp_drawimage(display, (0), (0), my_image);
        // qp_flush(display);
        my_anim = qp_animate(display, (0), (0), my_image);
    }
}
