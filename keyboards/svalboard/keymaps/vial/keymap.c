#include "keycodes.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>
#include "svalboard.h"

// ONLY wrap pointing_device_task_user to avoid the redefinition error.
#define pointing_device_task_user sval_support_pointing_device_task_user
#include "../keymap_support.c"
#undef pointing_device_task_user

// Fallback in case a specific board variant doesn't use the mouse task
__attribute__((weak)) report_mouse_t sval_support_pointing_device_task_user(report_mouse_t mouse_report) { return mouse_report; }

bool is_jiggling = false;
uint32_t jiggle_timer = 0;
uint8_t jiggle_step = 0;

enum layer {
    NORMAL = 0,
    NAVNAS = 1,
    FUNC = 2,
    BOARD_CONFIG = 3,
    MBO = 4,
};

#if __has_include("keymap_all.h")
#include "keymap_all.h"
#else
int sval_macro_size = 0;
uint8_t sval_macros[] = {0};
const uint16_t PROGMEM keymaps[DYNAMIC_KEYMAP_LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = LAYOUT(
        KC_J, KC_U, KC_QUOTE, KC_M, KC_H, KC_NO,
        KC_K, KC_I, KC_COLON, KC_COMMA, KC_Y, KC_NO,
        KC_L, KC_O, LT(BOARD_CONFIG, KC_NO), KC_DOT, KC_N, KC_NO,
        KC_SEMICOLON, KC_P, KC_BSLS, KC_SLASH, KC_RBRC, KC_NO,
        KC_F, KC_R, KC_G, KC_V, LSFT(KC_QUOTE), KC_NO,
        KC_D, KC_E, KC_T, KC_C, KC_GRAVE, KC_NO,
        KC_S, KC_W, KC_B, KC_X, KC_ESCAPE, KC_NO,
        KC_A, KC_Q, KC_LBRC, KC_Z, KC_DELETE, KC_NO,
        MO(NAVNAS), KC_SPACE, KC_NO, KC_BSPC, KC_LALT, MO(FUNC),
        KC_LSFT, LT(NAVNAS, KC_ENTER), KC_NO, LGUI_T(KC_TAB), KC_LCTL, KC_CAPS       
    ),
    [NAVNAS] = LAYOUT(
        KC_7, LSFT(KC_7), LSFT(KC_6), KC_LEFT, KC_6, KC_NO,
        KC_8, LSFT(KC_8), KC_NO, KC_UP, LSFT(KC_MINUS), KC_NO,
        KC_9, LSFT(KC_9), KC_NO, KC_DOWN, KC_INSERT, KC_NO,
        KC_0, LSFT(KC_0), KC_NO, KC_RIGHT, LSFT(KC_GRAVE), KC_NO,
        KC_4, LSFT(KC_4), KC_5, KC_END, LSFT(KC_5), KC_NO,
        KC_3, LSFT(KC_3), KC_MINUS, KC_PGDN, LSFT(KC_EQUAL), KC_NO,
        KC_2, LSFT(KC_2), KC_DOT, KC_PGUP, KC_TRNS, KC_NO,
        KC_1, LSFT(KC_1), KC_EQUAL, KC_HOME, KC_TRNS, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS         
    ),
    [FUNC] = LAYOUT(
        KC_F7, KC_NO, KC_F16, KC_F17, KC_F6, KC_NO,
        KC_F8, KC_NO, KC_NO, KC_F18, KC_NO, KC_NO,
        KC_F9, KC_NO, KC_NO, KC_F19, KC_NO, KC_NO,
        KC_F10, KC_NO, KC_NO, KC_F20, KC_NO, KC_NO,
        KC_F4, KC_F24, KC_F5, KC_F14, KC_F15, KC_NO,
        KC_F3, KC_F23, KC_F10, KC_F13, KC_NO, KC_NO,
        KC_F2, KC_F22, KC_NO, KC_F12, KC_NO, KC_NO,
        KC_F1, KC_F21, KC_NO, KC_F11, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS         
    ),
    [BOARD_CONFIG] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
