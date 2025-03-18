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
    [LAYER_BASE]   = { RGB565(0x00, 0x00, 0x00), RGB565(0xFF, 0xFF, 0xFF) }, // black bg, white text
    [LAYER_QWERTY] = { RGB565(0x00, 0x00, 0xFF), RGB565(0xFF, 0xFF, 0x00) }, // blue bg, yellow text
    [LAYER_LOWER]  = { RGB565(0x20, 0x20, 0x20), RGB565(0x00, 0xFF, 0xFF) }, // dark gray bg, cyan text
    [LAYER_RAISE]  = { RGB565(0x80, 0x00, 0x80), RGB565(0x00, 0xFF, 0x00) }, // purple bg, green text
};
static uint16_t current_bg = RGB565(0x00, 0x00, 0x00);
static uint16_t current_text = RGB565(0xFF, 0xFF, 0xFF);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭─────────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────────────────╮
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,  KC_7,    KC_8,    KC_9,         KC_0,    KC_MINS,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────┤
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,  KC_L,    KC_U,    KC_Y,         KC_SCLN, KC_BSLS,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────┤
       MT_CTES,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,  KC_N,    KC_E,    KC_I,         KC_O,    KC_QUOT,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────┤
       KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,  KC_H,    KC_COMM, KC_DOT,       KC_SLSH, DF(1),
  // ╰─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────╯
                        KC_LGUI, MT_ATDE,  KC_SPC,   LOWER,    RAISE, KC_BSPC, KC_ENT,  LT(2,KC_MPLY)
  //                   ╰───────────────────────────────────╯ ╰───────────────────────────────────────╯
  ),

  [LAYER_QWERTY] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────╮
       KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,  KC_7,   KC_8,    KC_9,   KC_0,    LOCK,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────┤
       KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,  KC_U,   KC_I,    KC_O,   KC_P,    KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,  KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────┤
       KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,  KC_M,   KC_COMM, KC_DOT, KC_SLSH, DF(0),
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────╯
                         KC_LGUI, KC_LALT,  KC_SPC,   LOWER,    RAISE, KC_BSPC, KC_ENT, _______
  //                    ╰───────────────────────────────────╯ ╰────────────────────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────╮ ╭───────────────────────────────────────────────────────────────────╮
       _______, RGB_TOG, RGB_RMOD,   RGB_MOD, RGB_VAD,    RGB_VAI,        XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,   XXXXXXX,
  // ├────────────────────────────────────────────────────────────────┤ ├───────────────────────────────────────────────────────────────────┤
       _______, KC_PGUP, C(KC_LEFT), KC_UP,   C(KC_RGHT), KC_HOME,        KC_GRV,    S(KC_9),    S(KC_0),    KC_EQL,     S(KC_EQL), XXXXXXX,
  // ├────────────────────────────────────────────────────────────────┤ ├───────────────────────────────────────────────────────────────────┤
       _______, KC_PGDN, KC_LEFT,    KC_DOWN, KC_RGHT,    KC_END,         S(KC_GRV), KC_LBRC,    KC_RBRC,    S(KC_MINS), KC_MINS,   XXXXXXX,
  // ├────────────────────────────────────────────────────────────────┤ ├───────────────────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX,    KC_LBRC, XXXXXXX,    XXXXXXX,        XXXXXXX,   S(KC_LBRC), S(KC_RBRC), XXXXXXX,    XXXXXXX,   XXXXXXX,
  // ╰────────────────────────────────────────────────────────────────┤ ├───────────────────────────────────────────────────────────────────╯
                          _______,    _______,    _______,    _______,    XXXXXXX,   _______,    _______,    KC_MUTE
  //                     ╰────────────────────────────────────────────╯ ╰───────────────────────────────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭───────────────────────────────────────────────────────╮
       KC_F12,   KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├───────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   KC_P7,   KC_P8,   KC_P9,  KC_PAST, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├───────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   KC_P4,   KC_P5,   KC_P6,  XXXXXXX, KC_CAPS,
  // ├──────────────────────────────────────────────────────┤ ├───────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   KC_P1,   KC_P2,   KC_P3,  KC_PSLS, KC_CALC,
  // ╰──────────────────────────────────────────────────────┤ ├───────────────────────────────────────────────────────╯
                      _______,  _______,  _______,  XXXXXXX,    _______, _______,  _______,  KC_P0
//                   ╰──────────────────────────────────────╯ ╰───────────────────────────────────╯
  )
};
// clang-format on
uint32_t animate_text(uint32_t trigger, void *ctx);
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
    [LAYER_BASE]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU),            ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    //[LAYER_QWERTY]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU),            ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_LOWER]   = {ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP),  ENCODER_CCW_CW(KC_RGHT, KC_LEFT)},
    [LAYER_RAISE]   = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT),            ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
};
// clang-format on
#endif  // ENCODER_MAP_ENABLE

static painter_font_handle_t my_font = NULL;
static painter_device_t display = NULL;
// static painter_image_handle_t my_image;
// static deferred_token my_anim;

// void keyboard_post_init_kb(void) {
//     // https://imageresizer.com/
//     // https://ezgif.com/resize
//     // https://msys.qmk.fm/  -- for the cli to run commands on
//     // qmk painter-convert-graphics -f pal2 -i pics/logo.png -o ./generated/
//
//     my_image = qp_load_image_mem(gfx_logo);
//     if (my_image != NULL) {
//         // qp_clear(display);
//         // qp_drawimage(display, (0), (0), my_image);
//         // qp_flush(display);
//         if (LAYER_BASE)
//         my_anim = qp_animate(display, (0), (0), my_image);
//     }
//    }
static layer_state_t default_layer_state = 1UL;
static const char *anim_text = NULL;
static uint8_t anim_step = 0;
static deferred_token anim_token;
// qmk painter-make-font-image --font fonts/Fira-Code-Mono.ttf --size 24 -o ./generated/fira24.png
// qmk painter-convert-font-image --input ./generated/fira24.png -f mono

void rgb565_to_rgb888(uint16_t rgb565, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = ((rgb565 >> 11) & 0x1F) << 3;
    *g = ((rgb565 >> 5) & 0x3F) << 2;
    *b = (rgb565 & 0x1F) << 3;
}
void rgb888_to_hsv(uint8_t r, uint8_t g, uint8_t b, uint8_t *h, uint8_t *s, uint8_t *v) {
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

uint32_t animate_text(uint32_t trigger, void *ctx) {
    if (!display || !my_font || !anim_text) return 0;

    uint8_t r, g, b;
    rgb565_to_rgb888(current_bg, &r, &g, &b);
    RGB rgb = { r, g, b };
    HSV hsv = rgb888_to_hsv(rgb);

    qp_rect(display, 0, 0, 239, 239, 0, 255, 255, true);  // bright red


    char partial[32] = {0};
    memcpy(partial, anim_text, anim_step);

    int16_t width = qp_textwidth(my_font, partial);
    int16_t x = (240 - width) / 2;
    int16_t y = (240 - my_font->line_height) / 2;
    uint8_t h_fg, s_fg, v_fg;
    uint8_t h_bg, s_bg, v_bg;

    rgb565_to_rgb888(current_text, &r, &g, &b);
    rgb888_to_hsv(r, g, b, &h_fg, &s_fg, &v_fg);

    rgb565_to_rgb888(current_bg, &r, &g, &b);
    rgb888_to_hsv(r, g, b, &h_bg, &s_bg, &v_bg);

    qp_drawtext_recolor(display, x, y, my_font, partial,
        h_fg, s_fg, v_fg,
        h_bg, s_bg, v_bg
    );
    qp_flush(display);

    if (anim_text[anim_step] != '\0') {
        anim_step++;
        anim_token = defer_exec(50, animate_text, NULL);  // ✅ 3 arguments
    }

    return 0;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Combine default + active layers
    layer_state_t merged_state = state | default_layer_state;

    uint8_t layer = get_highest_layer(merged_state);
    if (!my_font) {
        my_font = qp_load_font_mem(&font_fira24);
        if (!my_font) {
            dprint("Font load failed!\n");
            return state;
        }
    }

    if (!display) {
        display = qp_gc9a01_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 2, 0);
        qp_init(display, QP_ROTATION_0);
    }

    uint8_t layer = get_highest_layer(state);

    switch (layer) {
        case LAYER_BASE:   anim_text = "Colemak";     break;
        case LAYER_QWERTY: anim_text = "QWERTY";      break;
        case LAYER_LOWER:  anim_text = "Symbols";     break;
        case LAYER_RAISE:  anim_text = "Nav & Fkeys"; break;
        default:           anim_text = "Undefined";   break;
    }

    // 🌈 Get theme for this layer (fallback to base if out of bounds)
    if (layer < sizeof(layer_themes)/sizeof(layer_themes[0])) {
        current_bg = layer_themes[layer].bg_color;
        current_text = layer_themes[layer].text_color;
    } else {
        current_bg = RGB565(0x00, 0x00, 0x00);  // black
        current_text = RGB565(0xFF, 0xFF, 0xFF);  // white
    }

    // Start animation
    anim_step = 1;
    animate_text(0, NULL);  // Initial call
    return state;
}


layer_state_t default_layer_state_set_user(layer_state_t state) {
    // Reuse the drawing code from layer_state_set_user
    return layer_state_set_user(state);
}
