#include "ofApp.h"

LedMatrix display_snn_raw(0, "", false);
LedMatrix display_snn_output(0, "", false);
LedMatrix display_glyph(0, "", false);
LedMatrix display_transition(0, "", false);

// Totem side A
#if (TOTEM_SIDE == TOTEM_SIDE_A)
#define SERIAL_PORT_INDEX 0
#define PORT 7511
#define WINDOW_TITLE "TOTEM - side A - port 7511"

// Totem side B
#else
#define SERIAL_PORT_INDEX 1
#define WINDOW_TITLE "TOTEM - side B - port 7512"
#define PORT 7512
#endif

LedMatrix totem_side_A(2500000, "/dev/tty.usbmodem", SERIAL_PORT_INDEX, true);

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle(WINDOW_TITLE);
    ofSetBackgroundAuto(true);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    ofBackground(100);

    std::cout.precision(11);

    // Init random seed so that all random numbers will be the same
    // in each oF instance.
    srand(0);

    //Re-initialisation of spike net in the keyPress function
    spike_net.init(); //just to make sure there is no issue

    //------
    //DISPLAY
    //------
    display_snn_raw.setup();
    display_snn_output.setup();
    display_glyph.setup();
    totem_side_A.setup();
    //totem_side_B.setup();

    //------
    //OSC
    //------

#ifdef USE_OSC
    osc_sender_msx.setup("localhost", 7510);

    //SUSCRIBE
    ofxSubscribeOsc(PORT, "/SNN/stimulation", stimulation_val);
    ofxSubscribeOsc(PORT, "/SNN/whole_stimulation", whole_stimulation_val);

    ofxSubscribeOsc(PORT, "/SNN/neuron_getV_offset", neuron_getV_offset);
    ofxSubscribeOsc(PORT, "/SNN/number_of_neurons", set_number_of_neurons);
    ofxSubscribeOsc(PORT, "/SNN/set_network_type", set_network_type);
    ofxSubscribeOsc(PORT, "/SNN/set_inhibitory_neuron_type", set_inhibitory_neuron_type);
    ofxSubscribeOsc(PORT, "/SNN/set_excitatory_neuron_type", set_excitatory_neuron_type);
    ofxSubscribeOsc(PORT, "/SNN/set_inhibitory_portion", set_inhibitory_portion);
    ofxSubscribeOsc(PORT, "/SNN/set_input_portion", set_input_portion);
    ofxSubscribeOsc(PORT, "/SNN/set_input_group_size", set_input_group_size);
    ofxSubscribeOsc(PORT, "/SNN/set_output_portion", set_output_portion);
    ofxSubscribeOsc(PORT, "/SNN/set_output_group_size", set_output_group_size);
    ofxSubscribeOsc(PORT, "/SNN/set_number_of_connections", set_number_of_connections);
    ofxSubscribeOsc(PORT, "/SNN/set_stp_flag", set_stp_flag);
    ofxSubscribeOsc(PORT, "/SNN/set_stdp_flag", set_stdp_flag);
    ofxSubscribeOsc(PORT, "/SNN/set_decay_rate", set_decay_rate);
    ofxSubscribeOsc(PORT, "/SNN/init", [this](){
        initSNN();
    });

    ofxSubscribeOsc(PORT, "/glyph/glyph_alpha", glyph_alpha);
    ofxSubscribeOsc(PORT, "/glyph/glyph_trig_sensibility", glyph_trig_sensibility);
    ofxSubscribeOsc(PORT, "/glyph/glyph_trig", glyph_trig_osc, [this](){
        for(int i = 0; i < 10; i++){
            if(glyph_trig_osc[i]){ glyphs[i] = addGlyph();}
        }

    });

    ofxSubscribeOsc(PORT, "/glyph/glyph_sub_activation_threshold", glyph_sub_activation_threshold);
    ofxSubscribeOsc(PORT, "/glyph/glyph_top_mutation_rate", glyph_top_mutation_rate);
    ofxSubscribeOsc(PORT, "/glyph/glyph_sub_mutation_rate", glyph_top_mutation_rate);
    ofxSubscribeOsc(PORT, "/glyph/glyph_top_type", glyph_top_type);
    ofxSubscribeOsc(PORT, "/glyph/glyph_sub_type", glyph_sub_type);
    ofxSubscribeOsc(PORT, "/glyph/glyph_top_rotation", glyph_top_rotation);
    ofxSubscribeOsc(PORT, "/glyph/glyph_sub_rotation", glyph_sub_rotation);

    ofxSubscribeOsc(PORT, "/SNN_output/current_spiked_output_smoothing", current_spiked_output_smoothing);
    ofxSubscribeOsc(PORT, "/SNN_output/post_smoothing_curve", post_smoothing_curve);

    ofxSubscribeOsc(PORT, "/SNN_output/output_time_window", output_time_window);
    ofxSubscribeOsc(PORT, "/SNN_output/spiked_scalar", spiked_scalar);

    ofxSubscribeOsc(PORT, "/transition/global_value", global_value);

    ofxSubscribeOsc(PORT, "/mixer/A/faders", mixing_val_A);
    ofxSubscribeOsc(PORT, "/mixer/B/faders", mixing_val_B);

    ofxSubscribeOsc(PORT, "/display/fps", fps);
    ofxSubscribeOsc(PORT, "/display/display_size", display_size);

    //PUBLISH
    //ofxPublishOsc("localhost", 7510, "/display/A/ms_since_last_output", &msSinceLastOutput_A, false);
    //ofxPublishOsc("localhost", 7510, "/display/B/ms_since_last_output", &msSinceLastOutput_B, false);
//    ofxPublishOsc("localhost", 7510, "/SNN_output/spiked_output", &spiked_output[], false); // not working with osfPublishAsArray
#endif // USE_OSC

    ofSleepMillis(5000);

    //------
    //GLYPHS
    //------
    row = 0;
    for(int i = 0; i < LED_MATRIX_BOXES; i++){
        glyphs[i] = addGlyph();
    }

}
//--------------------------------------------------------------
void ofApp::update(){
    ofSetFrameRate(fps);

    //----------
    //update parameters
    //----------
    for(i=0; i < ConstParams::Input_Group_Size; i++){
        spike_net.stimulation(i, stimulation_val[i]); // (input group id, stimlation strength)
    }
    if(whole_stimulation_val != 0){
        spike_net.wholeNetworkStimulation(whole_stimulation_val);
    }
    //----------
    //update processes
    //----------

    //UPDATE SNN
    spike_net.update();

    //UPDATE SNN OUTPUT

    //get firing rates
    for(i=0;i<ConstParams::Output_Group_Size;i++){
        spiked_output[i]= spike_net.getSpikedOutput(i)/(n*output_time_window);
        output_group_value[i] = ofClamp(spiked_output[i]*spiked_scalar, 0, 254);
    }
    if(ofGetFrameNum()%output_time_window == 0){
        spike_net.clearSpikedNeuronId();
    }

    // compute eased/smoothed spiking outputs for each row
    current_spiked_output_smoothing = (int) ofClamp(current_spiked_output_smoothing, 0, MAX_SMOOTHING);
    easing_function smoothingFunction = SMOOTHINGS[current_spiked_output_smoothing];
    float prevOutput = spiked_output[ConstParams::Output_Group_Size-1];
    int row = LED_MATRIX_HEIGHT - (LED_MATRIX_HEIGHT_PER_BOX/2);
    for(i=0; i<ConstParams::Output_Group_Size; i++){
      float nextOutput = spiked_output[i];

      // Fill the rows between two center points of each box.
      for (j=0; j<LED_MATRIX_HEIGHT_PER_BOX; j++, row++) {
        float alpha = smoothingFunction( float(j) / LED_MATRIX_HEIGHT_PER_BOX );
        float value = alpha * nextOutput + (1-alpha) * prevOutput;
        smoothed_spiked_output[ row % LED_MATRIX_HEIGHT ] = value;
      }

      prevOutput = nextOutput;
    }

    osc_spiked_output.clear();
    osc_spiked_output.setAddress("/SNN_output/spiked_output");
    for(i=0;i<ConstParams::Output_Group_Size;i++){
        osc_spiked_output.addFloatArg(spiked_output[i]);
    }
    osc_sender_msx.sendMessage(osc_spiked_output);

    // Update factories.
    GlyphBlockFactory topFactory = createTopFactory();
    GlyphBlockFactory subFactory = createSubFactory();

    //UPDATE GLYPHS
    for(int i = 0; i < ConstParams::Output_Group_Size; i++){
        glyph_alpha[i] = 1;//ofClamp(spiked_output[i]*spiked_scalar, 0, 254);

        // Evolve blocks according to activations.
        for (int top = 0; top < N_TOP_BLOCKS; top++) {
          // Top blocks are mutated according to spiked output of corresponding glyph.
          glyphs[i].evolveTopBlock(topFactory, top, spiked_output[i] * glyph_top_mutation_rate);

          // Sub blocks are mutated according to activation of the region they cover.
          for (int xSub=0; xSub<BLOCK_SIDE; xSub++)
            for (int ySub=0; ySub<BLOCK_SIDE; ySub++) {

              // Sum up activations within block.
              double sumOutput = 0;
              int xOffset = xSub * BLOCK_SIDE;
              int yOffset = (i * LED_MATRIX_HEIGHT_PER_BOX + top * BLOCK_SIDE*BLOCK_SIDE + ySub * BLOCK_SIDE);
              for (int x=0; x<BLOCK_SIDE; x++)
                for (int y=0; y<BLOCK_SIDE; y++)
                  sumOutput += getNeuronV(xOffset+x, yOffset+y) / 255;
              glyphs[i].evolveSubBlock(topFactory, top, xSub, ySub, sumOutput * glyph_sub_mutation_rate);
            }
        }

        glyphs[i].update(glyph_sub_activation_threshold);

        // if(spiked_output[i] <= glyph_trig_sensibility) {
        //   glyph_trig_done[i] = 0;
        // }
        // else if(spiked_output[i] > glyph_trig_sensibility && glyph_trig_done[i] == 0) {
        //     glyphs[i] = addGlyph(); // removed for now
        //     glyph_trig_done[i] = 1;
        // }
        //
        // glyphs[i].update(glyph_sub_activation_threshold);
    }


    //----------
    //update displays
    //----------
    display_snn_raw.clear();
    display_snn_output.clear();
    display_glyph.clear();
    display_transition.clear();
    totem_side_A.clear();
    //totem_side_B.clear();

    //populate raw SNN matrix
    for (int x=0; x<LED_MATRIX_WIDTH; x++)
        for (int y=0; y<LED_MATRIX_HEIGHT; y++)
            display_snn_raw.set(x, y, ofClamp(getNeuronV(x, y), 0, 254));

    //populate SNN output matrix
    for (int x=0; x<LED_MATRIX_WIDTH; x++)
        for (int y=0; y<LED_MATRIX_HEIGHT; y++)
        {
          // Note: outputs are inverted (vertically) wrt spiked outputs.
          display_snn_output.set(x, LED_MATRIX_HEIGHT-1 - y, ofClamp(powf(smoothed_spiked_output[y], post_smoothing_curve)*spiked_scalar, 0, 254));
        }

    //populate glyph matrix

    for(int i = 0; i < LED_MATRIX_BOXES; i++){
        displayGlyph(glyphs[i], i, glyph_alpha[i]);
    }


    //populate transition matrix
    for (i = 0; i < LED_MATRIX_WIDTH; i++)
        for (int j = 0; j < LED_MATRIX_HEIGHT; j++)
        display_transition.set(i, j, ofClamp(ofRandom(1)*254 + global_value, 0, 254));

    //populate totem A matrix
    for(i = 0; i < LED_MATRIX_WIDTH; i++){
        for(j = 0; j < LED_MATRIX_HEIGHT; j++){
            totem_side_A.addTo(i, j, display_snn_raw.get(i,j), mixing_val_A[0]);
            totem_side_A.addTo(i, j, display_snn_output.get(i,j), mixing_val_A[1]);
            totem_side_A.addTo(i, j, display_glyph.get(i,j), mixing_val_A[2]);
            totem_side_A.addTo(i, j, display_transition.get(i,j), mixing_val_A[3]);
        }
    }


    //populate totem B matrix
    /*
     for(i = 0; i < LED_MATRIX_WIDTH; i++){
     for(j = 0; j < LED_MATRIX_HEIGHT; j++){
     totem_side_B.addTo(i, j, display_snn_raw.get(i,j), mixing_val_B[0]);
     totem_side_B.addTo(i, j, display_snn_output.get(i,j), mixing_val_B[1]);
     totem_side_B.addTo(i, j, display_glyph.get(i,j), mixing_val_B[2]);
     totem_side_B.addTo(i, j, display_transition.get(i,j), mixing_val_B[3]);
     }
     }
     */



    //----------
    //serial
    //----------

    //flush serial
    totem_side_A.flush();
    //totem_side_B.flush();

    //Serial watchdog
    //msSinceLastOutput_A = totem_side_A.check();
    //msSinceLastOutput_B = totem_side_B.check();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(100);
    ofDrawBitmapString("frame rate: "+ofToString(ofGetFrameRate(), 2), 220,20);
    ofDrawBitmapString("serial port : "+ofToString(ofGetFrameRate(), 2), 220,20);
    ofDrawBitmapString("output time window : "+ofToString(output_time_window), 220,50);

    //draw displays
    display_snn_raw.drawOnDisplay(display_size, 0, 10, 10);
    display_snn_output.drawOnDisplay(display_size, 0, 40, 10);
    display_glyph.drawOnDisplay(display_size, 0, 70, 10);
    display_transition.drawOnDisplay(display_size, 0, 100, 10);
    totem_side_A.drawOnDisplay(display_size, 0, 150, 10);
    //totem_side_B.drawOnDisplay(display_size, 0, 180, 10);

    //for(i=10; i>0;i--){ofDrawBitmapString(ofToString(output_group_value[i]), 200,i*80);}

}

//--------------------------------------------------------------
void ofApp::initSNN(){
    ConstParams::Number_Of_Neurons = set_number_of_neurons;
    ConstParams::Inhibitory_Portion = set_inhibitory_portion;
    ConstParams::Number_Of_Inhibitory = ConstParams::Number_Of_Neurons/ConstParams::Inhibitory_Portion;
    ConstParams::Number_Of_Connection = set_number_of_connections;

    ConstParams::Network_Type = set_network_type;
    ConstParams::Excitatory_Neuron_Type = set_excitatory_neuron_type;
    ConstParams::Inhibitory_Neuron_Type = set_inhibitory_neuron_type;

    ConstParams::Input_Portion  = set_input_portion;
    ConstParams::Output_Portion = set_output_portion;
    ConstParams::Input_Group_Size  = set_input_group_size;
    ConstParams::Output_Group_Size = set_output_group_size;
    ConstParams::Input_Neuron_Size  = ConstParams::Number_Of_Neurons/ConstParams::Input_Portion;
    ConstParams::Output_Neuron_Size = ConstParams::Number_Of_Neurons/ConstParams::Output_Portion;
    ConstParams::Input_Neuron_Per_Group  = ConstParams::Input_Neuron_Size/ConstParams::Input_Group_Size;
    ConstParams::Output_Neuron_Per_Group = ConstParams::Output_Neuron_Size/ConstParams::Output_Group_Size;

    spike_net.init();
}

//--------------------------------------------------------------
GlyphBlockFactory ofApp::createTopFactory() {
  float topTypeWeights[N_TYPES];
  float topRotationWeights[N_ROTATIONS];
  float topTranslationWeights[N_TRANSLATIONS];
  GlyphBlockFactory::generateSmoothWeights(topTypeWeights, ofClamp(glyph_top_type, 0, 1), N_TYPES, false);
  GlyphBlockFactory::generateSmoothWeights(topRotationWeights, ofClamp(glyph_top_rotation, 0, 1), N_ROTATIONS, true);
  // Note: Low probability of diverging from top preferred translation.
  GlyphBlockFactory::generateSmoothWeights(topTranslationWeights, ofMap(topPreferredTranslation, 0, MAX_TRANSLATION, 0, 1), N_TRANSLATIONS, false, 0.9, 0.1, 0.0);

  GlyphBlockFactory topFactory(topTypeWeights, topRotationWeights, topTranslationWeights);
  return topFactory;
}

GlyphBlockFactory ofApp::createSubFactory() {

    float subTypeWeights[N_TYPES];
    float subRotationWeights[N_ROTATIONS];
    float subTranslationWeights[N_TRANSLATIONS];
    GlyphBlockFactory::generateSmoothWeights(subTypeWeights, ofClamp(glyph_sub_type, 0, 1), N_TYPES, false);
    GlyphBlockFactory::generateSmoothWeights(subRotationWeights, ofClamp(glyph_sub_rotation, 0, 1), N_ROTATIONS, true);
   GlyphBlockFactory::generateSmoothWeights(subTranslationWeights, ofMap(subPreferredTranslation, 0, MAX_TRANSLATION, 0, 1), N_TRANSLATIONS, false);

    GlyphBlockFactory subFactory(subTypeWeights, subRotationWeights, subTranslationWeights);
    return subFactory;
}

Glyph ofApp::addGlyph()
{
    GlyphBlockFactory topFactory = createTopFactory();
    GlyphBlockFactory subFactory = createSubFactory();

    // Create glyph.
    return Glyph(topFactory, subFactory);
}


//--------------------------------------------------------------
void ofApp::displayGlyph(const Glyph& glyph, int box, float alpha){
    box = LED_MATRIX_BOXES - 1 - box;
    int row = box * LED_MATRIX_HEIGHT_PER_BOX;
    for (int x = 0; x < GLYPH_WIDTH; x++)
    {
        for (int y = 0; y < GLYPH_HEIGHT; y++)
        {
            bool isOn = glyph.get(x, y);
            display_glyph.set(x, row + y, isOn ? (254*alpha) : 0);
        }
    }
}

Izhikevich& ofApp::getNeuron(int x, int y) {
  y = LED_MATRIX_HEIGHT - 1 - y;
  return spike_net.neurons[ x + y * LED_MATRIX_WIDTH ];
}

double ofApp::getNeuronV(int x, int y) { return getNeuron(x, y).getV() + neuron_getV_offset; }

//--------------------------------------------------------------
void ofApp::setFrameRate(int & fps){
    ofSetFrameRate(fps);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    std::cout << (char)key << std::endl;
    switch (key) {

// //        case 'X': glyph_top_type = TYPE_X / float(MAX_TYPE); break;
//         case 'I': glyph_top_type = TYPE_I / float(MAX_TYPE); break;
//         case 'L': glyph_top_type = TYPE_L / float(MAX_TYPE); break;
//         case 'T': glyph_top_type = TYPE_T / float(MAX_TYPE); break;
//         case 'H': glyph_top_type = TYPE_H / float(MAX_TYPE); break;
//         case 'J': glyph_top_type = TYPE_J / float(MAX_TYPE); break;
//         case 'U': glyph_top_type = TYPE_U / float(MAX_TYPE); break;
//         case 'O': glyph_top_type = TYPE_O / float(MAX_TYPE); break;
//
// //        case 'x': glyph_sub_type = TYPE_X / float(MAX_TYPE); break;
//         case 'i': glyph_sub_type = TYPE_I / float(MAX_TYPE); break;
//         case 'l': glyph_sub_type = TYPE_L / float(MAX_TYPE); break;
//         case 't': glyph_sub_type = TYPE_T / float(MAX_TYPE); break;
//         case 'h': glyph_sub_type = TYPE_H / float(MAX_TYPE); break;
//         case 'j': glyph_sub_type = TYPE_J / float(MAX_TYPE); break;
//         case 'u': glyph_sub_type = TYPE_U / float(MAX_TYPE); break;
//         case 'o': glyph_sub_type = TYPE_O / float(MAX_TYPE); break;

        case 'S': glyph_top_rotation = ROTATION_0   / float(MAX_ROTATION); break;
        case 'D': glyph_top_rotation = ROTATION_90  / float(MAX_ROTATION); break;
        case 'F': glyph_top_rotation = ROTATION_180 / float(MAX_ROTATION); break;
        case 'G': glyph_top_rotation = ROTATION_270 / float(MAX_ROTATION); break;

        case 's': glyph_sub_rotation = ROTATION_0   / float(MAX_ROTATION); break;
        case 'd': glyph_sub_rotation = ROTATION_90  / float(MAX_ROTATION); break;
        case 'f': glyph_sub_rotation = ROTATION_180 / float(MAX_ROTATION); break;
        case 'g': glyph_sub_rotation = ROTATION_270 / float(MAX_ROTATION); break;

        case 'Q': topPreferredTranslation = TRANSLATION_TOP; break;
        case 'A': topPreferredTranslation = TRANSLATION_MIDDLE; break;
        case 'Z': topPreferredTranslation = TRANSLATION_BOTTOM; break;

        case 'q': subPreferredTranslation = TRANSLATION_TOP; break;
        case 'a': subPreferredTranslation = TRANSLATION_MIDDLE; break;
        case 'z': subPreferredTranslation = TRANSLATION_BOTTOM; break;

        case '+': glyph_sub_activation_threshold = ofClamp(glyph_sub_activation_threshold + 0.05, 0, 1); break;
        case '-': glyph_sub_activation_threshold = ofClamp(glyph_sub_activation_threshold - 0.05, 0, 1); break;

        case '1': glyph_top_mutation_rate = ofClamp(glyph_top_mutation_rate - 0.005, 0, 1); break;
        case '2': glyph_top_mutation_rate = ofClamp(glyph_top_mutation_rate + 0.005, 0, 1); break;

        case '3': glyph_top_type = ofClamp(glyph_top_type - 0.05, 0, 1); break;
        case '4': glyph_top_type = ofClamp(glyph_top_type + 0.05, 0, 1); break;

        case '5': glyph_sub_mutation_rate = ofClamp(glyph_sub_mutation_rate - 0.005, 0, 1); break;
        case '6': glyph_sub_mutation_rate = ofClamp(glyph_sub_mutation_rate + 0.005, 0, 1); break;

        case '7': glyph_sub_type = ofClamp(glyph_sub_type - 0.05, 0, 1); break;
        case '8': glyph_sub_type = ofClamp(glyph_sub_type + 0.05, 0, 1); break;

    }

    evolveGlyphs(glyph_top_mutation_rate, glyph_sub_mutation_rate);
}

void ofApp::evolveGlyphs(float topMutationRate, float subMutationRate) {

  // Update factories.
  GlyphBlockFactory topFactory = createTopFactory();
  GlyphBlockFactory subFactory = createSubFactory();

  // Evolve glyphs after any keypress.
  for(int i = 0; i < LED_MATRIX_BOXES; i++){
    for (int top = 0; top < N_TOP_BLOCKS; top++) {
      glyphs[i].evolveTopBlock(topFactory, top, topMutationRate);

      for (int x=0; x<BLOCK_SIDE; x++)
        for (int y=0; y<BLOCK_SIDE; y++) {
          glyphs[i].evolveSubBlock(topFactory, top, x, y, subMutationRate);
        }
    }

    glyphs[i].update(glyph_sub_activation_threshold);
  }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
