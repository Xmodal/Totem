#include "LedMatrix.h"

LedMatrix::LedMatrix(int baudRate_, const std::string& serialPort_, bool display_)
{
	init(baudRate_, serialPort_, display_);
}

LedMatrix::LedMatrix(int baudRate_, const std::string& serialPortPrefix_, int serialPortIndex_, bool display_)
{
	int currentIndex = 0;
	std::string foundSerialPort;
	vector<ofSerialDeviceInfo> devices = serial.getDeviceList();
	for (vector<ofSerialDeviceInfo>::iterator it = devices.begin(); it != devices.end(); ++it) {
		// Check if match prefix.
		if (it->getDevicePath().rfind(serialPortPrefix_, 0) == 0) {
			if (currentIndex == serialPortIndex_) {
				foundSerialPort = it->getDevicePath();
				break;
			}
			else
				currentIndex++;
		}
	}

	// Initialize with the found serial port.
	init(baudRate_, foundSerialPort, display_);
}

void LedMatrix::init(int baudRate_, const std::string& serialPort_, bool display_) {
	baudRate = baudRate_;
	display = display_;
	serialPort = serialPort_;

	if (display)
		std::cout << "Sending display & serial" << std::endl;
	else
		std::cout << "Sending serial only" << std::endl;
}

void LedMatrix::drawOnDisplay(int s_size, int s_spacing, int s_xOffset, int s_yOffset) {
	int size = s_size;
	int spacing = s_spacing;
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
	// serial.listDevices();
	// vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
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

void LedMatrix::set(int x, int y, unsigned char value, float mix)
{
    set_value = value * mix;
    if (set_value > 254)
        set_value = 254;
    if (set_value < 0)
        set_value = 0;
    LedMatrix2D[x][y] = set_value;
}

void LedMatrix::addTo(int x, int y, unsigned char value, float mix)
{
    set_value = value * mix;
    if (set_value > 254)
        set_value = 254;
    if (set_value < 0)
        set_value = 0;
    LedMatrix2D[x][y] += set_value;
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

	for (int i = 0; i < LED_MATRIX_HEIGHT; i++) {
		for (int j = 0; j < LED_MATRIX_WIDTH; j++) {
			led_string[totalPass++] = LedMatrix2D[j][i];
		}
	}
	serial.writeBytes(led_string, LED_MATRIX_N_LEDS + 1);
}

int LedMatrix::check() {
    if(serial.available()){
        while(serial.available()>0){
            if(serial.readByte() == 255){
                timeSinceLastOutput = serial.readByte();
                //std::cout << this << " : time since last output : " << timeSinceLastOutput << " ms" << std::endl;
                return timeSinceLastOutput;
            }
        }
    }
		// Not sure it this is appropriate.
		return 0;
}
