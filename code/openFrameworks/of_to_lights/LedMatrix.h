#pragma once

#include "ofMain.h"

#define LED_MATRIX_WIDTH  9
#define LED_MATRIX_HEIGHT 360
#define LED_MATRIX_BOXES 10
#define LED_MATRIX_HEIGHT_PER_BOX 36
#define LED_MATRIX_N_LEDS 3240

class LedMatrix {

public:
	LedMatrix(int baudRate, const std::string& serialPort);

	void setup();
	void set(int x, int y, unsigned char value);
	unsigned char get(int x, int y);
	void fill(unsigned char value);
	void clear();
	void flush();

private:

	int baudRate;
	std::string serialPort;
	unsigned char LedMatrix2D[LED_MATRIX_WIDTH][LED_MATRIX_HEIGHT];
	unsigned char led_string[LED_MATRIX_N_LEDS + 1];
	ofSerial serial;
};
