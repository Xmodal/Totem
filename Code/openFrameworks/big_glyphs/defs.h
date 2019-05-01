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


#endif