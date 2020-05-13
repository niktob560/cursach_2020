#ifndef __LAYOUT_H__
#define __LAYOUT_H__ 1

#include <gobjects.h>
#include <avr/pgmspace.h>

#define GOBJECT_PRIMITIVES 	10
#define GOBJECT_TEXTS 		10
#define GOBJECT_BUTTONS 	10

void foo(void);


extern graph_primitive 	LayoutPrimitives[GOBJECT_PRIMITIVES];
extern graph_text 		LayoutTexts 	[GOBJECT_TEXTS];
extern graph_button		LayoutButtons	[GOBJECT_BUTTONS];


static const graph_primitive 	LayoutMainmenuPrimitives[GOBJECT_PRIMITIVES]PROGMEM = {0};
static const graph_text 		LayoutMainmenuTexts 	[GOBJECT_TEXTS]		PROGMEM = {0};
static const graph_button		LayoutMainmenuButtons	[GOBJECT_BUTTONS]	PROGMEM = {0};

static const graph_primitive 	LayoutDateSetPrimitives [GOBJECT_PRIMITIVES]PROGMEM = {0};
static const graph_text 		LayoutDateSetTexts 		[GOBJECT_TEXTS]		PROGMEM = {0};
static const graph_button		LayoutDateSetButtons	[GOBJECT_BUTTONS]	PROGMEM = {0};

static const graph_primitive 	LayoutSettingsPrimitives[GOBJECT_PRIMITIVES]PROGMEM = {0};
static const graph_text 		LayoutSettingsTexts 	[GOBJECT_TEXTS]		PROGMEM = {0};
static const graph_button		LayoutSettingsButtons	[GOBJECT_BUTTONS]	PROGMEM = {0};


/*
* Function: LayoutSet
* Desc:     Установить текущую разметку как указанную
* Input:    prim:	разметка примитивов
*			txt:	разметка текстов
*			btn:	разметка кнопок
* Output:   none
*/
void LayoutSet(const graph_primitive* prim, const graph_text* txt, const graph_button* btn);


/*
* Function: LayoutSetMainmenu
* Desc:     Установить текущую разметку как главное меню
* Input:    none
* Output:   none
*/
static inline void LayoutSetMainmenu()
{
	LayoutSet(LayoutMainmenuPrimitives, LayoutMainmenuTexts, LayoutMainmenuButtons);
}

/*
* Function: LayoutSetDateSet
* Desc:     Установить текущую разметку как установку времени
* Input:    none
* Output:   none
*/
static inline void LayoutSetDateSet()
{
	LayoutSet(LayoutDateSetPrimitives, LayoutDateSetTexts, LayoutDateSetButtons);
}
/*
* Function: LayoutSetSettings
* Desc:     Установить текущую разметку как настройки
* Input:    none
* Output:   none
*/
static inline void LayoutSetSettings()
{
	LayoutSet(LayoutSettingsPrimitives, LayoutSettingsTexts, LayoutSettingsButtons);
}

#endif