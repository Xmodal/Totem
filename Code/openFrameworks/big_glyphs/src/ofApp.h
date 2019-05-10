#pragma once

#include "ofMain.h"
#include "../Glyph.h"
#include "../LedMatrix.h"
#include "../GlyphBlock.h"
#include <vector>

class ofApp : public ofBaseApp {

public:
	ofApp() {}

	void setup();
	void update();
	void draw();

	Glyph addGlyph();
	void displayGlyph(const Glyph& glyph, int row, int baseRow);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	std::vector<Glyph> text;
	int row;
	int shiftCount = 0;
	int glyphCount;
	Glyph onTotem[10];
	Glyph currentGlyph; 
};
