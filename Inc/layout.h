#ifndef __LAYOUT_H__
#define __LAYOUT_H__ 1

#include <gobjects.h>
#include <avr/pgmspace.h>

#define GOBJECT_PRIMITIVES 	10
#define GOBJECT_TEXTS 		10
#define GOBJECT_BUTTONS 	10

void foo(void);

typedef struct 
{
	graph_primitive 	primitives 	[GOBJECT_PRIMITIVES];
	graph_text 			texts 		[GOBJECT_TEXTS];
	graph_button		buttons 	[GOBJECT_BUTTONS];
} layout_page;

void LayoutConvertToArray(uint8_t* target, layout_page* page)
{
	*target = (uint8_t)page->texts[0].inverted;
}

#endif