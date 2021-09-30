#include "KeyReport.h"

#include "HIDKeys.h"

KeyReport::KeyReport(void) {
  _modifiers = KEY_NONE;
  _wasKeyPressed = false;
  _hadKeyOverflow = false;
  _nKeysDefined = 0;

  for (int i = 0; i < 6; i ++) {
    _keys[i] = KEY_NONE;
  }
}

void KeyReport::addModifier(int modifierCode) {
  _wasKeyPressed = true;
  _modifiers += modifierCode;
}

void KeyReport::addKey(int keyCode) {
  _wasKeyPressed = true;

  if (_nKeysDefined < 6) {
    _keys[_nKeysDefined] = keyCode;
    _nKeysDefined += 1;
  } else {
    _hadKeyOverflow = true;
  }
}

bool KeyReport::wasKeyPressed(void) {
  return _wasKeyPressed;
}

bool KeyReport::hadKeyOverflow(void) {
  return _hadKeyOverflow;
}

int KeyReport::getModifier(void) {
  return _modifiers;
}

int* KeyReport::getKeys(void) {
  return _keys;
}


