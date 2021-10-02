#include <Arduino.h>
#include "KeyMap.h"
#include "HIDKeys.h"

#define NUMBER_OF_LAYERS 3
#define NUMBER_OF_ROWS 5
#define NUMBER_OF_COLS 16

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

#define K_PSCR   KEY_SYSRQ
#define K_HOME   KEY_HOME
#define K_PGUP   KEY_PAGEUP
#define K_DEL    KEY_DELETE
#define K_END    KEY_END
#define K_PGDN   KEY_PAGEDOWN
#define K_RGHT   KEY_RIGHT
#define K_LEFT   KEY_LEFT
#define K_DOWN   KEY_DOWN
#define K_UP     KEY_UP

#define K_MUTE   KEY_MUTE
#define K_VOLU   KEY_VOLUMEUP
#define K_VOLD   KEY_VOLUMEDOWN

#define K_MPLY   KEY_MEDIA_PLAYPAUSE
#define K_MPRV   KEY_MEDIA_PREVIOUSSONG
#define K_MNXT   KEY_MEDIA_NEXTSONG
#define K_MBCK   KEY_MEDIA_BACK
#define M_MFWD   KEY_MEDIA_FORWARD

// LAYERS
#define BASE 0
#define FN_1 1
#define MACOS 2

#define K_MACOS 402
#define K_FN_1 301

const int layers[NUMBER_OF_LAYERS][NUMBER_OF_ROWS * NUMBER_OF_COLS] PROGMEM = {
  [BASE] = {
     K_GRV,   KEY_1,   KEY_2,   KEY_3,   KEY_4,   KEY_5,   KEY_6,   KEY_7,   KEY_8,   KEY_9,   KEY_0,   K_MINS,  K_EQL ,  _______, K_BSPC,  K_HOME,
     K_TAB,   KEY_Q,   KEY_W,   KEY_E,   KEY_R,   KEY_T,   _______, KEY_Y,   KEY_U,   KEY_I,   KEY_O,   KEY_P,   K_LBRC,  K_RBRC,  K_BSLS,  K_END ,
     K_ESC,   KEY_A,   KEY_S,   KEY_D,   KEY_F,   KEY_G,   _______, KEY_H,   KEY_J,   KEY_K,   KEY_L,   K_SCLN,  K_QUOT,  _______, K_ENT,   K_PGUP,
     K_LSFT,  KEY_Z,   KEY_X,   KEY_C,   KEY_V,   KEY_B,   _______, KEY_N,   KEY_M,   K_COMM,  K_DOT,   K_SLSH,  _______, K_RSFT,  K_UP,    K_PGDN,
     K_LCTL,  K_FN_1,  K_LMET,  K_LALT,  K_SPC,   _______, _______, _______, K_SPC,   _______, K_RMET,  K_RALT,  K_RCTL,  K_LEFT,  K_DOWN,  K_RGHT
  },
  [FN_1] = {
     K_ESC,   KEY_F1,  KEY_F2,  KEY_F3,  KEY_F4,  KEY_F5,  KEY_F6,  KEY_F7,  KEY_F8,  KEY_F9,  KEY_F10, KEY_F11, KEY_F12, _______, K_DEL,   K_MPLY ,
     _______, _______, K_UP,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, K_MUTE ,
     _______, K_LEFT,  K_DOWN,  K_RGHT,  _______, _______, _______, K_LEFT,  K_DOWN,  K_UP,    K_RGHT,  _______, _______, _______, _______, K_PSCR ,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, K_VOLU,  _______ ,
     _______, _______, K_MACOS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, K_MPRV,  K_VOLD,  K_MNXT
  },

  [MACOS] = {
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
     _______, _______, K_LALT,  K_LMET,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
  },
};

// [TEMPLATE] = {
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
// },


int permanentOverlay = BASE;
int temporaryOverlay = BASE;

int getKeyCodeAt(int row, int col) {
  return getKeyCodeAtPosition(getKeyPosition(row, col));
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

int getKeyPosition(int row, int col) {
  return (row * NUMBER_OF_COLS) + col;
}

int getKeyCodeAtPosition(int position) {
   int keycode;

   if (temporaryOverlay != BASE) {
      keycode = pgm_read_word(&layers[temporaryOverlay][position]);

      if (keycode != _______) {
         return keycode;
      }
   }

   keycode = pgm_read_word(&layers[permanentOverlay][position]);

   if (keycode == _______ && permanentOverlay != BASE) {
     keycode = pgm_read_word(&layers[BASE][position]);
   }

   return keycode;
};

void resetLayer() {
   temporaryOverlay = BASE;
}

bool isLayerToggle(int keycode) {
   return keycode > 300;
}

void changeLayer(int layer) {
  if (layer > 400) {
    int overlay = layer - 400;

    if (permanentOverlay == BASE) {
      permanentOverlay = overlay;
    } else {
      permanentOverlay = BASE;
    }
  } else if (layer > 300) {
    temporaryOverlay = layer - 300;
  }
}
