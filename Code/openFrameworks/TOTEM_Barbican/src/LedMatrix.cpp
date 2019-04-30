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

void LedMatrix::drawOnDisplay(int s_size, int s_spacing, int s_xOffset, int s_yOffset) {
	int size = s_size;
	int spacing =  s_spacing;
	int xOffSet = s_xOffset;
	int yOffSet = s_yOffset;

	for (int x = 0; x < LED_MATRIX_WIDTH; x++) {
		for (int y = 0; y < LED_MATRIX_HEIGHT; y++) {
			ofSetColor(LedMatrix2D[x][y], 0 ,0);
			ofDrawRectangle(x * (size + spacing) + xOffSet , y * (size + spacing) + yOffSet , size, size);
		}
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
    if (value < 0)
        value = 0;
	LedMatrix2D[x][y] = value;
}

void LedMatrix::set(int x, int y, unsigned char value, float mix)
{
    set_value = value * mix;
    if (set_value > 254)
        set_value = 254;
    if (set_value < 0)
        set_value = 0;
    LedMatrix2D[x][y] = set_value;
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

