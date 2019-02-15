import gab.opencv.*;
import processing.video.*;

import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress recipient;

OpenCV opencv;
Capture video;

void setup() {
  size(320, 240);
  
  oscP5 = new OscP5(this,12000);  
  recipient = new NetAddress("127.0.0.1",12001);
  
  video = new Capture(this, 640/2, 480/2, 15);
  opencv = new OpenCV(this, 640/2, 480/2);
  video.start();
}

void draw() {
  background(0);
  opencv.loadImage(video);
  opencv.calculateOpticalFlow();

  //image(video, 0, 0);
  //translate(video.width,0);
  stroke(255,0,0);
  opencv.drawOpticalFlow();
  
  PVector aveFlow = opencv.getAverageFlow();
  int flowScale = 50;
  
  opticalFlowAnalysis(opencv.getAverageFlow());
  
  stroke(255);
  strokeWeight(2);
  line(video.width/2, video.height/2, video.width/2 + aveFlow.x*flowScale, video.height/2 + aveFlow.y*flowScale);
  
  OscMessage aveFlowMessage = new OscMessage("/aveFlow");
  aveFlowMessage.add(aveFlow.x);                          //message looks like: "/aveFlow/[x value]/[y value]"
  aveFlowMessage.add(aveFlow.y);
  oscP5.send(aveFlowMessage, recipient);
  
  aveFlowMessage.print();
}

void captureEvent(Capture c) {
  c.read();
}

/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  
  //theOscMessage.print();
  
}

void opticalFlowAnalysis(PVector flow){
  println(flow);
}