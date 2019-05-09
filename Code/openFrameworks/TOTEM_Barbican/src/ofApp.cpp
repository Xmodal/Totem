#include "ofApp.h"

LedMatrix display_snn_raw(0, "", false);
LedMatrix display_snn_output(0, "", false);
LedMatrix display_glyph(0, "", false);
LedMatrix display_transition(0, "", false);
//LedMatrix totem_side_A(2500000, "/dev/tty.usbmodem4621901", true);
LedMatrix totem_side_A(2500000, "/dev/tty.usbmodem4072061", true);
//LedMatrix totem_side_A(2500000, "/dev/tty.usbmodem4075901", true);
//LedMatrix totem_side_A(2500000, "/dev/tty.usbmodem4660021", true);

LedMatrix totem_side_B(2500000, "", true);


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("TOTEM");
    ofSetBackgroundAuto(true);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    ofBackground(10);
    
    std::cout.precision(11);
    
    setupGui();
    
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
    
    ofxSubscribeOsc(7511, "/SNN_output/Output_Time_Window", Output_Time_Window);
    ofxSubscribeOsc(7511, "/SNN_output/spiked_scalar", spiked_scalar);
    
    ofxSubscribeOsc(7511, "/transition/global_value", global_value);
    
    ofxSubscribeOsc(7511, "/mixer/A/faders", mixing_val_A);
    ofxSubscribeOsc(7511, "/mixer/B/faders", mixing_val_B);
    
    ofxSubscribeOsc(7511, "/display/fps", fps);
    
    //PUBLISH
    //ofxPublishOsc("localhost", 7510, "/display/A/ms_since_last_output", &msSinceLastOutput_A, false);
    //ofxPublishOsc("localhost", 7510, "/display/B/ms_since_last_output", &msSinceLastOutput_B, false);
//    ofxPublishOsc("localhost", 7510, "/SNN_output/spiked_output", &spiked_output[], false); // not working with osfPublishAsArray
    
    
    
}
//--------------------------------------------------------------
void ofApp::update(){
    ofSetFrameRate(fps);
    updateGui();
    
    //----------
    //update parameters
    //----------
    for(i=0; i < ConstParams::Input_Group_Size; i++){
        spike_net.stimulation(i, stimulation_val[i]); // (input group id, stimlation strength)
    }
    //----------
    //update processes
    //----------
    spike_net.update();
    
    //get firing rates
    float n = ConstParams::Output_Neuron_Size/ConstParams::Output_Group_Size;
    osc_spiked_output.clear();
    osc_spiked_output.setAddress("/SNN_output/spiked_output");
    for(i=0;i<ConstParams::Output_Group_Size;i++){
        spiked_output[i] = spike_net.getSpikedOutput(i)/(n*Output_Time_Window);
        osc_spiked_output.addFloatArg(spiked_output[i]);
    }
    osc_sender_msx.sendMessage(osc_spiked_output);
    if(ofGetFrameNum()%Output_Time_Window == 0){
        spike_net.clearSpikedNeuronId();
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
        display_snn_raw.set(i%9, int(i/9), ofClamp(spike_net.neurons[i].getV()+neuron_getV_offset, 0, 254));
    }
    
    //populate SNN output matrix
    for(i=0; i<ConstParams::Number_Of_Neurons; i++){
        display_snn_output.set(i%9, int(i/9), ofClamp(spiked_scalar*spiked_output[int(i/324)], 0, 254));
    }
    
    //populate glyph matrix
    
    //populate transition matrix
    for(i=0; i<ConstParams::Number_Of_Neurons; i++){
        display_transition.set(i%9, int(i/9), global_value);
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
    msSinceLastOutput_A = totem_side_A.check();
    //msSinceLastOutput_B = totem_side_B.check();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    
    //draw displays
    display_snn_raw.drawOnDisplay(size_display, 0, 10, 10);
    display_snn_output.drawOnDisplay(size_display, 0, 50, 10);
    display_glyph.drawOnDisplay(size_display, 0, 90, 10);
    display_transition.drawOnDisplay(size_display, 0, 130, 10);
    totem_side_A.drawOnDisplay(size_display, 0, 170, 10);
    totem_side_B.drawOnDisplay(size_display, 0, 210, 10);
   
    
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
void ofApp::setupGui(){
    gui.setup();
    gui.add(size_display.setup("Display size", 3, 1, 10));
    gui.add(start_message.setup("press <space> to restart", ""));
    
}

//--------------------------------------------------------------
void ofApp::updateGui(){
    ConstParams::Stp_Flag = set_stp_flag;
    ConstParams::Stdp_Flag = set_stdp_flag;
    ConstParams::Decay_Rate = double(set_decay_rate)/10 + 0.9;   //set_decay_rate should be double
    //std::cout << ConstParams::Decay_Rate << std::endl;
}

//--------------------------------------------------------------
void ofApp::setFrameRate(int & fps){
    ofSetFrameRate(fps);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   
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
