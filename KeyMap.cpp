#include <Arduino.h>
#include "KeyMap.h"
#include "HIDKeys.h"

#define NUMBER_OF_LAYERS 1
#define NUMBER_OF_ROWS 5
#define NUMBER_OF_COLS 15
#define BASE 0


// renames
#define _______  KEY_NONE

#define K_LCTL   KEY_LEFTCTRL
#define K_LSFT   KEY_LEFTSHIFT
#define K_LALT   KEY_LEFTALT
#define K_LMET   KEY_LEFTMETA
#define K_RCTL   KEY_RIGHTCTRL
#define K_RSFT   KEY_RIGHTSHIFT
#define K_RALT   KEY_RIGHTALT
#define K_RMET   KEY_RIGHTMETA

#define K_SPC    KEY_SPACE
#define K_ENT    KEY_ENTER
#define K_ESC    KEY_ESC
#define K_BSPC   KEY_BACKSPACE
#define K_TAB    KEY_TAB
#define K_MINS   KEY_MINUS
#define K_EQL    KEY_EQUAL
#define K_LBRC   KEY_LEFTBRACE
#define K_RBRC   KEY_RIGHTBRACE
#define K_BSLS   KEY_BACKSLASH
#define K_SCLN   KEY_SEMICOLON
#define K_QUOT   KEY_APOSTROPHE
#define K_GRV    KEY_GRAVE
#define K_COMM   KEY_COMMA
#define K_DOT    KEY_DOT
#define K_SLSH   KEY_SLASH
#define K_CAPS   KEY_CAPSLOCK

// #define KEY_SYSRQ 0x46 // Keyboard Print Screen
// #define KEY_PAUSE 0x48 // Keyboard Pause
// #define KEY_INSERT 0x49 // Keyboard Insert
#define K_HOME   KEY_HOME
#define K_PGUP   KEY_PAGEUP
#define K_DEL    KEY_DELETE
#define K_END    KEY_END
#define K_PGDN   KEY_PAGEDOWN
#define K_RGHT   KEY_RIGHT
#define K_LEFT   KEY_LEFT
#define K_DOWN   KEY_DOWN
#define K_UP     KEY_UP

// #define KEY_OPEN 0x74 // Keyboard Execute
// #define KEY_HELP 0x75 // Keyboard Help
// #define KEY_PROPS 0x76 // Keyboard Menu
// #define KEY_FRONT 0x77 // Keyboard Select
// #define KEY_STOP 0x78 // Keyboard Stop
// #define KEY_AGAIN 0x79 // Keyboard Again
// #define KEY_UNDO 0x7a // Keyboard Undo
// #define KEY_CUT 0x7b // Keyboard Cut
// #define KEY_COPY 0x7c // Keyboard Copy
// #define KEY_PASTE 0x7d // Keyboard Paste
// #define KEY_FIND 0x7e // Keyboard Find
// #define KEY_MUTE 0x7f // Keyboard Mute
// #define KEY_VOLUMEUP 0x80 // Keyboard Volume Up
// #define KEY_VOLUMEDOWN 0x81 // Keyboard Volume Down

// #define KEY_MEDIA_PLAYPAUSE 0xe8
// #define KEY_MEDIA_STOPCD 0xe9
// #define KEY_MEDIA_PREVIOUSSONG 0xea
// #define KEY_MEDIA_NEXTSONG 0xeb
// #define KEY_MEDIA_EJECTCD 0xec
// #define KEY_MEDIA_VOLUMEUP 0xed
// #define KEY_MEDIA_VOLUMEDOWN 0xee
// #define KEY_MEDIA_MUTE 0xef
// #define KEY_MEDIA_WWW 0xf0
// #define KEY_MEDIA_BACK 0xf1
// #define KEY_MEDIA_FORWARD 0xf2
// #define KEY_MEDIA_STOP 0xf3
// #define KEY_MEDIA_FIND 0xf4
// #define KEY_MEDIA_SCROLLUP 0xf5
// #define KEY_MEDIA_SCROLLDOWN 0xf6
// #define KEY_MEDIA_EDIT 0xf7
// #define KEY_MEDIA_SLEEP 0xf8
// #define KEY_MEDIA_COFFEE 0xf9
// #define KEY_MEDIA_REFRESH 0xfa
// #define KEY_MEDIA_CALC 0xfb

const int layers[NUMBER_OF_LAYERS][NUMBER_OF_ROWS][NUMBER_OF_COLS] PROGMEM = {
  [BASE] = {
    { K_GRV,  KEY_1,   KEY_2,    KEY_3,    KEY_4,    KEY_5,    KEY_6,    KEY_7,    KEY_8,    KEY_9,    KEY_0,     K_MINS,    K_EQL ,  K_BSPC,  K_HOME },
    { K_TAB,  KEY_Q,   KEY_W,    KEY_E,    KEY_R,    KEY_T,    KEY_Y,    KEY_U,    KEY_I,    KEY_O,    KEY_P,     K_LBRC,    K_RBRC,  K_BSLS,  K_END },
    { K_ESC,  KEY_A,   KEY_S,    KEY_D,    KEY_F,    KEY_G,    KEY_H,    KEY_J,    KEY_K,    KEY_L,    K_SCLN,    K_QUOT,    K_ENT,   K_PGUP,  _______ },
    { K_LSFT, KEY_Z,   KEY_X,    KEY_C,    KEY_V,    KEY_B,    KEY_N,    KEY_M,    K_COMM,   K_DOT,    K_SLSH,    K_RSFT,    K_UP,    K_PGDN,  _______ },
    { K_LCTL, _______, K_LMET,   K_LALT,   K_SPC,    K_SPC,    _______,  K_RMET,   K_RALT,   K_RCTL,   K_LEFT,    K_DOWN,    K_RGHT,  _______, _______ }
  }
};




// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//   [_BASE] = LAYOUT_65(
//     KC_GRV, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_NO,  KC_BSPC, KC_HOME, \
//     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END, \
//     KC_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP, \
//     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN, \
//     KC_LCTL, MO(_FN1), KC_LGUI, KC_LALT, KC_SPC,           KC_SPC,  KC_NO,   KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
//   ),
//
//   [_FN1] = LAYOUT_65(
//     KC_ESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,  KC_DEL, KC_MPLY, \
//     RGB_TOG, RGB_MOD, KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, \
//     KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______, _______, KC_BRIU, \
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_BRID, \
//     _______, _______, _______, _______, _______,          _______, _______, TG(_FN2), TG(_COLOR), _______, KC_MPRV, KC_VOLD, KC_MNXT
//   ),
//
//   [_FN2] = LAYOUT_65(
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//     _______, _______, KC_LALT, KC_LGUI, _______,          _______, _______, _______, _______, _______, _______, _______, _______
//   ),
//
//   [_COLOR] = LAYOUT_65(
//     _______, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, _______, _______, _______, _______, _______, _______, \
//     RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//     _______, _______, _______, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//     _______, _______, _______, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//     _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
//   )
//
  /* [_FN2] = LAYOUT_65( */
  /*   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \ */
  /*   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \ */
  /*   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \ */
  /*   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \ */
  /*   _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______ */
  /* ) */
// };

int currentLayer = BASE;

int getKeyCodeAt(int row, int col) {
  return pgm_read_word(&layers[currentLayer][row][col]);
}

bool isModifier(int keycode) {
  switch (keycode) {
    case K_LCTL:
    case K_LSFT:
    case K_LALT:
    case K_LMET:
    case K_RCTL:
    case K_RSFT:
    case K_RALT:
    case K_RMET:
      return true;
    default: 
      return false;
  }
}

int getModifierCode(int keycode) {
  switch (keycode) {
    case K_LCTL:
      return KEY_MOD_LCTRL;
    case K_LSFT:
      return KEY_MOD_LSHIFT;
    case K_LALT:
      return KEY_MOD_LALT;
    case K_LMET:
      return KEY_MOD_LMETA;
    case K_RCTL:
      return KEY_MOD_RCTRL;
    case K_RSFT:
      return KEY_MOD_RSHIFT;
    case K_RALT:
      return KEY_MOD_RALT;
    case K_RMET:
      return KEY_MOD_RMETA;
  }
}
