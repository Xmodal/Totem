#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    ofBackground(0);
    ofSetFrameRate(frameRate);
    
    sender.setup(hostIP, PORT);
    
    //camera.setup(640, 480);
    
    video.load("movies/jackson_hole_30.mp4");
    video.play();
    
    gui.setup();
    
    /*gui.add(lkMaxLevel.set("lkMaxLevel", 3, 0, 8));
    gui.add(lkMaxFeatures.set("lkMaxFeatures", 200, 1, 1000));
    gui.add(lkQualityLevel.set("lkQualityLevel", 0.01, 0.001, .02));
    gui.add(lkMinDistance.set("lkMinDistance", 4, 1, 16));
    gui.add(lkWinSize.set("lkWinSize", 8, 4, 64));*/
    
    gui.add(usefb.set("Use Farneback", true));
    gui.add(fbPyrScale.set("fbPyrScale", .5, 0, .99));
    gui.add(fbLevels.set("fbLevels", 4, 1, 8));
    gui.add(fbIterations.set("fbIterations", 2, 1, 8));
    gui.add(fbPolyN.set("fbPolyN", 7, 5, 10));
    gui.add(fbPolySigma.set("fbPolySigma", 1.5, 1.1, 2));
    gui.add(fbUseGaussian.set("fbUseGaussian", false));
    gui.add(fbWinSize.set("winSize", 9, 4, 64));
    
    gui.add(resetBackground.set("Reset Background", false));
    gui.add(learningTime.set("Learning Time", (frameRate*30), 0, (frameRate*60)));
    gui.add(thresholdValue.set("Threshold Value", 25, 0, 255));
    curFlow = &fb;
    
}

void ofApp::update(){
    
    //camera.update();
    video.update();
    tempResize = video.getPixels();
    //tempResize = camera.getPixels();
    tempResize.resize(640/derezFactor, 480/derezFactor);
    
    if(resetBackground) {
        background.reset();
        resetBackground = false;
    }
    
    //if(camera.isFrameNew()) {
    if(video.isFrameNew()) {
        
        background.setLearningTime(learningTime);
        background.setThresholdValue(thresholdValue);
        //background.setIgnoreForeground(false); //setIgnoreForeground(bool ignoreForeground)
        
        //background.update(camera, thresholded);
        //background.update(video, thresholded);
        
        background.update(tempResize, thresholded);
        thresholded.update();
        
        if(usefb) {
            curFlow = &fb;
            fb.setPyramidScale(fbPyrScale);
            fb.setNumLevels(fbLevels);
            fb.setWindowSize(fbWinSize);
            fb.setNumIterations(fbIterations);
            fb.setPolyN(fbPolyN);
            fb.setPolySigma(fbPolySigma);
            fb.setUseGaussian(fbUseGaussian);
        } else {
            curFlow = &lk;
            lk.setMaxFeatures(lkMaxFeatures);
            lk.setQualityLevel(lkQualityLevel);
            lk.setMinDistance(lkMinDistance);
            lk.setWindowSize(lkWinSize);
            lk.setMaxLevel(lkMaxLevel);
        }
        
        //curFlow->calcOpticalFlow(camera);
        //curFlow->calcOpticalFlow(video);
        curFlow->calcOpticalFlow(tempResize);
        
        fb.getTotalFlow();
        
        runningTotalVectorBuffer[bufferCounter] = getQuantityOfFlow(fb);
        runningAverageVectorBuffer[bufferCounter] = fb.getAverageFlow();
        
        averageFlowPerSecond = getFlowPerSecond(runningAverageVectorBuffer);
        totalFlowPerSecond = getFlowPerSecond(runningTotalVectorBuffer);
        amountFlowPerSecond = glm::length(totalFlowPerSecond);
        
        presence = cv::mean(background.getForeground())[0]/100;
        
        bufferCounter++;
        
        if(bufferCounter == frameRate - 1){
            
            bufferCounter = 0;
            longAverageFlowBuffer[secondCounter] = averageFlowPerSecond;
            longTotalFlowBuffer[secondCounter] = totalFlowPerSecond;
            secondCounter++;
            
        }
        
        if(secondCounter >= 2000 - 1){
            secondCounter = 0;
        }
        
        flowSecA.clear();
        flowSecA.setAddress("/A/CV/flow/0");
        flowSecA.addFloatArg(averageFlowPerSecond.x);
        flowSecA.addFloatArg(averageFlowPerSecond.y);
        flowSecA.addFloatArg(amountFlowPerSecond);
        sender.sendMessage(flowSecA);
        
        presenceA.clear();
        presenceA.setAddress("/A/CV/flow/0");
        presenceA.addFloatArg(averageFlowPerSecond.x);
        presenceA.addFloatArg(averageFlowPerSecond.y);
        presenceA.addFloatArg(amountFlowPerSecond);
        sender.sendMessage(presenceA);
        
    }
    
}

void ofApp::draw(){
    
    if(thresholded.isAllocated()) {
        thresholded.draw(640, 480);
    }
    
    ofPushMatrix();
    
    ofTranslate(640, 0);
    //camera.draw(0,0,640,480);
    //video.draw(0,0,640,480);
    
    tempResize.draw(0,0,640,480);
    curFlow->draw(0,0,640,480);
    
    ofDrawBitmapStringHighlight(ofToString((int) ofGetFrameRate()) + " fps", -300, 20);
    
    ofDrawBitmapStringHighlight(ofToString(secondCounter) + " second counter", -300, 40);
    
    ofDrawBitmapStringHighlight(ofToString(averageFlowPerSecond.x) + " per second X", -300, 60);
    ofDrawBitmapStringHighlight(ofToString(averageFlowPerSecond.y) + " per second Y", -300, 80);
    ofDrawBitmapStringHighlight(ofToString(getAverageOverTime(10).y) + " per ten seconds Y", -300, 100);
    ofDrawBitmapStringHighlight(ofToString(getAverageOverTime(60).y) + " per minute Y", -300, 120);
    ofDrawBitmapStringHighlight(ofToString(getAverageOverTime(60*10).y) + " per ten minutes Y", -300, 140);
    
    ofDrawBitmapStringHighlight(ofToString(amountFlowPerSecond) + " per second flow total", -300, 180);
    ofDrawBitmapStringHighlight(ofToString(averageFlowPerSecond) + " per second flow average", -300, 200);
    ofDrawBitmapStringHighlight(ofToString(presence) + " presence", -300, 220);
    ofDrawBitmapStringHighlight(ofToString(presence / amountFlowPerSecond) + " devotion (presence / perSecondSpeed)", -300, 240);
    
    ofPopMatrix();
    gui.draw();
    
}

glm::vec2 ofApp::getFlowPerSecond(glm::vec2 buffer[]){
    
    perSecondVectorTotal.x = 0;
    perSecondVectorTotal.y = 0;
    amountFlowPerSecond = 0;
    
    for(int i = 0; i < frameRate; i++){
        perSecondVectorTotal += buffer[i];
        amountFlowPerSecond += glm::length(buffer[i]);
    }
    
    perSecondVectorTotal.x /= frameRate;
    perSecondVectorTotal.y /= frameRate;
    
    return perSecondVectorTotal;
    
}

glm::vec2 ofApp::getQuantityOfFlow(ofxCv::FlowFarneback flow){
    
    quantityVector.x = 0;
    quantityVector.y = 0;
    
    for(int i = 0; i < (480 / derezFactor) / 8; i++){
        for(int j = 0; j < (640 / derezFactor) / 8; j++){
            quantityVector = abs(flow.getTotalFlowInRegion(ofRectangle(i, j, 8, 8)));
        }
    }
    
    return quantityVector/4;
    
}

glm::vec2 ofApp::getAverageOverTime(int seconds){
    
    sumVector.x = 0;
    sumVector.y = 0;
    
    if(seconds > 1999){
        return sumVector;
    }
    
    if((secondCounter - seconds) < 0){
        
        for(int i = 0; i < secondCounter; i++){
            sumVector += longAverageFlowBuffer[i];
        }
        
        for(int i = longBufferSize - (seconds - secondCounter); i < longBufferSize; i++){
            sumVector += longAverageFlowBuffer[i];
        }
        
        sumVector.x /= seconds;
        sumVector.y /= seconds;
        
        return sumVector;
        
    }else{
        
        for(int i = (secondCounter - seconds); i < secondCounter; i++){
            sumVector += longAverageFlowBuffer[i];
        }
        
        sumVector.x /= seconds;
        sumVector.y /= seconds;
        
        return sumVector;
        
    }
    
}
