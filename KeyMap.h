#ifndef KEY_MAP_H
#define KEY_MAP_H


int getKeyCodeAt(int row, int col);

bool isModifier(int keycode);

int getModifierCode(int keycode);

int getKeyPosition(int row, int col);

int getKeyCodeAtPosition(int position);

void resetLayer();

bool isLayerToggle(int keycode);

void changeLayer(int layer);


#endif
