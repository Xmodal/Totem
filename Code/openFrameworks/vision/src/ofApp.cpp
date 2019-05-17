#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    ofBackground(0);
    ofSetFrameRate(frameRate);
    
    sender.setup(hostIP, PORT);
    
    cameraA.listDevices();
    cameraB.listDevices();
    
    cameraA.setDeviceID(0);
    cameraB.setDeviceID(1);
    
    cameraA.setup(640, 480);
    
    uvcControlA.useCamera(vendorId, productId, interfaceNum);
    uvcControlA.setAutoExposure(false);
    uvcControlA.setExposure(0.9);
    uvcControlA.setAutoWhiteBalance(false);
    controls = uvcControlA.getCameraControls();
    
    cameraB.setup(640, 480);

    uvcControlB.useCamera(vendorId, productId, interfaceNum);
    uvcControlB.setAutoExposure(false);
    uvcControlB.setExposure(0.9);
    uvcControlB.setAutoWhiteBalance(false);
    controls = uvcControlB.getCameraControls();
    
    gui.setup();
    
    gui.add(resetBackground.set("Reset Background", false));
    gui.add(learningTime.set("Learning Time", (frameRate*10), 0, (frameRate*60)));
    gui.add(thresholdValue.set("Threshold Value", 25, 0, 255));
    
    gui.add(drawThreshold.set("draw threshold", false));
    gui.add(drawFlow.set("draw flow", true));
    
    gui.add(usefb.set("Use Farneback", true));
    gui.add(fbPyrScale.set("fbPyrScale", .5, 0, .99));
    gui.add(fbLevels.set("fbLevels", 4, 1, 8));
    gui.add(fbIterations.set("fbIterations", 2, 1, 8));
    gui.add(fbPolyN.set("fbPolyN", 7, 5, 10));
    gui.add(fbPolySigma.set("fbPolySigma", 1.5, 1.1, 2));
    gui.add(fbUseGaussian.set("fbUseGaussian", false));
    gui.add(fbWinSize.set("winSize", 9, 4, 64));
    
    curFlowA = &fbA;
    curFlowB = &fbB;
}

void ofApp::update(){
    
    controls = uvcControlA.getCameraControls();
    
    cameraA.update();
    cameraB.update();

    tempResizeA = cameraA.getPixels();
    tempResizeA.resize(640/derezFactor, 480/derezFactor);
    tempResizeA.rotate90(2);
    
    tempResizeB = cameraB.getPixels();
    tempResizeB.resize(640/derezFactor, 480/derezFactor);
    tempResizeB.rotate90(2);
    
    if(resetBackground) {
        backgroundA.reset();
        backgroundB.reset();
        resetBackground = false;
    }
    
    if(cameraA.isFrameNew()) {
        
        backgroundA.setLearningTime(learningTime);
        backgroundA.setThresholdValue(thresholdValue);
        
        backgroundB.setLearningTime(learningTime);
        backgroundB.setThresholdValue(thresholdValue);
        
        backgroundA.update(tempResizeA, thresholdedA);
        backgroundB.update(tempResizeB, thresholdedB);
        
        thresholdedA.update();
        thresholdedB.update();
        
            if(usefb) {
                curFlowA = &fbA;
                fbA.setPyramidScale(fbPyrScale);
                fbA.setNumLevels(fbLevels);
                fbA.setWindowSize(fbWinSize);
                fbA.setNumIterations(fbIterations);
                fbA.setPolyN(fbPolyN);
                fbA.setPolySigma(fbPolySigma);
                fbA.setUseGaussian(fbUseGaussian);
                
                curFlowB = &fbB;
                fbB.setPyramidScale(fbPyrScale);
                fbB.setNumLevels(fbLevels);
                fbB.setWindowSize(fbWinSize);
                fbB.setNumIterations(fbIterations);
                fbB.setPolyN(fbPolyN);
                fbB.setPolySigma(fbPolySigma);
                fbB.setUseGaussian(fbUseGaussian);
            }
        
        curFlowA->calcOpticalFlow(tempResizeA);
        curFlowB->calcOpticalFlow(tempResizeB);
        
        //runningTotalVectorBufferA[bufferCounter] = getQuantityOfFlow2(fbA);
        runningTotalAmountFlowA[bufferCounter] = getQuantityOfFlow2(fbA);
        runningAverageVectorBufferA[bufferCounter] = fbA.getAverageFlow();
    
        //runningTotalVectorBufferB[bufferCounter] = getQuantityOfFlow2(fbB);
        runningTotalAmountFlowB[bufferCounter] = getQuantityOfFlow2(fbB);
        runningAverageVectorBufferB[bufferCounter] = fbB.getAverageFlow();
    
        averageFlowPerSecond = (getFlowPerSecond(runningAverageVectorBufferA) - getFlowPerSecond(runningAverageVectorBufferB))/2;
        
        if(averageFlowPerSecond.y > 1.0){
            curFlowA->resetFlow();
            curFlowB->resetFlow();
        }
        
        averageFlowPerTenSeconds = getAverageOverTime(frameRate*10);
        totalFlowPerSecond = (getFlowPerSecond(runningTotalVectorBufferA) - getFlowPerSecond(runningTotalVectorBufferB))/2;
        amountFlowPerSecond = (getPresencePerSecond(runningTotalAmountFlowA) + getPresencePerSecond(runningTotalAmountFlowB))/2;
        presencePerSecond = (getPresencePerSecond(runningAveragePresenceBufferA) + getPresencePerSecond(runningAveragePresenceBufferA))/2;
    
        runningAveragePresenceBufferA[bufferCounter] = cv::mean(backgroundA.getForeground())[0] * 0.8;
        runningAveragePresenceBufferB[bufferCounter] = cv::mean(backgroundB.getForeground())[0] * 0.8;
        
        presencePerSecond = (getPresencePerSecond(runningAveragePresenceBufferA) + getPresencePerSecond(runningAveragePresenceBufferB))/2;
        
        presenceTenSeconds = getAveragePresenceOverTime(10);
        presenceThirtySeconds = getAveragePresenceOverTime(30);
        presenceMinute = getAveragePresenceOverTime(60);
        presenceFiveMinutes = getAveragePresenceOverTime(60 * 5);
        presenceThirtyMinutes = getAveragePresenceOverTime(60 * 30);
        presenceThreeHours = getAveragePresenceOverTime(60 * 180);
        presenceMinuteStanDev = getPresenceStanDev(longAveragePresenceBuffer, 60);
        //presenceThreeHoursStanDev = getPresenceStanDev(longAveragePresenceBuffer, 60);
        
        bufferCounter++;
        
        if(bufferCounter == frameRate - 1){
            bufferCounter = 0;
            longAverageFlowBuffer[secondCounter] = averageFlowPerSecond;
            //longTotalFlowBuffer[secondCounter] = totalFlowPerSecond;
            longAveragePresenceBuffer[secondCounter] = presencePerSecond;
            secondCounter++;
            sendMessages();
        }
        
        if(secondCounter >= longBufferSize - 1){
            secondCounter = 0;
            hasBufferFilled = true;
        }
        
        s << "Camera name: " << cameraName << "\nAuto-exposure: " << uvcControlA.getAutoExposure() << "\nexposure: " << uvcControlA.getExposure() << "\nAuto-focus: " << uvcControlA.getAutoFocus() <<
        "\nAbsolute focus: " << uvcControlA.getAbsoluteFocus() <<
        "\nPress 'e' to toggle auto-exposure.\nPress 'f' to toggle auto-focus.\nPress +/- to set absolute foucs.\n\nResult of GET_STATUS for each feature\non this camera:\n";
        
        for(int i = 0; i < 4; i++){
            
            s << controls.at(i).name << ": " << controls.at(i).status << "\n";
            
        }
        
        if(bufferCounter == 5 && !fiveSecIn){
            backgroundA.reset();
            backgroundB.reset();
            fiveSecIn = true;
        }
        
        sendMessages();
        
    }
    
}

void ofApp::draw(){
    
    ofPushMatrix();
    
    tempResizeA.draw(0,350,640/2,480/2);
    tempResizeB.draw(0,590,640/2,480/2);
    
    if(drawThreshold){
        if(thresholdedA.isAllocated()) {
            thresholdedA.resize(640/2, 480/2);
            thresholdedA.draw(0,350);
        }if(thresholdedB.isAllocated()) {
            thresholdedB.resize(640/2, 480/2);
            thresholdedB.draw(0,590);
        }
    }
    
    if(drawFlow){
        curFlowA->draw(0,350,640/2,480/2);
        curFlowB->draw(0,590,640/2,480/2);
    }
    
    ofDrawBitmapStringHighlight("camA", 10, 370);
    ofDrawBitmapStringHighlight("camB", 10,590);
    
    ofDrawBitmapStringHighlight(ofToString(presencePerSecond) + "% presence Second", 320, 20);
    ofDrawBitmapStringHighlight(ofToString(presenceTenSeconds) + "% presence 10 Seconds", 320, 40);
    ofDrawBitmapStringHighlight(ofToString(presenceThirtySeconds) + "% presence 30 Seconds", 320, 60);
    ofDrawBitmapStringHighlight(ofToString(presenceMinute) + "% presence 1 Minute", 320, 80);
    ofDrawBitmapStringHighlight(ofToString(presenceFiveMinutes) + "% presence 5 Minutes", 320, 100);
    ofDrawBitmapStringHighlight(ofToString(presenceThirtyMinutes) + "% presence 30 Minutes", 320, 120);
    ofDrawBitmapStringHighlight(ofToString(presenceThreeHours) + "% presence 3 hours", 320, 140);
    ofDrawBitmapStringHighlight(ofToString(presencePerSecond - presenceMinute) + "% presence change (1 minute window)", 320, 160);
    ofDrawBitmapStringHighlight(ofToString(presenceTenSeconds - presenceFiveMinutes) + "% presence change (5 minute window)", 320, 180);
    ofDrawBitmapStringHighlight(ofToString(presenceThirtyMinutes - presenceThreeHours) + "% presence change (3 hour window)", 320, 200);
    ofDrawBitmapStringHighlight(ofToString(presenceMinuteStanDev) + " stanDev (1 minute)", 320, 220);
    
    ofDrawBitmapStringHighlight(ofToString(averageFlowPerSecond.x) + " per second X", 320, 260);
    ofDrawBitmapStringHighlight(ofToString(averageFlowPerSecond.y) + " per second Y", 320, 280);
    //ofDrawBitmapStringHighlight(ofToString(totalFlowPerSecond) + " total flow per second", 320, 300);
    ofDrawBitmapStringHighlight(ofToString(amountFlowPerSecond) + " abs(total flow per second)", 320, 300);
    
    ofDrawBitmapStringHighlight(ofToString((int) ofGetFrameRate()) + " fps", 320, 400);
    ofDrawBitmapStringHighlight(ofToString(secondCounter) + " second counter", 320, 420);
    ofDrawBitmapStringHighlight(ofToString(longBufferSize - secondCounter) + " time until full buffer", 320, 440);

    //ofDrawBitmapStringHighlight(ofToString(averageFlowPerTenSeconds.y) + " per ten seconds Y", 320, 240);
    //ofDrawBitmapStringHighlight(ofToString(averageFlowPerMinute.y) + " per minute Y", 320, 260);
    //ofDrawBitmapStringHighlight(ofToString(averageFlowPerMinute.y) + " per ten minutes Y", 320, 280);
    
    ofDrawBitmapString(uvcControlA.getAutoExposure(), 320, 500);
    ofDrawBitmapString(uvcControlA.getExposure(), 320, 520);
    
    ofPopMatrix();
    gui.draw();
    
    ofSetBackgroundColor(presencePerSecond*2.55, presencePerSecond*2.55, presencePerSecond*2.55);
}

float ofApp::getPresenceStanDev(float buffer[], int seconds){
    
    int output = 0;

    if((secondCounter - seconds) < 0){
        
        for(int i = 0; i < secondCounter; i++){
            output += pow(buffer[i] - presenceMinute, 2);
        }
        
        for(int i = longBufferSize - (seconds - secondCounter); i < longBufferSize; i++){
            output += pow(buffer[i] - presenceMinute, 2);
        }
        
        sumFloat /= seconds;
        
        return sqrt(output/seconds);
        
    }else{
        
        for(int i = (secondCounter - seconds); i < secondCounter; i++){
            output += pow(buffer[i] - presenceMinute, 2);
        }
        
        return sqrt(output/seconds);
        
    }
    
}

float ofApp::getPresencePerSecond(float buffer[]){
    
    presenceTotal = 0;
    
    for(int i = 0; i < frameRate; i++){
        presenceTotal += buffer[i];
    }
   
    return presenceTotal/frameRate;
    
}

float ofApp::getAveragePresenceOverTime(int seconds){
    
    sumFloat = 0;
    
    if(seconds > longBufferSize - 1){
        return sumFloat;
    }
    
    if((secondCounter - seconds) < 0){
        
        for(int i = 0; i < secondCounter; i++){
            sumFloat += longAveragePresenceBuffer[i];
        }
        
        for(int i = longBufferSize - (seconds - secondCounter); i < longBufferSize; i++){
            sumFloat += longAveragePresenceBuffer[i];
        }
        
        sumFloat /= seconds;
        
        return sumFloat/seconds;
        
    }else{
        
        for(int i = (secondCounter - seconds); i < secondCounter; i++){
            sumFloat += longAveragePresenceBuffer[i];
        }
        
        sumVector.x /= seconds;
        sumVector.y /= seconds;
        
        return sumFloat/seconds;
        
    }
    
}

glm::vec2 ofApp::getFlowPerSecond(glm::vec2 buffer[]){
    
    perSecondVectorTotal.x = 0;
    perSecondVectorTotal.y = 0;
    //amountFlowPerSecond = 0;
    
    for(int i = 0; i < frameRate; i++){
        perSecondVectorTotal += buffer[i];
        //amountFlowPerSecond += glm::length(buffer[i]);
    }
    
    perSecondVectorTotal.x /= frameRate;
    perSecondVectorTotal.y /= frameRate;
    
    return perSecondVectorTotal;
    
}

glm::vec2 ofApp::getQuantityOfFlow(ofxCv::FlowFarneback flow){
    
    quantityVector.x = 0;
    quantityVector.y = 0;
    
    flowAmount = 0;
    
    for(int i = 0; i < (480 / derezFactor) / 8; i+=8){
        for(int j = 0; j < (640 / derezFactor) / 8; j+=8){
            quantityVector += abs(flow.getTotalFlowInRegion(ofRectangle(i, j, 8, 8)));
            if(abs(flow.getTotalFlowInRegion(ofRectangle(i, j, 8, 8))).x > 0.5){
                flowAmount++;
            }
        }
    }
    
    //cout << flowAmount << endl;
    
    return quantityVector/3000;
    
}

float ofApp::getQuantityOfFlow2(ofxCv::FlowFarneback flow){
    
    float sum = 0;
    int numberOfTiles = (flow.getWidth() * flow.getHeight()) / (flowQuantityTileSize*flowQuantityTileSize);
    
    for(int i = 0; i < flow.getWidth(); i+=flowQuantityTileSize) {
        for(int j = 0; j < flow.getHeight(); j+=flowQuantityTileSize) {
            sum += glm::length(flow.getTotalFlowInRegion(ofRectangle(i, j, flowQuantityTileSize, flowQuantityTileSize)));
        }
    }
    
    //cout << quantityVector/300 << endl;
    //cout << "test: " << flow.getTotalFlowInRegion(ofRectangle((440/derezFactor), 20, 8, 8)) << endl;
    
    return sum/numberOfTiles;
    
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

void ofApp::sendMessages(){
    
    //////////////////PRESENCE//////////////////
    
    /////////1 SECOND/////////
    presenceSec.clear();
    presenceSec.setAddress("/CV/presence/0");
    presenceSec.addFloatArg(presencePerSecond);
    sender.sendMessage(presenceSec);
    
    /////////10 SECONDS/////////
    presenceTenSec.clear();
    presenceTenSec.setAddress("/CV/presence/10");
    presenceTenSec.addFloatArg(presenceTenSeconds);
    sender.sendMessage(presenceTenSec);
    
    /////////30 SECONDS/////////
    presenceThirtySec.clear();
    presenceThirtySec.setAddress("/CV/presence/30");
    presenceThirtySec.addFloatArg(presenceThirtySeconds);
    sender.sendMessage(presenceThirtySec);
   
    /////////1 MINUTE/////////
    presenceMin.clear();
    presenceMin.setAddress("/CV/presence/60");
    presenceMin.addFloatArg(presenceMinute);
    sender.sendMessage(presenceMin);
    
    /////////1 MINUTE STANDEV/////////
    presenceMinStanDev.clear();
    presenceMinStanDev.setAddress("/CV/presenceStanDev/60");
    presenceMinStanDev.addFloatArg(presenceMinuteStanDev);
    sender.sendMessage(presenceMinStanDev);
    
    /////////5 MINUTES/////////
    presenceFiveMin.clear();
    presenceFiveMin.setAddress("/CV/presence/300");
    presenceFiveMin.addFloatArg(presenceFiveMinutes);
    sender.sendMessage(presenceFiveMin);
    
    /////////30 MINUTES/////////
    presenceThirtyMin.clear();
    presenceThirtyMin.setAddress("/CV/presence/1800");
    presenceThirtyMin.addFloatArg(presenceThirtyMinutes);
    sender.sendMessage(presenceThirtyMin);
    
    /////////3 HOURS/////////
    presenceThreeHour.clear();
    presenceThreeHour.setAddress("/CV/presence/10800");
    presenceThreeHour.addFloatArg(presenceThreeHours);
    sender.sendMessage(presenceThreeHour);
    
    
    //////////////////FLOW//////////////////
    
    /////////1 SECOND/////////
    flowSec.clear();
    flowSec.setAddress("/CV/flow/0");
    flowSec.addFloatArg(averageFlowPerSecond.y);
    sender.sendMessage(flowSec);
    
    
    /////////1 SECOND/////////
    movement.clear();
    movement.setAddress("/CV/movement/0");
    movement.addFloatArg(amountFlowPerSecond);
    sender.sendMessage(movement);
     
     /*/////////10 SECONDS/////////
     flowTenSec.clear();
     flowTenSec.setAddress("/CV/flow/10");
     flowTenSec.addFloatArg(averageFlowPerTenSeconds.x * 255);
     flowTenSec.addFloatArg(averageFlowPerTenSeconds.y * 255);
     flowTenSec.addFloatArg(amountFlowPerSecond * 255);
     sender.sendMessage(flowTenSec);
     
     /////////30 SECONDS/////////
     flowThirtySec.clear();
     flowThirtySec.setAddress("/CV/flow/30");
     flowThirtySec.addFloatArg(averageFlowPerThirtySeconds.x * 255);
     flowThirtySec.addFloatArg(averageFlowPerThirtySeconds.y * 255);
     flowThirtySec.addFloatArg(amountFlowPerSecond * 255);
     sender.sendMessage(flowThirtySec);
     
     /////////1 MINUTE/////////
     flowMin.clear();
     flowMin.setAddress("/CV/flow/60");
     flowMin.addFloatArg(averageFlowPerMinute.x * 255);
     flowMin.addFloatArg(averageFlowPerMinute.y * 255);
     flowMin.addFloatArg(amountFlowPerSecond * 255);
     sender.sendMessage(flowMin);
    
    
    //////////////////DEVOTION//////////////////
    
    /////////1 SECOND/////////
    devotionSec.clear();
    devotionSec.setAddress("/CV/devotion/0");
    devotionSec.addFloatArg(presencePerSecond / (amountFlowPerSecond * 255));
    sender.sendMessage(devotionSec);*/
    
}

void ofApp::keyPressed(int key){
    if(key == 'e'){
        uvcControlA.setAutoExposure(!uvcControlA.getAutoExposure());
    }
    
    if(key == 'f'){
        uvcControlA.setAutoFocus(!uvcControlA.getAutoFocus());
    }
    
    if(key == '='){
        focus += 0.1;
        uvcControlA.setAbsoluteFocus(focus);
    }
    
    if(key == '-'){
        focus -= 0.1;
        uvcControlA.setAbsoluteFocus(focus);
        
    }
}
