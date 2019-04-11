#include "ofApp.h"

//Serial communication speed
int baud = 2500000;
//const std::string& input = "com3";

LedMatrix led(baud, "COM4");
unsigned char x = 0;

void ofApp::setup() 
{
	ofSetFrameRate(20);
	//Serial
	led.setup();
	led.clear();
	led.flush();
	row = 0;

	currentGlyph = addGlyph();
}

void ofApp::update() 
{
	
	// Reset background.
	led.clear();
	led.flush();

	displayGlyph(currentGlyph, row);
	
	// Add glyph when ready.
	if (row == currentGlyph.nRows() + 1)
	{
		currentGlyph = addGlyph();
		row = 0;
	}

	// Draw glyphs.
	int y = -(currentGlyph.nRows() - row);
	for (int i = text.size() - 1; i >= 0; i--)
	{
		Glyph& g = text[i];
		displayGlyph(g, y);
		y += (g.nRows() + 1);
	}

	row++;

	led.flush();
}

//--------------------------------------------------------------
void ofApp::draw() 
{

}


Glyph ofApp::addGlyph()
{
	
	// Build random weights.
	float typeWeights[N_TYPES];
	Glyph::generateSmoothWeights(typeWeights, float(mouseX) / ofGetWindowWidth(), N_TYPES-1, false);

	float rotationWeights[N_ROTATIONS] = { 1, 0.5, 1, 0.5 };
	float translationWeights[N_TRANSLATIONS];
	Glyph::generateSmoothWeights(translationWeights, float(mouseY) / ofGetWindowHeight(), N_TRANSLATIONS - 1, false);

	// Create glyph.
	Glyph nextGlyph(typeWeights, rotationWeights, translationWeights);
	text.push_back(nextGlyph);
	return nextGlyph;
}

void ofApp::displayGlyph(const Glyph& glyph, int row)
{
	for (int i = 0; i < glyph.nRows(); i++)
	{
		for (int j = 0; j < LED_MATRIX_WIDTH; j++)
		{
			bool isOn = glyph.get(i, j);
			led.set(j, row + i, isOn ? 254 : 0);
		}
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

