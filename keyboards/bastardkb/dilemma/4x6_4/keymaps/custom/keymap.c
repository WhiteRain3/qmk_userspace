// [ ... Copyright & includes remain unchanged ... ]

// ─────────────────────────────────────────────────────────────────────────────
// CONFIG / ENUMS / MACROS
// ─────────────────────────────────────────────────────────────────────────────
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
#endif

// ─────────────────────────────────────────────────────────────────────────────
// THEMING
// ─────────────────────────────────────────────────────────────────────────────
typedef struct {
    uint16_t bg_color;
    uint16_t text_color;
} LayerTheme;

const LayerTheme layer_themes[] = {
    [LAYER_BASE]   = { RGB565(0xFF, 0x00, 0x00), RGB565(0xFF, 0xFF, 0xFF) },
    [LAYER_QWERTY] = { RGB565(0x00, 0x00, 0xFF), RGB565(0xFF, 0xFF, 0xFF) },
    [LAYER_LOWER]  = { RGB565(0x00, 0x00, 0x00), RGB565(0xFF, 0xFF, 0xFF) },
    [LAYER_RAISE]  = { RGB565(0xFF, 0xFF, 0xFF), RGB565(0x00, 0x00, 0x00) },
};

static uint16_t current_bg    = RGB565(0, 0, 0);
static uint16_t current_text  = RGB565(255, 255, 255);

// ─────────────────────────────────────────────────────────────────────────────
// LAYOUTS (PRESERVED 💯)
// ─────────────────────────────────────────────────────────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT(
        KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
        KC_TAB,  KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSLS,
        MT_CTES, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, DF(1),
                 KC_LGUI, MT_ATDE, KC_SPC, LOWER, RAISE, KC_BSPC, KC_ENT, LT(2, KC_MPLY)
    ),
    [LAYER_QWERTY] = LAYOUT(
        KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, LOCK,
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, DF(0),
                 KC_LGUI, KC_LALT, KC_SPC, LOWER, RAISE, KC_BSPC, KC_ENT, _______
    ),
    [LAYER_LOWER] = LAYOUT(
        _______, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_VAD, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, KC_PGUP, C(KC_LEFT), KC_UP, C(KC_RGHT), KC_HOME, KC_GRV, S(KC_9), S(KC_0), KC_EQL, S(KC_EQL), XXXXXXX,
        _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, S(KC_GRV), KC_LBRC, KC_RBRC, S(KC_MINS), KC_MINS, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, KC_LBRC, XXXXXXX, XXXXXXX, XXXXXXX, S(KC_LBRC), S(KC_RBRC), XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, _______, _______, _______, XXXXXXX, _______, _______, KC_MUTE
    ),
    [LAYER_RAISE] = LAYOUT(
        KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P7, KC_P8, KC_P9, KC_PAST, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P4, KC_P5, KC_P6, XXXXXXX, KC_CAPS,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1, KC_P2, KC_P3, KC_PSLS, KC_CALC,
                 _______, _______, _______, XXXXXXX, _______, _______, _______, KC_P0
    )
};

// ─────────────────────────────────────────────────────────────────────────────
// GRAPHICS HELPERS
// ─────────────────────────────────────────────────────────────────────────────
void rgb565_to_rgb888(uint16_t rgb, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = ((rgb >> 11) & 0x1F) << 3;
    *g = ((rgb >> 5) & 0x3F) << 2;
    *b = (rgb & 0x1F) << 3;
}

void rgb565_to_hsv(uint16_t rgb, uint8_t *h, uint8_t *s, uint8_t *v) {
    uint8_t r, g, b;
    rgb565_to_rgb888(rgb, &r, &g, &b);
    rgb888_to_hsv(r, g, b, h, s, v);
}

void draw_layer_ring(uint16_t color) {
    uint8_t h, s, v;
    rgb565_to_hsv(color, &h, &s, &v);
    qp_circle(display, 120, 120, 121, h, s, v, true);  // Outer ring
    qp_circle(display, 120, 120, 115, 0, 0, 0, false); // Inner hole
    qp_flush(display);
}

// ─────────────────────────────────────────────────────────────────────────────
// STATE HANDLERS
// ─────────────────────────────────────────────────────────────────────────────
layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_t merged = state | default_layer_state;
    uint8_t layer = get_highest_layer(merged);

    // Init once
    if (!my_font)  my_font = qp_load_font_mem(&font_fira24);
    if (!display) {
        display = qp_gc9a01_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 2, 0);
        qp_init(display, QP_ROTATION_0);
    }

    // Set text based on layer
    switch (layer) {
        case LAYER_BASE:   anim_text = "Colemak";  break;
        case LAYER_QWERTY: anim_text = "QWERTY";   break;
        case LAYER_LOWER:  anim_text = "Movement"; break;
        case LAYER_RAISE:  anim_text = "F#&nums";  break;
        default:           anim_text = "Undefined";break;
    }

    // Set theme
    if (layer < ARRAY_SIZE(layer_themes)) {
        current_bg   = layer_themes[layer].bg_color;
        current_text = layer_themes[layer].text_color;
    }

    draw_layer_ring(current_bg);
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    default_layer_state = state;
    return layer_state_set_user(layer_state | default_layer_state);
}
