#include <font.h>


void FontScaleUp(uint8_t* target, char c, uint8_t scale)
{
	uint8_t pixmap[8];
	FontGetPixmap(pixmap, c);
	for(uint8_t i = 0; i < (uint8_t)(scale * 8); i++)
	{
		for(uint8_t j = 0; j < (uint8_t)(scale * 10); j++)
		{
			target[j] = setBit(target[j], i, getBit(pixmap[j / 10], i / 8));
		}
	}
}


void FontGetPixmap(uint8_t target[8], const char c)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		target[i] = pgm_read_byte(&(Font8x8[(int)c][i]));
	}
}