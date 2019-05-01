#pragma once

#include <iomanip>
#include <fstream>
#include <time.h>
#include <sys/stat.h>
#include <math.h>
#include <string>
#include <cmath>

#include "ofMain.h"
#include "ofMath.h"

#include "ofxGui.h"
#include "ofxPubSubOsc.h"

#include "Parameters.h"
#include "SpikingNet.h"
#include "SpikeNetWriter.h"
#include "LedMatrix.h"



class ofApp : public ofBaseApp{
    
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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void setFrameRate(int & fps_);
        
    ofSerial serial;

private:
    
    void setupGui();
    void updateGui();
    void initParams();
    
    int i, j, k;
    
    SpikingNet spike_net;
    SpikeNetWriter writer_weight, writer_spike;
    
    //raw snn variables
    int stimulation_val[10]; //dimension is ConstParams::Input_Group_Size
    int neuron_getV_offset = 0;
    
    //output snn variables
    
    //glyphs variables
    
    //transition variables
    int global_value = 0;
    
    //mixing variables
    float mixing_val_A[4];
    float mixing_val_B[4];
    
    
    ofxLabel start_message;
    ofxPanel gui;
    ofxIntSlider fps;
    ofxIntSlider size_display;
    ofxToggle set_stp_flag;
    ofxToggle set_stdp_flag;
    ofxFloatSlider set_decay_rate; //it should be a double...
    ofxIntSlider set_number_of_neurons;
    ofxLabel network_types;
    ofxIntSlider set_network_type;
    ofxLabel neuron_type;
    ofxIntSlider set_inhibitory_neuron_type;
    ofxLabel excitatory_neuron_type;
    ofxIntSlider set_excitatory_neuron_type;
    ofxIntSlider set_inhibitory_number;
    ofxIntSlider set_input_number;
    ofxIntSlider set_number_of_connection;

};
