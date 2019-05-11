#include "ofApp.h"

LedMatrix display_snn_raw(0, "", false);
LedMatrix display_snn_output(0, "", false);
LedMatrix display_glyph(0, "", false);
LedMatrix display_transition(0, "", false);
LedMatrix totem_side_A(2500000, "/dev/tty.usbmodem4621901", true);
LedMatrix totem_side_B(2500000, "/dev/tty.usbmodem4072061", true);
//LedMatrix totem_side_A(2500000, "/dev/tty.usbmodem4075901", true);
//LedMatrix totem_side_A(2500000, "/dev/tty.usbmodem4660021", true);



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("TOTEM");
    ofSetBackgroundAuto(true);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    ofBackground(100);
    
    std::cout.precision(11);
    
    
    //Re-initialisation of spike net in the keyPress function
    spike_net.init(); //just to make sure there is no issue
  
    //------
    //DISPLAY
    //------
    display_snn_raw.setup();
    display_snn_output.setup();
    display_glyph.setup();
    totem_side_A.setup();
    totem_side_B.setup();
    
    //------
    //OSC
    //------
    
    osc_sender_msx.setup("localhost", 7510);
    
    //SUSCRIBE
    ofxSubscribeOsc(7511, "/SNN/stimulation", stimulation_val);
    
    ofxSubscribeOsc(7511, "/SNN/neuron_getV_offset", neuron_getV_offset);
    ofxSubscribeOsc(7511, "/SNN/number_of_neurons", set_number_of_neurons);
    ofxSubscribeOsc(7511, "/SNN/set_network_type", set_network_type);
    ofxSubscribeOsc(7511, "/SNN/set_inhibitory_neuron_type", set_inhibitory_neuron_type);
    ofxSubscribeOsc(7511, "/SNN/set_excitatory_neuron_type", set_excitatory_neuron_type);
    ofxSubscribeOsc(7511, "/SNN/set_inhibitory_portion", set_inhibitory_portion);
    ofxSubscribeOsc(7511, "/SNN/set_input_portion", set_input_portion);
    ofxSubscribeOsc(7511, "/SNN/set_input_group_size", set_input_group_size);
    ofxSubscribeOsc(7511, "/SNN/set_output_portion", set_output_portion);
    ofxSubscribeOsc(7511, "/SNN/set_output_group_size", set_output_group_size);
    ofxSubscribeOsc(7511, "/SNN/set_number_of_connections", set_number_of_connections);
    ofxSubscribeOsc(7511, "/SNN/set_stp_flag", set_stp_flag);
    ofxSubscribeOsc(7511, "/SNN/set_stdp_flag", set_stdp_flag);
    ofxSubscribeOsc(7511, "/SNN/set_decay_rate", set_decay_rate);
    ofxSubscribeOsc(7511, "/SNN/init", [this](){
        initSNN();
    });
    
    ofxSubscribeOsc(7511, "/glyph/glyph_alpha", glyph_alpha);
    ofxSubscribeOsc(7511, "/glyph/glyph_trig_sensibility", glyph_trig_sensibility);
    ofxSubscribeOsc(7511, "/glyph/glyph_trig", glyph_trig_osc, [this](){
        for(int i = 0; i < 10; i++){
            if(glyph_trig_osc[i]){ glyphs[i] = addGlyph();}
        }

    });
    
    
    ofxSubscribeOsc(7511, "/SNN_output/output_time_window", output_time_window);
    ofxSubscribeOsc(7511, "/SNN_output/spiked_scalar", spiked_scalar);
    
    ofxSubscribeOsc(7511, "/transition/global_value", global_value);
    
    ofxSubscribeOsc(7511, "/mixer/A/faders", mixing_val_A);
    ofxSubscribeOsc(7511, "/mixer/B/faders", mixing_val_B);
    
    ofxSubscribeOsc(7511, "/display/fps", fps);
    ofxSubscribeOsc(7511, "/display/display_size", display_size);
    
    //PUBLISH
    //ofxPublishOsc("localhost", 7510, "/display/A/ms_since_last_output", &msSinceLastOutput_A, false);
    //ofxPublishOsc("localhost", 7510, "/display/B/ms_since_last_output", &msSinceLastOutput_B, false);
//    ofxPublishOsc("localhost", 7510, "/SNN_output/spiked_output", &spiked_output[], false); // not working with osfPublishAsArray
    
    ofSleepMillis(5000);
    
    //------
    //GLYPHS
    //------
    row = 0;
    for(int i = 0; i < 10; i++){
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
    
    osc_spiked_output.clear();
    osc_spiked_output.setAddress("/SNN_output/spiked_output");
    for(i=0;i<ConstParams::Output_Group_Size;i++){
        osc_spiked_output.addFloatArg(spiked_output[i]);
    }
    osc_sender_msx.sendMessage(osc_spiked_output);
    
    
    //UPDATE GLYPHS
    for(int i = 0; i < ConstParams::Output_Group_Size; i++){
        //glyph_alpha[i] = ofClamp(spiked_output[i]*spiked_scalar, 0, 254);
        
        if(spiked_output[i] < glyph_trig_sensibility){glyph_trig_done[i] = 0;}
        else if(spiked_output[i] > glyph_trig_sensibility && glyph_trig_done[i] == 0){
            glyphs[i] = addGlyph();
            glyph_trig_done[i] = 1;
        }
        
    }
    
    
    //----------
    //update displays
    //----------
    display_snn_raw.clear();
    display_snn_output.clear();
    display_glyph.clear();
    display_transition.clear();
    totem_side_A.clear();
    totem_side_B.clear();
    
    //populate raw SNN matrix
    for(i=0; i<ConstParams::Number_Of_Neurons; i++){
        display_snn_raw.set(i%9, LED_MATRIX_HEIGHT - 1 - int(i/9), ofClamp(spike_net.neurons[i].getV()+neuron_getV_offset, 0, 254));
    }
    
    //populate SNN output matrix
    /*
    for(i=0; i<ConstParams::Number_Of_Neurons; i++){
        display_snn_output.set(i%9, LED_MATRIX_HEIGHT - 1 - int(i/10), ofClamp(spiked_scalar*spiked_output[int(i/360)], 0, 254));
    }
    */
    
    
    for(k = 0; k < ConstParams::Output_Group_Size; k++){
        for (i = 0; i < LED_MATRIX_WIDTH; i++)
        {
            for (int j = 0; j < LED_MATRIX_HEIGHT_PER_BOX; j++)
            {
                display_snn_output.set(i, 360 - 1 - (k * LED_MATRIX_HEIGHT_PER_BOX + j), output_group_value[k]);
            }
        }
    }
     
    
    //populate glyph matrix
    
    
    /*
    for(i=0; i<LED_MATRIX_WIDTH; i++){
        for(j=0; j<LED_MATRIX_HEIGHT; j++){
            display_glyph.set(i, j, j%36 == 0 ? 255 : 0);
        }
    }
    */
    
    for(int i = 0; i < 10; i++){
        displayGlyph(glyphs[i], 9 - i, glyph_alpha[i]);
    }
    
    
    //populate transition matrix
    for(i=0; i<ConstParams::Number_Of_Neurons; i++){
        //display_transition.set(i%9, int(i/9), global_value);
        display_transition.set(i%9, int(i/9), ofRandom(1)*254);
    }
    
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
    
    for(i = 0; i < LED_MATRIX_WIDTH; i++){
        for(j = 0; j < LED_MATRIX_HEIGHT; j++){
            totem_side_B.addTo(i, j, display_snn_raw.get(i,j), mixing_val_B[0]);
            totem_side_B.addTo(i, j, display_snn_output.get(i,j), mixing_val_B[1]);
            totem_side_B.addTo(i, j, display_glyph.get(i,j), mixing_val_B[2]);
            totem_side_B.addTo(i, j, display_transition.get(i,j), mixing_val_B[3]);
        }
    }
    
    
    
    //----------
    //serial
    //----------
    
    //flush serial
    totem_side_A.flush();
    totem_side_B.flush();
    
    //Serial watchdog
    //msSinceLastOutput_A = totem_side_A.check();
    //msSinceLastOutput_B = totem_side_B.check();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(100);
    ofDrawBitmapString("frame rate: "+ofToString(ofGetFrameRate(), 2), 220,20);
    
    
    //draw displays
    display_snn_raw.drawOnDisplay(display_size, 0, 10, 10);
    display_snn_output.drawOnDisplay(display_size, 0, 40, 10);
    display_glyph.drawOnDisplay(display_size, 0, 70, 10);
    display_transition.drawOnDisplay(display_size, 0, 100, 10);
    totem_side_A.drawOnDisplay(display_size, 0, 150, 10);
    totem_side_B.drawOnDisplay(display_size, 0, 180, 10);
   
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
Glyph ofApp::addGlyph()
{
    float topTypeWeights[N_TYPES];
    float topRotationWeights[N_ROTATIONS];
    float topTranslationWeights[N_TRANSLATIONS];
    GlyphBlockFactory::generateSmoothWeights(topTypeWeights, ofMap(topPreferredType, 0, MAX_TYPE, 0, 1), N_TYPES, false);
    GlyphBlockFactory::generateSmoothWeights(topRotationWeights, ofMap(topPreferredRotation, 0, MAX_ROTATION, 0, 1), N_ROTATIONS, true);
    GlyphBlockFactory::generateSmoothWeights(topTranslationWeights, ofMap(topPreferredTranslation, 0, MAX_TRANSLATION, 0, 1), N_TRANSLATIONS, false);
    
    float subTypeWeights[N_TYPES];
    float subRotationWeights[N_ROTATIONS];
    float subTranslationWeights[N_TRANSLATIONS];
    GlyphBlockFactory::generateSmoothWeights(subTypeWeights, ofMap(subPreferredType, 0, MAX_TYPE, 0, 1), N_TYPES, false);
    GlyphBlockFactory::generateSmoothWeights(subRotationWeights, ofMap(subPreferredRotation, 0, MAX_ROTATION, 0, 1), N_ROTATIONS, true);
    GlyphBlockFactory::generateSmoothWeights(subTranslationWeights, ofMap(subPreferredTranslation, 0, MAX_TRANSLATION, 0, 1), N_TRANSLATIONS, false);
    
    GlyphBlockFactory topFactory(topTypeWeights, topRotationWeights, topTranslationWeights);
    GlyphBlockFactory subFactory(subTypeWeights, subRotationWeights, subTranslationWeights);
    
    // Create glyph.
    return Glyph(topFactory, subFactory, subdivisionProbability);
}


//--------------------------------------------------------------
void ofApp::displayGlyph(const Glyph& glyph, int box, float alpha){
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

//--------------------------------------------------------------
void ofApp::setFrameRate(int & fps){
    ofSetFrameRate(fps);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    std::cout << (char)key << std::endl;
    switch (key) {
            
        case 'I': topPreferredType = TYPE_I; break;
        case 'L': topPreferredType = TYPE_L; break;
        case 'T': topPreferredType = TYPE_T; break;
        case 'U': topPreferredType = TYPE_U; break;
        case 'O': topPreferredType = TYPE_O; break;
        case 'X': topPreferredType = TYPE_X; break;
            
        case 'i': subPreferredType = TYPE_I; break;
        case 'l': subPreferredType = TYPE_L; break;
        case 't': subPreferredType = TYPE_T; break;
        case 'u': subPreferredType = TYPE_U; break;
        case 'o': subPreferredType = TYPE_O; break;
        case 'x': subPreferredType = TYPE_X; break;
            
        case 'S': topPreferredRotation = ROTATION_0; break;
        case 'D': topPreferredRotation = ROTATION_90; break;
        case 'F': topPreferredRotation = ROTATION_180; break;
        case 'G': topPreferredRotation = ROTATION_270; break;
            
        case 's': subPreferredRotation = ROTATION_0; break;
        case 'd': subPreferredRotation = ROTATION_90; break;
        case 'f': subPreferredRotation = ROTATION_180; break;
        case 'g': subPreferredRotation = ROTATION_270; break;
            
        case 'Q': topPreferredTranslation = TRANSLATION_TOP; break;
        case 'A': topPreferredTranslation = TRANSLATION_MIDDLE; break;
        case 'Z': topPreferredTranslation = TRANSLATION_BOTTOM; break;
            
        case 'q': subPreferredTranslation = TRANSLATION_TOP; break;
        case 'a': subPreferredTranslation = TRANSLATION_MIDDLE; break;
        case 'z': subPreferredTranslation = TRANSLATION_BOTTOM; break;
            
        case '+': subdivisionProbability = ofClamp(subdivisionProbability + 0.05, 0, 1); break;
        case '-': subdivisionProbability = ofClamp(subdivisionProbability - 0.05, 0, 1); break;
    }
    
    // Add glyph after any keypress.
    for(int i = 0; i < 10; i++){
        glyphs[i] = addGlyph();
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
