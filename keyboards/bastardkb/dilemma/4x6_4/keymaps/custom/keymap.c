/**
 * Copyright 2021 Charly Delay <charly@codesink.dev>
 * Copyright 2023 casuanoob <casuanoob@hotmail.com>
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
 #include "generated/fira24.qff.h"
 #include "quantum/color.h"

 enum dilemma_keymap_layers {
     LAYER_BASE = 0,
     LAYER_QWERTY,
     LAYER_LOWER,
     LAYER_RAISE,
 };
 #define RGB565(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

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

 typedef struct {
     uint16_t bg_color;
     uint16_t text_color;
 } LayerTheme;

 const LayerTheme layer_themes[] = {
     [LAYER_BASE]   = { RGB565(0xFF, 0x00, 0x00), RGB565(0xFF, 0xFF, 0xFF) }, // Red bg, White text
     [LAYER_QWERTY] = { RGB565(0x00, 0x00, 0xFF), RGB565(0xFF, 0xFF, 0xFF) }, // Blue bg, White text
     [LAYER_LOWER]  = { RGB565(0x00, 0x00, 0x00), RGB565(0xFF, 0xFF, 0xFF) }, // Black bg, White text
     [LAYER_RAISE]  = { RGB565(0xFF, 0xFF, 0xFF), RGB565(0x00, 0x00, 0x00) }, // White bg, Black text
 };

 // Layout definitions remain unchanged.
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [LAYER_BASE] = LAYOUT(
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,  KC_7,    KC_8,    KC_9,         KC_0,    KC_MINS,
        KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,  KC_L,    KC_U,    KC_Y,         KC_SCLN, KC_BSLS,
        MT_CTES,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,  KC_N,    KC_E,    KC_I,         KC_O,    KC_QUOT,
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,  KC_H,    KC_COMM, KC_DOT,       KC_SLSH, DF(1),
                         KC_LGUI, MT_ATDE,  KC_SPC,   LOWER,    RAISE, KC_BSPC, KC_ENT,  LT(2,KC_MPLY)
   ),

   [LAYER_QWERTY] = LAYOUT(
        KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,  KC_7,   KC_8,    KC_9,   KC_0,    LOCK,
        KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,  KC_U,   KC_I,    KC_O,   KC_P,    KC_BSLS,
        KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,  KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,  KC_M,   KC_COMM, KC_DOT, KC_SLSH, DF(0),
                          KC_LGUI, KC_LALT,  KC_SPC,   LOWER,    RAISE, KC_BSPC, KC_ENT, _______
   ),

   [LAYER_LOWER] = LAYOUT(
        _______, RGB_TOG, RGB_RMOD,   RGB_MOD, RGB_VAD,    RGB_VAI,        XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,   XXXXXXX,
        _______, KC_PGUP, C(KC_LEFT), KC_UP,   C(KC_RGHT), KC_HOME,        KC_GRV,    S(KC_9),    S(KC_0),    KC_EQL,     S(KC_EQL), XXXXXXX,
        _______, KC_PGDN, KC_LEFT,    KC_DOWN, KC_RGHT,    KC_END,         S(KC_GRV), KC_LBRC,    KC_RBRC,    S(KC_MINS), KC_MINS,   XXXXXXX,
        _______, XXXXXXX, XXXXXXX,    KC_LBRC, XXXXXXX,    XXXXXXX,        XXXXXXX,   S(KC_LBRC), S(KC_RBRC), XXXXXXX,    XXXXXXX,   XXXXXXX,
                           _______,    _______,    _______,    _______,    XXXXXXX,   _______,    _______,    KC_MUTE
   ),

   [LAYER_RAISE] = LAYOUT(
        KC_F12,   KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   KC_P7,   KC_P8,   KC_P9,  KC_PAST, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   KC_P4,   KC_P5,   KC_P6,  XXXXXXX, KC_CAPS,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   KC_P1,   KC_P2,   KC_P3,  KC_PSLS, KC_CALC,
                       _______,  _______,  _______,  XXXXXXX,    _______, _______,  _______,  KC_P0
   )
 };

 #ifdef POINTING_DEVICE_ENABLE
 #    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
 layer_state_t layer_state_set_user(layer_state_t state) {
     dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
     return state;
 }
 #    endif  // DILEMMA_AUTO_SNIPING_ON_LAYER
 #endif  // POINTING_DEVICE_ENABLE

 #ifdef RGB_MATRIX_ENABLE
 void rgb_matrix_update_pwm_buffers(void);
 #endif  // RGB_MATRIX_ENABLE

 #ifdef ENCODER_MAP_ENABLE
 const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
     [LAYER_BASE]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU),            ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
     //[LAYER_QWERTY]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU),            ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
     [LAYER_LOWER]   = {ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP),  ENCODER_CCW_CW(KC_RGHT, KC_LEFT)},
     [LAYER_RAISE]   = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT),            ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
 };
 #endif  // ENCODER_MAP_ENABLE

 // Remove unused variables and commented-out code to reduce memory footprint.
 static painter_font_handle_t my_font = NULL;
 static painter_device_t display = NULL;

 extern layer_state_t default_layer_state;

 // Mark helper functions as inline for performance.
 static inline void rgb565_to_rgb888(uint16_t rgb565, uint8_t *r, uint8_t *g, uint8_t *b) {
     *r = ((rgb565 >> 11) & 0x1F) << 3;
     *g = ((rgb565 >> 5) & 0x3F) << 2;
     *b = (rgb565 & 0x1F) << 3;
 }

 static inline void rgb888_to_hsv(uint8_t r, uint8_t g, uint8_t b, uint8_t *h, uint8_t *s, uint8_t *v) {
     uint8_t max = r > g ? (r > b ? r : b) : (g > b ? g : b);
     uint8_t min = r < g ? (r < b ? r : b) : (g < b ? g : b);
     *v = max;
     uint8_t delta = max - min;
     *s = (max == 0) ? 0 : (delta * 255) / max;
     if (delta == 0) {
         *h = 0;
         return;
     }
     if (max == r) {
         *h = 43 * (g - b) / delta;
     } else if (max == g) {
         *h = 85 + 43 * (b - r) / delta;
     } else {
         *h = 171 + 43 * (r - g) / delta;
     }
 }

 layer_state_t layer_state_set_user(layer_state_t state) {
     // Combine the current state with the default layer state.
     layer_state_t merged_state = state | default_layer_state;
     uint8_t layer = get_highest_layer(merged_state);

     // Lazy-load the font if not already loaded.
     if (!my_font) {
         my_font = qp_load_font_mem(&font_fira24);
         if (!my_font) {
             dprint("Font load failed!\n");
             return state;
         }
     }
     // Lazy initialize the display device.
     if (!display) {
         display = qp_gc9a01_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 2, 0);
         qp_init(display, QP_ROTATION_0);
     }

     // Determine the theme for the active layer using only the background color.
     uint16_t current_bg;
     if (layer < (sizeof(layer_themes) / sizeof(layer_themes[0]))) {
         current_bg = layer_themes[layer].bg_color;
     } else {
         current_bg = RGB565(0x00, 0x00, 0x00);  // Fallback to black
     }

     // Convert the RGB565 background color to HSV and update the display.
     uint8_t h_bg, s_bg, v_bg, r, g, b;
     rgb565_to_rgb888(current_bg, &r, &g, &b);
     rgb888_to_hsv(r, g, b, &h_bg, &s_bg, &v_bg);
     qp_circle(display, 120, 120, 121, h_bg, s_bg, v_bg, true);   // Outer ring (border)
     qp_circle(display, 120, 120, 115, 0, 0, 0, false);             // Inner cutout
     qp_flush(display);

     return state;
 }

 layer_state_t default_layer_state_set_user(layer_state_t state) {
     default_layer_state = state;  // Update global default layer state.
     layer_state_t merged_state = state | default_layer_state;
     return layer_state_set_user(merged_state);
 }
