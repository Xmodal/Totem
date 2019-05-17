#pragma once

#ifndef LED_MATRIX_
#define LED_MATRIX_

#include "ofMain.h"
#include "DefsLedMatrix.h"

class LedMatrix {

public:
	LedMatrix(int baudRate, const std::string& serialPort, bool display);
	LedMatrix(int baudRate, const std::string& serialPortPrefix, int serialPortIndex, bool display);

	void init(int baudRate, const std::string& serialPort, bool display);

	void setup();
	void set(int x, int y, unsigned char value);
    void set(int x, int y, unsigned char value, float mix);
    void addTo(int x, int y, unsigned char value, float mix);
	unsigned char get(int x, int y);
	void fill(unsigned char value);

	void write(int x, int y, int w, int h, unsigned char* value);

	void drawOnDisplay(int s_size, int s_spacing, int s_xOffset, int s_yOffset) ;
	bool display;

	void clear();
	void flush();
    int check();

private:

	int baudRate;
	std::string serialPort;
    unsigned char set_value;
	unsigned char LedMatrix2D[LED_MATRIX_WIDTH][LED_MATRIX_HEIGHT];
	unsigned char led_string[LED_MATRIX_N_LEDS + 1];
	ofSerial serial;
    int timeSinceLastOutput;

};

#endif
