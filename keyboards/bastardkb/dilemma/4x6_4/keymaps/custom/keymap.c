#include QMK_KEYBOARD_H
#include <qp.h>
#include "generated/logo.qgf.h"
#include "generated/ring.qff.h"
#include "quantum/color.h"

// 1. Enums first so functions below can see them
enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_QWERTY,
    LAYER_LOWER,
    LAYER_RAISE,
};

enum {
    TD_GUI_DF0 = 0,
    TD_GUI_DF1
};

// --- TAP DANCE FUNCTIONS ---
void dance_gui0_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) register_code(KC_LGUI);
    else if (state->count == 2) default_layer_set(1UL << LAYER_BASE);
}
void dance_gui0_reset(tap_dance_state_t *state, void *user_data) { unregister_code(KC_LGUI); }

void dance_gui1_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) register_code(KC_LGUI);
    else if (state->count == 2) default_layer_set(1UL << LAYER_QWERTY);
}
void dance_gui1_reset(tap_dance_state_t *state, void *user_data) { unregister_code(KC_LGUI); }

tap_dance_action_t tap_dance_actions[] = {
    [TD_GUI_DF0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_gui0_finished, dance_gui0_reset),
    [TD_GUI_DF1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_gui1_finished, dance_gui1_reset),
};

// --- DISPLAY GLOBALS ---
static painter_font_handle_t  my_font = NULL;
static painter_image_handle_t my_logo = NULL;
static painter_device_t       display = NULL;
static uint8_t                last_reported_layer = 255;

#define RGB565(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

typedef struct {
    uint16_t bg_color;
} LayerTheme;

const LayerTheme layer_themes[] = {
    [LAYER_BASE]   = { RGB565(0xFF, 0x00, 0x00) },
    [LAYER_QWERTY] = { RGB565(0x00, 0x00, 0xFF) },
    [LAYER_LOWER]  = { RGB565(0x00, 0x00, 0x00) },
    [LAYER_RAISE]  = { RGB565(0x33, 0x33, 0x33) },
};

// --- KEYMAPS & ENCODERS (Omitted for brevity, keep yours as they were) ---
// ... (Your keymaps[][][] and encoder_map[][][] blocks here) ...

// --- COLOR HELPERS ---
static inline void rgb565_to_rgb888(uint16_t rgb565, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = ((rgb565 >> 11) & 0x1F) << 3;
    *g = ((rgb565 >> 5) & 0x3F) << 2;
    *b = (rgb565 & 0x1F) << 3;
}

static inline void rgb888_to_hsv(uint8_t r, uint8_t g, uint8_t b, uint8_t *h, uint8_t *s, uint8_t *v) {
    uint8_t max = (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
    uint8_t min = (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
    *v = max;
    uint8_t delta = max - min;
    if (max == 0 || delta == 0) { *s = 0; *h = 0; return; }
    *s = (delta * 255) / max;
    if (max == r) *h = 43 * (g - b) / delta;
    else if (max == g) *h = 85 + 43 * (b - r) / delta;
    else *h = 171 + 43 * (r - g) / delta;
}

void update_display_now(uint8_t layer) {
    if (!display) return;

    if (!my_font) my_font = qp_load_font_mem(&font_ring);
    if (!my_logo) my_logo = qp_load_image_mem(&gfx_logo);

    uint16_t color_565 = (layer < 4) ? layer_themes[layer].bg_color : 0x0000;
    uint8_t r, g, b, h, s, v;
    rgb565_to_rgb888(color_565, &r, &g, &b);
    rgb888_to_hsv(r, g, b, &h, &s, &v);

    qp_rect(display, 0, 0, 239, 239, 0, 0, 0, true);

    // Draw the "Ring" (assuming the ring font is sized to ~200-240px)
    if (my_font) {
        qp_drawtext_recolor(display, 20, 20, my_font, "o", h, s, v, 0, 0, 0);
    }

    // Draw the Resized Logo (Centered at 60, 60)
    if (my_logo) {
        qp_drawimage(display, 60, 60, my_logo);
    }

    qp_flush(display);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t current_layer = get_highest_layer(state);

    // Initial hardware setup
    if (!display) {
        // Divisor 8 is the safest speed for long wires/ribbon cables
        display = qp_gc9a01_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 8, 0);
        qp_init(display, QP_ROTATION_0);
        update_display_now(current_layer);
    }

    // Only update if the layer actually changed
    if (current_layer != last_reported_layer) {
        last_reported_layer = current_layer;
        update_display_now(current_layer);
    }

    return state;
}
