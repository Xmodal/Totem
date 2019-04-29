#pragma once

#ifndef LED_MATRIX_
#define LED_MATRIX_

#include "ofMain.h"
#include "defs.h"

class LedMatrix {

public:
	LedMatrix(int baudRate, const std::string& serialPort, bool display);

	void setup();
	void set(int x, int y, unsigned char value);
	unsigned char get(int x, int y);
	void fill(unsigned char value);

	void write(int x, int y, int w, int h, unsigned char* value);

	void drawOnDisplay();

	void clear();
	void flush();

private:

	int baudRate;
	bool display;
	std::string serialPort;
	unsigned char LedMatrix2D[LED_MATRIX_WIDTH][LED_MATRIX_HEIGHT];
	unsigned char led_string[LED_MATRIX_N_LEDS + 1];
	ofSerial serial;
};

#endif