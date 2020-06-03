#ifndef __FONT_H__
#define __FONT_H__ 1


#include <main.h>
#include <avr/pgmspace.h>

static const uint8_t Font8x8[256][8] PROGMEM = 
{
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0/ --> 
	{ 0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00}, //1/ --> 
	{ 0x00, 0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08}, //2/ --> 
	{ 0x10, 0x30, 0x70, 0xF0, 0x70, 0x30, 0x10, 0x00}, //3/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0xFE, 0x7C, 0x38, 0x10}, //4/ --> 
	{ 0x10, 0x38, 0x7C, 0xFE, 0x00, 0x00, 0x00, 0x00}, //5/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //6/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //7/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //8/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //9/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //10/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //11/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //12/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //13/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //14/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //15/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //16/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //17/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //18/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //19/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //20/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //21/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //22/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //23/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //24/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //25/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //26/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //27/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //28/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //29/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //30/ --> 
	{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, //31/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //32/ --> 
	{ 0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x00, 0x00}, //33/ --> !
	{ 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00}, //34/ --> "
	{ 0x00, 0x24, 0x7E, 0x24, 0x24, 0x7E, 0x24, 0x00}, //35/ --> #
	{ 0x00, 0x44, 0x4A, 0xFF, 0x4A, 0x32, 0x00, 0x00}, //36/ --> $
	{ 0x02, 0x45, 0x22, 0x10, 0x08, 0x44, 0xA2, 0x40}, //37/ --> %
	{ 0x00, 0x60, 0x94, 0x8A, 0x54, 0x20, 0x50, 0x80}, //38/ --> &
	{ 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00}, //39/ --> '
	{ 0x00, 0x00, 0x00, 0x3C, 0x42, 0x81, 0x00, 0x00}, //40/ --> (
	{ 0x00, 0x00, 0x81, 0x42, 0x3C, 0x00, 0x00, 0x00}, //41/ --> )
	{ 0x00, 0x00, 0x05, 0x02, 0x05, 0x00, 0x00, 0x00}, //42/ --> *
	{ 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00}, //43/ --> +
	{ 0x00, 0x00, 0x00, 0x60, 0xE0, 0x00, 0x00, 0x00}, //44/ --> ,
	{ 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00}, //45/ --> -
	{ 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00}, //46/ --> .
	{ 0x00, 0x80, 0x60, 0x18, 0x06, 0x01, 0x00, 0x00}, //47/ --> /
	{ 0x00, 0x3C, 0x62, 0x5A, 0x46, 0x3C, 0x00, 0x00}, //48/ --> 0
	{ 0x00, 0x00, 0x00, 0x04, 0x7E, 0x00, 0x00, 0x00}, //49/ --> 1
	{ 0x00, 0x00, 0x62, 0x52, 0x4A, 0x4E, 0x00, 0x00}, //50/ --> 2
	{ 0x00, 0x00, 0x42, 0x42, 0x4A, 0x34, 0x00, 0x00}, //51/ --> 3
	{ 0x00, 0x00, 0x1E, 0x10, 0x10, 0x7E, 0x00, 0x00}, //52/ --> 4
	{ 0x00, 0x00, 0x9E, 0x92, 0x92, 0x62, 0x00, 0x00}, //53/ --> 5
	{ 0x00, 0x00, 0xFE, 0x92, 0x92, 0xF2, 0x00, 0x00}, //54/ --> 6
	{ 0x00, 0x00, 0x02, 0x72, 0x0A, 0x06, 0x00, 0x00}, //55/ --> 7
	{ 0x00, 0x00, 0x34, 0x4A, 0x4A, 0x34, 0x00, 0x00}, //56/ --> 8
	{ 0x00, 0x00, 0x4E, 0x4A, 0x4A, 0x3E, 0x00, 0x00}, //57/ --> 9
	{ 0x00, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00}, //58/ --> :
	{ 0x00, 0x00, 0x00, 0x6C, 0xEC, 0x00, 0x00, 0x00}, //59/ --> ;
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //60/ --> <
	{ 0x00, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x00}, //61/ --> =
	{ 0x00, 0x00, 0x00, 0x82, 0x44, 0x28, 0x10, 0x00}, //62/ --> >
	{ 0x00, 0x06, 0x01, 0xB1, 0x09, 0x06, 0x00, 0x00}, //63/ --> ?
	{ 0x7E, 0x81, 0x99, 0xA5, 0x95, 0x39, 0x41, 0x7E}, //64/ --> @
	{ 0x00, 0x00, 0xFE, 0x09, 0x09, 0xFE, 0x00, 0x00}, //65/ --> A
	{ 0x00, 0x00, 0xFF, 0x89, 0x89, 0x76, 0x00, 0x00}, //66/ --> B
	{ 0x00, 0x7E, 0x81, 0x81, 0x81, 0x42, 0x00, 0x00}, //67/ --> C
	{ 0x00, 0x00, 0xFF, 0x81, 0x81, 0x81, 0x7E, 0x00}, //68/ --> D
	{ 0x00, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0x00}, //69/ --> E
	{ 0x00, 0x00, 0xFF, 0x09, 0x09, 0x09, 0x00, 0x00}, //70/ --> F
	{ 0x00, 0x7E, 0x81, 0x91, 0x91, 0x72, 0x00, 0x00}, //71/ --> G
	{ 0x00, 0xFF, 0x10, 0x10, 0x10, 0xFF, 0x00, 0x00}, //72/ --> H
	{ 0x00, 0x81, 0x81, 0xFF, 0x81, 0x81, 0x00, 0x00}, //73/ --> I
	{ 0x00, 0x60, 0x80, 0x80, 0x7F, 0x00, 0x00, 0x00}, //74/ --> J
	{ 0x00, 0x00, 0xFF, 0x18, 0x24, 0xC3, 0x00, 0x00}, //75/ --> K
	{ 0x00, 0x00, 0xFF, 0x80, 0x80, 0xC0, 0x00, 0x00}, //76/ --> L
	{ 0x00, 0xFF, 0x02, 0x0C, 0x10, 0x0C, 0x02, 0xFF}, //77/ --> M
	{ 0x00, 0xFF, 0x02, 0x0C, 0x30, 0x40, 0xFF, 0x00}, //78/ --> N
	{ 0x00, 0x7E, 0x81, 0x81, 0x81, 0x7E, 0x00, 0x00}, //79/ --> O
	{ 0x00, 0x00, 0xFF, 0x09, 0x09, 0x06, 0x00, 0x00}, //80/ --> P
	{ 0x00, 0x3E, 0x41, 0x41, 0x21, 0x5E, 0x80, 0x00}, //81/ --> Q
	{ 0x00, 0x00, 0xFF, 0x19, 0x29, 0xC6, 0x00, 0x00}, //82/ --> R
	{ 0x00, 0x46, 0x89, 0x89, 0x89, 0x72, 0x00, 0x00}, //83/ --> S
	{ 0x00, 0x00, 0x01, 0x01, 0xFF, 0x01, 0x01, 0x00}, //84/ --> T
	{ 0x00, 0x00, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x00}, //85/ --> U
	{ 0x00, 0x00, 0x1F, 0x60, 0xC0, 0x60, 0x1F, 0x00}, //86/ --> V
	{ 0x07, 0x38, 0x40, 0x30, 0x40, 0x38, 0x07, 0x00}, //87/ --> W
	{ 0x00, 0x00, 0x81, 0x66, 0x18, 0x66, 0x81, 0x00}, //88/ --> X
	{ 0x00, 0x00, 0x03, 0x04, 0xF8, 0x04, 0x03, 0x00}, //89/ --> Y
	{ 0x00, 0xC1, 0xA1, 0x91, 0x89, 0x85, 0x83, 0x00}, //90/ --> Z
	{ 0x00, 0x00, 0xFF, 0x81, 0x00, 0x00, 0x00, 0x00}, //91/ --> [
	{ 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x00, 0x00}, /*92/ --> \*/
	{ 0x00, 0x00, 0x00, 0x00, 0x81, 0xFF, 0x00, 0x00}, //93/ --> ]
	{ 0x00, 0x04, 0x02, 0x01, 0x02, 0x04, 0x00, 0x00}, //94/ --> ^
	{ 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00}, //95/ --> _
	{ 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00}, //96/ --> `
	{ 0x00, 0x00, 0x48, 0xA4, 0xA4, 0xF8, 0x00, 0x00}, //97/ --> a
	{ 0x00, 0x00, 0xFC, 0xA0, 0xA0, 0x40, 0x00, 0x00}, //98/ --> b
	{ 0x00, 0x00, 0x60, 0x90, 0x90, 0x00, 0x00, 0x00}, //99/ --> c
	{ 0x00, 0x00, 0x40, 0xA0, 0xA0, 0xFC, 0x00, 0x00}, //100/ --> d
	{ 0x00, 0x00, 0x70, 0xA8, 0xA8, 0x10, 0x00, 0x00}, //101/ --> e
	{ 0x00, 0x00, 0x10, 0xFC, 0x14, 0x00, 0x00, 0x00}, //102/ --> f
	{ 0x00, 0x00, 0x48, 0x94, 0x7C, 0x00, 0x00, 0x00}, //103/ --> g
	{ 0x00, 0x00, 0xFC, 0x20, 0x20, 0xC0, 0x00, 0x00}, //104/ --> h
	{ 0x00, 0x00, 0x00, 0xF4, 0x00, 0x00, 0x00, 0x00}, //105/ --> i
	{ 0x00, 0x00, 0x00, 0x80, 0x74, 0x00, 0x00, 0x00}, //106/ --> j
	{ 0x00, 0x00, 0xFE, 0x20, 0x50, 0x88, 0x00, 0x00}, //107/ --> k
	{ 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00}, //108/ --> l
	{ 0x00, 0xF0, 0x10, 0x10, 0xF0, 0x10, 0x10, 0xE0}, //109/ --> m
	{ 0x00, 0x00, 0xF0, 0x10, 0x10, 0xE0, 0x00, 0x00}, //110/ --> n
	{ 0x00, 0x00, 0x60, 0x90, 0x90, 0x60, 0x00, 0x00}, //111/ --> o
	{ 0x00, 0x00, 0xF0, 0x28, 0x28, 0x10, 0x00, 0x00}, //112/ --> p
	{ 0x00, 0x00, 0x10, 0x28, 0xF0, 0x00, 0x00, 0x00}, //113/ --> q
	{ 0x00, 0x00, 0xE0, 0x10, 0x10, 0x20, 0x00, 0x00}, //114/ --> r
	{ 0x00, 0x00, 0x48, 0x94, 0xA4, 0x48, 0x00, 0x00}, //115/ --> s
	{ 0x00, 0x00, 0x10, 0xFC, 0x90, 0x00, 0x00, 0x00}, //116/ --> t
	{ 0x00, 0x00, 0x70, 0x80, 0xF0, 0x00, 0x00, 0x00}, //117/ --> u
	{ 0x00, 0x3C, 0x60, 0x80, 0x60, 0x3C, 0x00, 0x00}, //118/ --> v
	{ 0x1C, 0x30, 0x60, 0x30, 0x60, 0x30, 0x1C, 0x00}, //119/ --> w
	{ 0x00, 0x00, 0x90, 0x60, 0x90, 0x00, 0x00, 0x00}, //120/ --> x
	{ 0x00, 0x00, 0x4C, 0x90, 0x7C, 0x00, 0x00, 0x00}, //121/ --> y
	{ 0x00, 0x00, 0x88, 0xC8, 0xA8, 0x98, 0x00, 0x00}, //122/ --> z
	{ 0x00, 0x00, 0x10, 0x6C, 0x82, 0x00, 0x00, 0x00}, //123/ --> {
	{ 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00}, //124/ --> |
	{ 0x00, 0x00, 0x00, 0x00, 0x82, 0x6C, 0x10, 0x00}, //125/ --> }
	{ 0x00, 0x10, 0x08, 0x08, 0x10, 0x10, 0x08, 0x00}, //126/ --> ~
	{ 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00}, //127/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //128/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //129/ --> 
	{ 0x00, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x00}, //130/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //131/ --> 
	{ 0x00, 0x00, 0x80, 0x40, 0x80, 0x40, 0x00, 0x00}, //132/ --> 
	{ 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00}, //133/ --> 
	{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, //134/ --> 
	{ 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF}, //135/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //136/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //137/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //138/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //139/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //140/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //141/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //142/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //143/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //144/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //145/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //146/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //147/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //148/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //149/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //150/ --> 
	{ 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08}, //151/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //152/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //153/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //154/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //155/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //156/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //157/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //158/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //159/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //160/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //161/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //162/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //163/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //164/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //165/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //166/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //167/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //168/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //169/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //170/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //171/ --> 
	{ 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0C, 0x00}, //172/ --> 
	{ 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00}, //173/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //174/ --> 
	{ 0x00, 0x00, 0x02, 0xF8, 0x02, 0x00, 0x00, 0x00}, //175/ --> 
	{ 0x00, 0x00, 0x02, 0x05, 0x02, 0x00, 0x00, 0x00}, //176/ --> 
	{ 0x00, 0x00, 0x48, 0x5C, 0x48, 0x00, 0x00, 0x00}, //177/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //178/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //179/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //180/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //181/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //182/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00}, //183/ --> 
	{ 0x00, 0x00, 0x78, 0x95, 0x94, 0x49, 0x00, 0x00}, //184/ --> 
	{ 0xFF, 0x0C, 0x30, 0xFF, 0x00, 0x12, 0x15, 0x12}, //185/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //186/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //187/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //188/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //189/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //190/ --> 
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //191/ --> 
	{ 0x00, 0x00, 0xFE, 0x09, 0x09, 0xFE, 0x00, 0x00}, //192/ --> 
	{ 0x00, 0x00, 0xFF, 0x91, 0x91, 0x61, 0x00, 0x00}, //193/ --> 
	{ 0x00, 0x00, 0xFF, 0x89, 0x89, 0x76, 0x00, 0x00}, //194/ --> 
	{ 0x00, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x00}, //195/ --> 
	{ 0x00, 0xC0, 0x7F, 0x41, 0x41, 0x7F, 0xC0, 0x00}, //196/ --> 
	{ 0x00, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0x00}, //197/ --> 
	{ 0xC3, 0x24, 0x18, 0xFF, 0x18, 0x24, 0xC3, 0x00}, //198/ --> 
	{ 0x00, 0x00, 0x42, 0x89, 0x89, 0x76, 0x00, 0x00}, //199/ --> 
	{ 0x00, 0x00, 0xFE, 0x40, 0x20, 0x10, 0xFE, 0x00}, //200/ --> 
	{ 0x00, 0x00, 0xFE, 0x40, 0x21, 0x10, 0xFE, 0x00}, //201/ --> 
	{ 0x00, 0x00, 0xFF, 0x18, 0x24, 0x42, 0x81, 0x00}, //202/ --> 
	{ 0x00, 0x00, 0x80, 0xFE, 0x01, 0x01, 0xFF, 0x00}, //203/ --> 
	{ 0x00, 0xFF, 0x06, 0x0C, 0x10, 0x0C, 0x06, 0xFF}, //204/ --> 
	{ 0x00, 0x00, 0xFF, 0x08, 0x08, 0xFF, 0x00, 0x00}, //205/ --> 
	{ 0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x7E, 0x00}, //206/ --> 
	{ 0x00, 0x00, 0xFF, 0x01, 0x01, 0x01, 0xFF, 0x00}, //207/ --> 
	{ 0x00, 0x00, 0xFF, 0x09, 0x09, 0x09, 0x06, 0x00}, //208/ --> 
	{ 0x00, 0x7E, 0x81, 0x81, 0x81, 0x42, 0x00, 0x00}, //209/ --> 
	{ 0x00, 0x01, 0x01, 0xFF, 0x01, 0x01, 0x00, 0x00}, //210/ --> 
	{ 0x00, 0x00, 0x47, 0x88, 0x88, 0x7F, 0x00, 0x00}, //211/ --> 
	{ 0x0F, 0x09, 0x09, 0xFF, 0x09, 0x09, 0x0F, 0x00}, //212/ --> 
	{ 0x81, 0x66, 0x18, 0x66, 0x81, 0x00, 0x00, 0x00}, //213/ --> 
	{ 0x00, 0x7F, 0x40, 0x40, 0x40, 0x7F, 0xC0, 0x00}, //214/ --> 
	{ 0x00, 0x00, 0x07, 0x08, 0x08, 0xFF, 0x00, 0x00}, //215/ --> 
	{ 0x7F, 0x40, 0x40, 0x7F, 0x40, 0x40, 0x7F, 0x00}, //216/ --> 
	{ 0x7F, 0x40, 0x40, 0x7F, 0x40, 0x40, 0x7F, 0xC0}, //217/ --> 
	{ 0x00, 0x01, 0x01, 0x01, 0xFE, 0x90, 0x90, 0x60}, //218/ --> 
	{ 0x00, 0xFF, 0x90, 0x90, 0x60, 0x00, 0xFF, 0x00}, //219/ --> 
	{ 0x00, 0x00, 0xFF, 0x90, 0x90, 0x60, 0x00, 0x00}, //220/ --> 
	{ 0x00, 0x00, 0x52, 0x89, 0x91, 0x4A, 0x3C, 0x00}, //221/ --> 
	{ 0x00, 0xFE, 0x10, 0x10, 0x7C, 0x82, 0x82, 0x7C}, //222/ --> 
	{ 0x00, 0x00, 0x86, 0x49, 0x29, 0xFF, 0x00, 0x00}, //223/ --> 
	{ 0x00, 0x00, 0x48, 0xA4, 0xA4, 0xF8, 0x00, 0x00}, //224/ --> 
	{ 0x00, 0x00, 0x7C, 0x92, 0x91, 0x60, 0x00, 0x00}, //225/ --> 
	{ 0x00, 0x00, 0xFC, 0x94, 0x94, 0x68, 0x00, 0x00}, //226/ --> 
	{ 0x00, 0x00, 0xF0, 0x10, 0x10, 0x00, 0x00, 0x00}, //227/ --> 
	{ 0x00, 0x80, 0x7C, 0x44, 0x7C, 0x80, 0x00, 0x00}, //228/ --> 
	{ 0x00, 0x78, 0x94, 0x94, 0x58, 0x00, 0x00, 0x00}, //229/ --> 
	{ 0x00, 0xD8, 0x20, 0xF8, 0x20, 0xD8, 0x00, 0x00}, //230/ --> 
	{ 0x00, 0x00, 0x50, 0x88, 0xA8, 0x50, 0x00, 0x00}, //231/ --> 
	{ 0x00, 0x00, 0x70, 0x80, 0x80, 0xF0, 0x00, 0x00}, //232/ --> 
	{ 0x00, 0x00, 0x70, 0x84, 0x84, 0xF0, 0x00, 0x00}, //233/ --> 
	{ 0x00, 0x00, 0xF8, 0x20, 0x50, 0x88, 0x00, 0x00}, //234/ --> 
	{ 0x00, 0x00, 0x80, 0xF0, 0x10, 0xF0, 0x00, 0x00}, //235/ --> 
	{ 0x00, 0xF8, 0x10, 0x20, 0x10, 0xF8, 0x00, 0x00}, //236/ --> 
	{ 0x00, 0x00, 0xF8, 0x20, 0x20, 0xF8, 0x00, 0x00}, //237/ --> 
	{ 0x00, 0x78, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00}, //238/ --> 
	{ 0x00, 0x00, 0xF0, 0x10, 0x10, 0xF0, 0x00, 0x00}, //239/ --> 
	{ 0x00, 0x00, 0xFC, 0x24, 0x24, 0x18, 0x00, 0x00}, //240/ --> 
	{ 0x00, 0x70, 0x88, 0x88, 0x50, 0x00, 0x00, 0x00}, //241/ --> 
	{ 0x00, 0x00, 0x10, 0xF0, 0x10, 0x00, 0x00, 0x00}, //242/ --> 
	{ 0x00, 0x00, 0x98, 0xA0, 0x78, 0x00, 0x00, 0x00}, //243/ --> 
	{ 0x00, 0x00, 0x10, 0x28, 0xF8, 0x28, 0x10, 0x00}, //244/ --> 
	{ 0x00, 0x00, 0x90, 0x60, 0x90, 0x00, 0x00, 0x00}, //245/ --> 
	{ 0x00, 0x00, 0x78, 0x40, 0x78, 0xC0, 0x00, 0x00}, //246/ --> 
	{ 0x00, 0x00, 0x18, 0x20, 0xF8, 0x00, 0x00, 0x00}, //247/ --> 
	{ 0x00, 0x00, 0x78, 0x40, 0x78, 0x40, 0x78, 0x00}, //248/ --> 
	{ 0x00, 0x00, 0x78, 0x40, 0x78, 0x40, 0x78, 0xC0}, //249/ --> 
	{ 0x08, 0x08, 0xF8, 0xA0, 0xA0, 0x40, 0x00, 0x00}, //250/ --> 
	{ 0x00, 0xF8, 0xA0, 0x40, 0x00, 0xF8, 0x00, 0x00}, //251/ --> 
	{ 0x00, 0x00, 0xF8, 0xA0, 0x40, 0x00, 0x00, 0x00}, //252/ --> 
	{ 0x00, 0x00, 0x00, 0xA8, 0xA8, 0x70, 0x00, 0x00}, //253/ --> 
	{ 0x00, 0x00, 0xF0, 0x40, 0x60, 0x90, 0x60, 0x00}, //254/ --> 
	{ 0x00, 0x00, 0x88, 0x54, 0xFC, 0x00, 0x00, 0x00}, //255/ -->
};


void FontScaleUp(uint8_t* target, const char c, const uint8_t scale);

void FontGetPixmap(uint8_t target[8], const char c);

#endif