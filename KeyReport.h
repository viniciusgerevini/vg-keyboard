#ifndef _KeyReport_H_
#define _KeyReport_H_

#include "HIDKeys.h"

class KeyReport {
  public:
    KeyReport(void);

    void addModifier(int modifierCode);

    void addKey(int keyCode);

    bool wasKeyPressed(void);

    bool hadKeyOverflow(void);

    int getModifier(void);

    int* getKeys(void);

  private:
    int _modifiers;
    int _keys[6];
    bool _wasKeyPressed;
    bool _hadKeyOverflow;
    int _nKeysDefined;
};

#endif
