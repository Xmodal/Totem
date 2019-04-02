#include "ofApp.h"

const static int NB_LEDS = 3240;     // 9 col * 36 lines * 10 boxes
unsigned char led_string[NB_LEDS + 1];

//SERIAL FORMAT
//The first byte has to be 255	(the teensy reads 255 as the beginning of a new led array)
//All other bytes have to be between 0 and 254


void ofApp::setup() {

	//Serial
	int baud = 2500000;

	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

	serial.setup("COM3", baud);
	led_string[0] = 255;
	for (int i = 0; i < NB_LEDS; i++)
	{
		led_string[i + 1] = 0;
	}
	serial.writeBytes(led_string, NB_LEDS + 1);
}

void ofApp::update() {
	for (int i = 0; i < NB_LEDS; i++) {
		//led_string[i+1] = neuronToLED(spike_net.neurons[i].getV(), 50);
		//led_string[i+1] = testVal;
		led_string[i + 1] = 50;
	}
	std:cout << "end of loop" << endl;
	serial.writeBytes(led_string, NB_LEDS + 1);
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
