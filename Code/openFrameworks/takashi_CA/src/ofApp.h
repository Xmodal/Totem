#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxSyphon.h"
//  #include "ofxPubSubOsc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




class ofApp : public ofBaseApp{
    
    ofxOscSender sender;
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int rulecntl = 30;
    int framerate = 60;
    int i,j,k;
    long int iseed;    /* random seed */
    int iflag;    /* initial state type */
    
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonClient mClient;
    
    
    
};

