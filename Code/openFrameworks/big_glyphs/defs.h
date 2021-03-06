#pragma once

#ifndef DEFS_INC_
#define DEFS_INC_

#define LED_MATRIX_WIDTH  9
#define LED_MATRIX_HEIGHT 396 // MATT: I think the total height of the LED matrix is wrong: I had an offset of 36 pixels which indicates that there might be 11 boxes, not 10
//#define LED_MATRIX_HEIGHT 360
#define LED_MATRIX_BOXES 11
#define LED_MATRIX_HEIGHT_PER_BOX 36
#define LED_MATRIX_N_LEDS (LED_MATRIX_WIDTH*LED_MATRIX_HEIGHT)

#define BLOCK_SIDE 3
#define N_TOP_BLOCKS 4

enum GlyphType {
	TYPE_I,
	TYPE_L,
	TYPE_T,
	TYPE_U,
	TYPE_O,
	TYPE_VOID,
	N_TYPES
};
const int MAX_TYPE = N_TYPES - 1;

enum GlyphRotation {
	ROTATION_0,
	ROTATION_90,
	ROTATION_180,
	ROTATION_270,
	N_ROTATIONS
};
const int MAX_ROTATION = N_ROTATIONS - 1;

enum GlyphTranslation {
	TRANSLATION_TOP,
	TRANSLATION_MIDDLE,
	TRANSLATION_BOTTOM,
	N_TRANSLATIONS
};
const int MAX_TRANSLATION = N_TRANSLATIONS - 1;


#endif