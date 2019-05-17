#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxPlotter.h"
#include "ofxUVC.h"

#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#define PORT 7510
#define recipientIP "172.31.116.32"
#define localIP "127.0.0.1"
#define hostIP "127.0.0.1"

#define longBufferSize 3600
#define frameRate 15
#define derezFactor 4

#define flowQuantityTileSize 8

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofxUVC uvcControlA;
    ofxUVC uvcControlB;
    
    string cameraName = "Logitech c270";
    int camWidth = 640;
    int camHeight = 480;
    int vendorId = 0x046d;
    int productId = 0x0825;
    int interfaceNum = 0x00;
    float focus;
    
    vector<ofxUVCControl> controls;
    
    stringstream s;
    
    ofVideoGrabber cameraA;
    ofVideoGrabber cameraB;
    ofVideoPlayer video;
    ofImage tempResizeA;
    ofImage tempResizeB;
    
    ofxCv::FlowFarneback fbA;
    ofxCv::FlowFarneback fbB;
    
    ofxCv::FlowPyrLK lk;
    
    ofxCv::Flow* curFlowA;
    ofxCv::Flow* curFlowB;
    
    //vector<ofVideoDevice> devices;
    
    ofxPanel gui;
    ofParameter<float> fbPyrScale, lkQualityLevel, fbPolySigma;
    ofParameter<int> fbLevels, lkWinSize, fbIterations, fbPolyN, fbWinSize, lkMaxLevel, lkMaxFeatures, lkMinDistance;
    ofParameter<bool> fbUseGaussian, usefb;
    ofParameter<bool> resetBackground;
    ofParameter<bool> drawThreshold;
    ofParameter<bool> drawFlow;
    ofParameter<float> learningTime, thresholdValue;
    ofParameter<ofxCv::RunningBackground::DifferenceMode> differenceMode = ofxCv::RunningBackground::ABSDIFF;
    
    ofxOscSender sender;
    
    ofxOscMessage flowSec;
    ofxOscMessage flowTenSec;
    ofxOscMessage flowThirtySec;
    ofxOscMessage flowMin;
    
    ofxOscMessage movement;
    
    ofxOscMessage presenceSec;
    ofxOscMessage presenceTenSec;
    ofxOscMessage presenceThirtySec;
    ofxOscMessage presenceMin;
    ofxOscMessage presenceMinStanDev;
    ofxOscMessage presenceFiveMin;
    ofxOscMessage presenceThirtyMin;
    ofxOscMessage presenceThreeHour;

    ofxOscMessage devotionSec;

    void sendMessages();
    
    ofxCv::RunningBackground backgroundA;
    ofxCv::RunningBackground backgroundB;
    ofImage thresholdedA;
    ofImage thresholdedABuffer[frameRate];
    ofImage thresholdedB;
    ofImage thresholdedABufferB[frameRate];
    
    int secondCounter = 0;
    int bufferCounter = 0;
    bool hasBufferFilled = false;
    bool fiveSecIn = false;
    
    float runningAveragePresenceBufferA[frameRate];
    float runningAveragePresenceBufferB[frameRate];
   
    float presenceTenSeconds;
    float presenceThirtySeconds;
    float presenceMinute;
    float presenceFiveMinutes;
    float presenceThirtyMinutes;
    float presenceThreeHours;
    float presenceMinuteStanDev;
    float presenceThreeHoursStanDev;
    float presenceChange;
    
    glm::vec2 averageFlowPerSecond;
    glm::vec2 averageFlowPerTenSeconds;
    glm::vec2 averageFlowPerThirtySeconds;
    glm::vec2 averageFlowPerMinute;
    glm::vec2 averageFlowPerTenMinutes;
    
    glm::vec2 totalFlowPerSecond;
    glm::vec2 totalFlowPerTenSeconds;
    glm::vec2 totalFlowPerThirtySeconds;
    glm::vec2 totalFlowPerMinute;
    
    glm::vec2 runningTotalVectorBufferA[frameRate];
    glm::vec2 runningAverageVectorBufferA[frameRate];
    glm::vec2 runningTotalVectorBufferB[frameRate];
    glm::vec2 runningAverageVectorBufferB[frameRate];
    
    float runningTotalAmountFlowA[frameRate];
    float runningTotalAmountFlowB[frameRate];
    
    float amountFlowPerSecond;
    float presencePerSecond;
    float longAveragePresenceBuffer[longBufferSize];
    glm::vec2 perSecondVectorTotal;
    glm::vec2 longTotalFlowBuffer[longBufferSize];
    glm::vec2 longAverageFlowBuffer[longBufferSize];
    glm::vec2 sumVector;
    float sumFloat;
    glm::vec2 quantityVector;
    float flowAmount = 0;
    float presenceTotal = 0;
    
    float getPresenceStanDev(float buffer[], int seconds);
    glm::vec2 getQuantityOfFlow(ofxCv::FlowFarneback flow);
    float getQuantityOfFlow2(ofxCv::FlowFarneback flow);
    glm::vec2 getFlowPerSecond(glm::vec2 buffer[]);
    float getPresencePerSecond(float buffer[]);
    glm::vec2 getAverageOverTime(int seconds);
    float getAveragePresenceOverTime(int seconds);
    
    void keyPressed(int key);
    
};
