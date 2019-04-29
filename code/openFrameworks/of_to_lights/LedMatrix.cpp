#include "LedMatrix.h"


LedMatrix::LedMatrix(int baudRate_, const std::string& serialPort_, bool toDisplay) : baudRate(baudRate_), serialPort(serialPort_)
{
	display = toDisplay;
	if (display)
	{
		std::cout << "Sending display & serial" << std::endl;
	}
	else
		std::cout << "Sending serial only" << std::endl;

	
	//serial.listDevices();
	//vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
}

void LedMatrix::drawOnDisplay() {
	int size = 35;
	int spacing = size + 3;
	int xOffSet = 0;
	int yOffSet = 0;

	for (int x = 0; x < LED_MATRIX_WIDTH; x++) {
		for (int y = 0; y < LED_MATRIX_HEIGHT; y++) {
			if (y * spacing > yOffSet + 3500) {
				xOffSet += LED_MATRIX_WIDTH * size + 30;
				yOffSet += y * spacing;
			}
			ofSetColor(LedMatrix2D[x][y]);
			ofDrawRectangle((x * spacing) + xOffSet , (y * spacing) - yOffSet , size, size);
		}
		xOffSet = 0;
		yOffSet = 0;
	}
}

void LedMatrix::setup()
{
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	serial.setup(serialPort, baudRate);
	//setup the led with nothing on it
	clear();
	flush();
}

void LedMatrix::set(int x, int y, unsigned char value)
{
	if (value > 254)
		value = 254;
	LedMatrix2D[x][y] = value;
}

unsigned char LedMatrix::get(int x, int y)
{
	return LedMatrix2D[x][y];
}

void LedMatrix::fill(unsigned char value = 10)
{
	//set nothing to be on the screen
	for (int i = 0; i < LED_MATRIX_WIDTH; i++) {
		for (int j = 0; j < LED_MATRIX_HEIGHT; j++) {
			LedMatrix2D[i][j] = value;
		}
	}
}

void LedMatrix::write(int x, int y, int w, int h, unsigned char* value)
{
	int k = 0;
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			set(x + i, y + j, value[k++]);
		}
	}
}

void LedMatrix::clear() {
	fill(0);
}

void LedMatrix::flush() {
	//print to serial.
	int totalPass = 0;
	led_string[totalPass++] = 255;

	for (int i = 0; i < LED_MATRIX_WIDTH; i++) {
		for (int j = 0; j < LED_MATRIX_HEIGHT; j++) {
			led_string[totalPass++] = LedMatrix2D[i][j];
		}
	}

	serial.writeBytes(led_string, LED_MATRIX_N_LEDS + 1);
}

