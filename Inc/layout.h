#ifndef __LAYOUT_H__
#define __LAYOUT_H__ 1

#include <gobjects.h>
#include <avr/pgmspace.h>

#define GOBJECT_PRIMITIVES 	2
#define GOBJECT_TEXTS 		5
#define GOBJECT_BUTTONS 	15

#define LAYOUT_MAINMENU_TEXT_ID_TIME	0
#define LAYOUT_MAINMENU_TEXT_ID_DAY		1
#define LAYOUT_MAINMENU_TEXT_ID_DATE	2

#define LAYOUT_DATESET_TEXT_ID_TIME		0
#define LAYOUT_DATESET_TEXT_ID_DAY		1
#define LAYOUT_DATESET_TEXT_ID_DATE		2

#define LAYOUT_BUTTON_H_UP				0
#define LAYOUT_BUTTON_H_DOWN			1

#define LAYOUT_BUTTON_M_UP 				2
#define LAYOUT_BUTTON_M_DOWN 			3

#define LAYOUT_BUTTON_S_UP 				4
#define LAYOUT_BUTTON_S_DOWN			5

#define LAYOUT_BUTTON_D_UP 				6
#define LAYOUT_BUTTON_D_DOWN 			7

#define LAYOUT_BUTTON_m_UP 				8
#define LAYOUT_BUTTON_m_DOWN 			9

#define LAYOUT_BUTTON_Y_UP 				10
#define LAYOUT_BUTTON_Y_DOWN			11

#define LAYOUT_BUTTON_DAY_UP			12
#define LAYOUT_BUTTON_DAY_DOWN 			13

#define LAYOUT_BUTTON_SUBMIT			14


extern graph_primitive 	LayoutPrimitives[GOBJECT_PRIMITIVES];
extern graph_text 		LayoutTexts 	[GOBJECT_TEXTS];
extern graph_button		LayoutButtons	[GOBJECT_BUTTONS];


static const graph_primitive 	LayoutMainmenuPrimitives[GOBJECT_PRIMITIVES]PROGMEM = {	{{0, 0}, {GLCD_WIDTH, GLCD_HEIGHT}, NOT_FILLED, NOT_BORDERED}};
static const graph_text 		LayoutMainmenuTexts 	[GOBJECT_TEXTS]		PROGMEM = {	{{0, 0}, {GLCD_WIDTH, 20}, NOT_INVERTED, "00:00:00", 2},	/*время*/
																						{{0, 28}, {GLCD_WIDTH, 10}, NOT_INVERTED, "SAT", 1},	/*день недели*/
																						{{8, 41}, {GLCD_WIDTH, 15}, NOT_INVERTED, "01.01.2000", 1.5}	/*дата*/
																						};
static const graph_button		LayoutMainmenuButtons	[GOBJECT_BUTTONS]	PROGMEM = {0};

static const graph_primitive 	LayoutDateSetPrimitives [GOBJECT_PRIMITIVES]PROGMEM = {	{{0, 0}, {GLCD_WIDTH, GLCD_HEIGHT}, NOT_FILLED, NOT_BORDERED}};
static const graph_text 		LayoutDateSetTexts 		[GOBJECT_TEXTS]		PROGMEM = {	{{0, 10}, {GLCD_WIDTH, 10}, INVERTED, "00:00:00", 1},	/*время*/
																						{{0, 44}, {24, 10}, INVERTED, "SAT", 1},			/*день недели*/
																						{{48, 44}, {GLCD_WIDTH, 10}, INVERTED, "01.01.2000", 1}	/*дата*/
																						};
static const graph_button		LayoutDateSetButtons	[GOBJECT_BUTTONS]	PROGMEM = { {{4, 0}, {8, 10}, FILLED, {2}, 1, 0},		/*часы*/
																						{{4, 20}, {8, 10}, FILLED, {3}, 1, 1},

																						{{28, 0}, {8, 10}, FILLED, {2}, 1, 2},		/*минуты*/
																						{{28, 20}, {8, 10}, FILLED, {3}, 1, 3},

																						{{52, 0}, {8, 10}, FILLED, {2}, 1, 4},		/*секунды*/
																						{{52, 20}, {8, 10}, FILLED, {3}, 1, 5},

																						{{52, 34}, {8, 10}, FILLED, {2}, 1, 6},		/*день*/
																						{{52, 54}, {8, 10}, FILLED, {3}, 1, 7},

																						{{76, 34}, {8, 10}, FILLED, {2}, 1, 8},		/*месяц*/
																						{{76, 54}, {8, 10}, FILLED, {3}, 1, 9},

																						{{108, 34}, {8, 10}, FILLED, {2}, 1, 10},	/*год*/
																						{{108, 54}, {8, 10}, FILLED, {3}, 1, 11},	

																						{{8, 34}, {8, 10}, FILLED, {2}, 1, 12},		/*день недели*/
																						{{8, 54}, {8, 10}, FILLED, {3}, 1, 13},

																						{{72, 10}, {8 * 6, 10}, NOT_FILLED, "SUBMIT", 1, 14}	/*SUBMIT*/
																						};

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
* Function: LayoutDraw
* Desc:     Отрисовть текущую разметку
* Input:    none
* Output:   none
*/
void LayoutDraw(void);

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