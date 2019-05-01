#include "ofApp.h"

//Serial communication speed
int baud = 2500000;
//const std::string& input = "com3";

LedMatrix led(baud, "COM4", true);
unsigned char x = 0;

int topPreferredType = TYPE_O;
int topPreferredRotation = ROTATION_0;
int topPreferredTranslation = TRANSLATION_MIDDLE;

int subPreferredType = TYPE_O;
int subPreferredRotation = ROTATION_0;
int subPreferredTranslation = TRANSLATION_MIDDLE;

float subdivisionProbability = 0;

void ofApp::setup() 
{
	ofSetFrameRate(10);
	//Serial
	led.setup();
	//led.clear();
	//led.flush();
	row = 0;

	currentGlyph = addGlyph();
}

void ofApp::update() 
{
	// Reset background.
	led.clear();
	led.flush();

/*	GlyphBlock test(TYPE_L, ROTATION_0, TRANSLATION_MIDDLE);

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			bool isOn = test.get(x, y);
			led.set(x, y, isOn ? 254 : 0);
		}
	}*/

	displayGlyph(currentGlyph, 0);

	led.flush();
}

//--------------------------------------------------------------
void ofApp::draw() 
{
	if(led.display)
		led.drawOnDisplay();
}


Glyph ofApp::addGlyph()
{
	float topTypeWeights[N_TYPES];
	float topRotationWeights[N_ROTATIONS];
	float topTranslationWeights[N_TRANSLATIONS];
	GlyphBlockFactory::generateSmoothWeights(topTypeWeights, ofMap(topPreferredType, 0, MAX_TYPE, 0, 1), N_TYPES, false);
	GlyphBlockFactory::generateSmoothWeights(topRotationWeights, ofMap(topPreferredRotation, 0, MAX_ROTATION, 0, 1), N_ROTATIONS, true);
	GlyphBlockFactory::generateSmoothWeights(topTranslationWeights, ofMap(topPreferredTranslation, 0, MAX_TRANSLATION, 0, 1), N_TRANSLATIONS, false);

	float subTypeWeights[N_TYPES];
	float subRotationWeights[N_ROTATIONS];
	float subTranslationWeights[N_TRANSLATIONS];
	GlyphBlockFactory::generateSmoothWeights(subTypeWeights, ofMap(subPreferredType, 0, MAX_TYPE, 0, 1), N_TYPES, false);
	GlyphBlockFactory::generateSmoothWeights(subRotationWeights, ofMap(subPreferredRotation, 0, MAX_ROTATION, 0, 1), N_ROTATIONS, true);
	GlyphBlockFactory::generateSmoothWeights(subTranslationWeights, ofMap(subPreferredTranslation, 0, MAX_TRANSLATION, 0, 1), N_TRANSLATIONS, false);

	GlyphBlockFactory topFactory(topTypeWeights, topRotationWeights, topTranslationWeights);
	GlyphBlockFactory subFactory(subTypeWeights, subRotationWeights, subTranslationWeights);

	// Create glyph.
	return Glyph(topFactory, subFactory, subdivisionProbability);
}

void ofApp::displayGlyph(const Glyph& glyph, int box)
{
	int row = box * LED_MATRIX_HEIGHT_PER_BOX;
	for (int x = 0; x < GLYPH_WIDTH; x++)
	{
		for (int y = 0; y < GLYPH_HEIGHT; y++)
		{
			bool isOn = glyph.get(x, y);
			led.set(x, row + y, isOn ? 254 : 0);
		}
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	std::cout << (char)key << std::endl;
	switch (key) {

	case 'I': topPreferredType = TYPE_I; break;
	case 'L': topPreferredType = TYPE_L; break;
	case 'T': topPreferredType = TYPE_T; break;
	case 'U': topPreferredType = TYPE_U; break;
	case 'O': topPreferredType = TYPE_O; break;

	case 'i': subPreferredType = TYPE_I; break;
	case 'l': subPreferredType = TYPE_L; break;
	case 't': subPreferredType = TYPE_T; break;
	case 'u': subPreferredType = TYPE_U; break;
	case 'o': subPreferredType = TYPE_O; break;

	case 'S': topPreferredRotation = ROTATION_0; break;
	case 'D': topPreferredRotation = ROTATION_90; break;
	case 'F': topPreferredRotation = ROTATION_180; break;
	case 'G': topPreferredRotation = ROTATION_270; break;

	case 's': subPreferredRotation = ROTATION_0; break;
	case 'd': subPreferredRotation = ROTATION_90; break;
	case 'f': subPreferredRotation = ROTATION_180; break;
	case 'g': subPreferredRotation = ROTATION_270; break;

	case 'Q': topPreferredTranslation = TRANSLATION_TOP; break;
	case 'A': topPreferredTranslation = TRANSLATION_MIDDLE; break;
	case 'Z': topPreferredTranslation = TRANSLATION_BOTTOM; break;

	case 'q': subPreferredTranslation = TRANSLATION_TOP; break;
	case 'a': subPreferredTranslation = TRANSLATION_MIDDLE; break;
	case 'z': subPreferredTranslation = TRANSLATION_BOTTOM; break;

	case '+': subdivisionProbability = ofClamp(subdivisionProbability + 0.05, 0, 1); break;
	case '-': subdivisionProbability = ofClamp(subdivisionProbability - 0.05, 0, 1); break;
	}

	// Add glyph after any keypress.
	currentGlyph = addGlyph();
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

