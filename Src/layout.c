#include <layout.h>


graph_primitive LayoutPrimitives 	[GOBJECT_PRIMITIVES];
graph_text 		LayoutTexts 		[GOBJECT_TEXTS];
graph_button	LayoutButtons	 	[GOBJECT_BUTTONS];


void LayoutSet(const graph_primitive* prim, const graph_text* txt, const graph_button* btn)
{
	uint8_t primArray[GOBJECT_PRIMITIVE_ARRAY_SIZE],
			txtArray[GOBJECT_TEXT_ARRAY_SIZE],
			btnArray[GOBJECT_BUTTON_ARRAY_SIZE];

	for(uint8_t i = 0; i < sizeof(primArray); i++)
		primArray[i] = pgm_read_byte(&prim[i]);;

	for(uint8_t i = 0; i < sizeof(txtArray); i++)
		txtArray[i] = pgm_read_byte(&txt[i]);;

	for(uint8_t i = 0; i < sizeof(btnArray); i++)
		btnArray[i] = pgm_read_byte(&btn[i]);

	GOBJECTArrayToPrimitive	((const uint8_t*)&primArray, LayoutPrimitives);
	GOBJECTArrayToText		((const uint8_t*)&txtArray, LayoutTexts);
	GOBJECTArrayToButton	((const uint8_t*)&btnArray, LayoutButtons);
}

void LayoutDrawPrimitives(void)
{
	for(uint8_t i = 0; i < GOBJECT_PRIMITIVES; i++)
	{
		GOBJECTDrawPrimitive(&LayoutPrimitives[i]);
	}
}

void LayoutDrawTexts(void)
{
	for(uint8_t i = 0; i < GOBJECT_TEXTS; i++)
	{
		GOBJECTDrawText(&LayoutTexts[i]);
	}
}

void LayoutDrawButtons(void)
{
	for(uint8_t i = 0; i < GOBJECT_BUTTONS; i++)
	{
		GOBJECTDrawButton(&LayoutButtons[i]);
	}
}

void LayoutDraw(void)
{
	LayoutDrawPrimitives();
	LayoutDrawTexts();
	LayoutDrawButtons();
}