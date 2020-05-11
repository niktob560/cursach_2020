#ifndef __FONT_H__
#define __FONT_H__

#include "main.h"

extern const uint8_t Font8x8[256][8];

void FontScaleUp(uint8_t* target, const char c, const uint8_t scale);

#endif