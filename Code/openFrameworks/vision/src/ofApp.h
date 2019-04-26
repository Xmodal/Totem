#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxPlotter.h"

#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#define PORT 7500
#define recipientIP "172.31.116.32"
#define localIP "127.0.0.1"
#define hostIP "127.0.0.1"

#define longBufferSize 2000
#define frameRate 15
#define derezFactor 4

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber camera;
    ofVideoPlayer video;
    ofImage tempResize;
    
    ofxCv::FlowFarneback fb;
    ofxCv::FlowPyrLK lk;
    
    ofxCv::Flow* curFlow;
    
    ofxPanel gui;
    ofParameter<float> fbPyrScale, lkQualityLevel, fbPolySigma;
    ofParameter<int> fbLevels, lkWinSize, fbIterations, fbPolyN, fbWinSize, lkMaxLevel, lkMaxFeatures, lkMinDistance;
    ofParameter<bool> fbUseGaussian, usefb;
    ofParameter<bool> resetBackground;
    ofParameter<float> learningTime, thresholdValue;
    ofParameter<ofxCv::RunningBackground::DifferenceMode> differenceMode = ofxCv::RunningBackground::ABSDIFF;
    
    ofxPlotter plotter;
    
    ofxOscSender sender;
    
    ofxOscMessage flowSecA;
    ofxOscMessage flowSecB;
    ofxOscMessage flowTenSecA;
    ofxOscMessage flowTenSecB;
    ofxOscMessage flowMinA;
    ofxOscMessage flowMinB;

    ofxOscMessage presenceA;
    ofxOscMessage presenceB;
    
    ofxCv::RunningBackground background;
    ofImage thresholded;
    
    int secondCounter = 0;
    int bufferCounter = 0;
    
    glm::vec2 runningTotalVectorBuffer[frameRate];
    glm::vec2 runningAverageVectorBuffer[frameRate];
    glm::vec2 averageFlowPerSecond;
    glm::vec2 totalFlowPerSecond;
    float amountFlowPerSecond;
    float presence;
    glm::vec2 perSecondVectorTotal;
    glm::vec2 longTotalFlowBuffer[longBufferSize];
    glm::vec2 longAverageFlowBuffer[longBufferSize];
    glm::vec2 sumVector;
    glm::vec2 quantityVector;
    
    glm::vec2 getQuantityOfFlow(ofxCv::FlowFarneback flow);
    glm::vec2 getFlowPerSecond(glm::vec2 buffer[]);
    glm::vec2 getAverageOverTime(int seconds);
    
};
