#pragma once

#define USE_OSC

#define TOTEM_SIDE_A 0
#define TOTEM_SIDE_B 1

/////////
//CHOOSE SERIAL PORT TO USE HERE
/////////
//#define TOTEM_SIDE TOTEM_SIDE_A
#define TOTEM_SIDE TOTEM_SIDE_B

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
#ifdef USE_OSC
#include "ofxPubSubOsc.h"
#endif

#include "Parameters.h"
#include "SpikingNet.h"
#include "SpikeNetWriter.h"
#include "LedMatrix.h"

#include "Glyph.h"
#include "GlyphBlock.h"
#include "GlyphBlockFactory.h"

#include "easing.h"

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

    GlyphBlockFactory createTopFactory();
    GlyphBlockFactory createSubFactory();
    Glyph addGlyph();

    void evolveGlyphs(float topMutationRate, float subMutationRate);

    void displayGlyph(const Glyph& glyph, int row ,float alpha);

    // Return neuron in position (x, y) on the display.
    Izhikevich& getNeuron(int x, int y);
    double getNeuronV(int x, int y);
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

    int stimulation_val[LED_MATRIX_BOXES]; //dimension is ConstParams::Input_Group_Size
    int neuron_getV_offset = 0;
    int whole_stimulation_val = 0;

    //output snn variables
    int output_time_window = 10;
    float output_group_value[LED_MATRIX_BOXES];
    float spiked_output[LED_MATRIX_BOXES];
    float spiked_scalar = 400;
    float smoothed_spiked_output[LED_MATRIX_HEIGHT];
    float n = ConstParams::Output_Neuron_Size/ConstParams::Output_Group_Size;
    float post_smoothing_curve = 1;

    //glyphs variables
    float glyph_alpha[LED_MATRIX_BOXES];
    int glyph_trig_osc[LED_MATRIX_BOXES];
    float glyph_trig_sensibility = 0.1;
    int glyph_trig_done[LED_MATRIX_BOXES];
    int row;
    Glyph glyphs[LED_MATRIX_BOXES];

    // Parameters in [0, 1] controlling the glyphs.
    float glyph_sub_activation_threshold = 0.8;
    float glyph_top_type = 0.5;
    float glyph_sub_type = 0.5;
    float glyph_top_mutation_rate = 0.01;
    float glyph_sub_mutation_rate = 0.01;
    float glyph_top_rotation = 0.5;
    float glyph_sub_rotation = 0.5;

//    int topPreferredType = TYPE_O;
    int topPreferredRotation = ROTATION_0;
    int topPreferredTranslation = TRANSLATION_MIDDLE;

//    int subPreferredType = TYPE_O;
    int subPreferredRotation = ROTATION_0;
    int subPreferredTranslation = TRANSLATION_MIDDLE;

    // index of current smoothing function
    int current_spiked_output_smoothing = 0;

    float subdivisionProbability = 0;

    //transition variables
    int global_value = 0;

    //mixing variables
    float mixing_val_A[4];
    float mixing_val_B[4];

    //display variables
    int display_size = 3;
    int fps = 30;
    float msSinceLastOutput_A;
    float msSinceLastOutput_B;

    typedef AHFloat (*easing_function)(AHFloat);
    const easing_function SMOOTHINGS[N_SMOOTHINGS] = {
      LinearInterpolation,
      QuadraticEaseInOut,
      CubicEaseInOut,
      QuarticEaseInOut,
      QuinticEaseInOut,
      SineEaseInOut,
      CircularEaseInOut,
      ExponentialEaseInOut,
      ElasticEaseInOut,
      BackEaseInOut,
      BounceEaseInOut };
};
