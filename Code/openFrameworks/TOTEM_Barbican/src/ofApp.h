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
#include "ofxOsc.h"
#include "ofxPubSubOsc.h"

#include "Parameters.h"
#include "SpikingNet.h"
#include "SpikeNetWriter.h"
#include "LedMatrix.h"

#include "Glyph.h"
#include "GlyphBlock.h"
#include "GlyphBlockFactory.h"



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
    
    ofxOscSender osc_sender_msx;
    ofxOscMessage osc_spiked_output;
    
    void displayOutputGroup(int group);
    
    Glyph addGlyph();
    void displayGlyph(const Glyph& glyph, int row ,float alpha);

private:
    
    void updateGui();
    void initSNN();
    
    int i, j, k;
    
    SpikingNet spike_net;
    SpikeNetWriter writer_weight, writer_spike;
    
    //raw snn variables
    int set_number_of_neurons = ConstParams::Number_Of_Neurons;
    int set_inhibitory_portion = ConstParams::Inhibitory_Portion;
    int set_number_of_connections = ConstParams::Number_Of_Connection;
    
    int set_network_type = ConstParams::Network_Type;
    int set_excitatory_neuron_type = ConstParams::Excitatory_Neuron_Type;
    int set_inhibitory_neuron_type = ConstParams::Inhibitory_Neuron_Type;
    
    int set_input_portion = ConstParams::Input_Portion;
    int set_input_group_size = ConstParams::Input_Group_Size;
    
    int set_output_portion = ConstParams::Output_Portion;
    int set_output_group_size = ConstParams::Output_Group_Size;
    
    bool set_stp_flag = ConstParams::Stp_Flag;
    bool set_stdp_flag = ConstParams::Stdp_Flag;
    double set_decay_rate = ConstParams::Decay_Rate;

    int stimulation_val[10]; //dimension is ConstParams::Input_Group_Size
    int neuron_getV_offset = 0;
    int whole_stimulation_val = 0;
    
    //output snn variables
    int output_time_window = 10;
    float output_group_value[10];
    float spiked_output[10];
    float spiked_scalar = 400;
    float n = ConstParams::Output_Neuron_Size/ConstParams::Output_Group_Size;
    
    //glyphs variables
    float glyph_alpha[10];
    int glyph_trig_osc[10];
    float glyph_trig_sensibility = 0.1;
    int glyph_trig_done[10];
    int row;
    Glyph glyphs[10];
    
    int topPreferredType = TYPE_O;
    int topPreferredRotation = ROTATION_0;
    int topPreferredTranslation = TRANSLATION_MIDDLE;
    
    int subPreferredType = TYPE_O;
    int subPreferredRotation = ROTATION_0;
    int subPreferredTranslation = TRANSLATION_MIDDLE;
    
    float subdivisionProbability = 0;
    
    //transition variables
    int global_value = 0;
    
    //mixing variables
    float mixing_val_A[4];
    float mixing_val_B[4];
    
    //display variables
    int display_size = 2;
    int fps = 30;
    float msSinceLastOutput_A;
    float msSinceLastOutput_B;
    
    

    
    

};
