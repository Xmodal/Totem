#include "ofApp.h"

LedMatrix led_matrix_snn_raw(2500000, "/dev/tty.usbmodem4621901", false);


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("TOTEM");
    ofSetBackgroundAuto(true);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    ofBackground(0);
    
    std::cout.precision(11);
    
    setupGui();
    
    //Re-initialisation of spike net in the keyPress function
    spike_net.init(); //just to make sure there is no issue
  
    //------
    //DISPLAY
    //------
    led_matrix_snn_raw.setup();
    
    //------
    //OSC
    //------
    
    ofxSubscribeOsc(7511, "/SNN/stimulation", stimulation_val);
    
}
//--------------------------------------------------------------
void ofApp::update(){
    updateGui();
    
    //update parameters
    for(i=0; i < ConstParams::Input_Group_Size; i++){
        spike_net.stimulation(i, stimulation_val[i]); // (input group id, stimlation strength)
    }

    
    //update processes
    spike_net.update();
    
    //update displays
    led_matrix_snn_raw.clear();
    
    for(int i=0; i<ConstParams::Number_Of_Neurons; i++){
        led_matrix_snn_raw.set(i%9, int(i/9), spike_net.neurons[i].getV()+100, set_mix);
    }
    
    //flush serial
    //led_matrix_snn_raw.flush();
    
    
    
    
   
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    
    //draw displays
    led_matrix_snn_raw.drawOnDisplay(size_display, 1, 10, 10);
    
}

//--------------------------------------------------------------
void ofApp::initParams(){
    ConstParams::Number_Of_Neurons = set_number_of_neurons;
    ConstParams::Number_Of_Inhibitory = set_number_of_neurons/set_inhibitory_number;
    ConstParams::Number_Of_Connection = 20;
    ConstParams::Network_Type = 6;
    ConstParams::Excitatory_Neuron_Type = set_excitatory_neuron_type;
    ConstParams::Inhibitory_Neuron_Type = set_inhibitory_neuron_type;
    ConstParams::Input_Neuron_Size  = set_number_of_neurons/set_input_number;
    ConstParams::Output_Neuron_Size = ConstParams::Number_Of_Neurons/5;
    ConstParams::Output_Group_Size = ConstParams::Output_Group_Size;
    ConstParams::Input_Group_Size  = ConstParams::Input_Group_Size;
    ConstParams::Network_Type = set_network_type;
    ConstParams::Number_Of_Connection = set_number_of_connection;
}

//--------------------------------------------------------------
void ofApp::setupGui(){
    gui.setup();
    gui.add(size_display.setup("Display size", 3, 1, 10));
    gui.add(fps.setup("FPS", 30, 1, 300));
    gui.add(set_mix.setup("mix", 1, -1, 5));
    gui.add(start_message.setup("press <space> to restart", ""));
    gui.add(set_stp_flag.setup( "stp flag" , false));
    gui.add(set_stdp_flag.setup( "stdp flag" , true));
    gui.add(set_decay_rate.setup( "Decay rate (*10)" , 0.999995, 0.999, 1)); //it should be a double...
    gui.add(set_number_of_neurons.setup( "Number of Neurons" , 3240, 0, 3240));
    gui.add(set_network_type.setup( "Network type" , 3, 0, 3));
    gui.add(network_types.setup("0:sparce 1:random 2:uniform 3:grid", ""));
    gui.add(set_inhibitory_neuron_type.setup( "Inhibitory type" , 5, 1, 5));
    gui.add(set_excitatory_neuron_type.setup( "Excitatory type" , 5, 1, 5));
    gui.add(neuron_type.setup( "1:spiking_demo 2:resonator_demo 3:spiking 3:resonator 3:chattering", ""));
    gui.add(set_inhibitory_number.setup( "Inhibitory portion" , 5, 1, 15));
    gui.add(set_input_number.setup( "Input portion" , 5, 1, 15));
    gui.add(set_number_of_connection.setup( "Number of connections" , 20, 1, 60));
    gui.add(set_led_val_offset.setup( "LED offset" , 50, -100, 100));
}

//--------------------------------------------------------------
void ofApp::updateGui(){
    ofSetFrameRate(fps);
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
    if(key == ' '){
        initParams();
        spike_net.init();
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
