/*
 Digial light board 
 Dynamic Light
 Matthew Loewen
 2/13/2019
 
 
 This code is for a single cell of lights for the Totem project
 
 */

//import librarys for OSC
import oscP5.*;
import netP5.*;

int brightness = 0;

//vars for OSC
OscP5 oscP5;
NetAddress myRemoteLocation;

final int COLAMT = 9;
final int ROWAMT = 36;
final int SIZE = 15;

//spaceing of lights
final int SPACEX = SIZE + 10;
final int SPACEY = SIZE + 12;

//loop counter
int k = 0;

//2D array for all pixels
Pixel[][] pixel = new Pixel[COLAMT][ROWAMT];

void setup() {

  //set up the scene
  size(216, 961); //DO NOT USE VARS OR ANY MATH EXPRESSIONS HERE
  background(40);
  stroke(20);

  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, 12000);

  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("127.0.0.1", 12000);

  //make new pixels
  for (int i = 0; i < COLAMT; i++) {
    for (int z = 0; z < ROWAMT; z++) {
      pixel[i][z] = new Pixel(SIZE, i * SPACEX, z * SPACEY );
      //display the pixels turned off
      pixel[i][z].display();
    }
  }
}

void draw() {
  //nothing to do here

  for (int i = 0; i < COLAMT; i++) {
    for (int z = 0; z < ROWAMT; z++) {
      pixel[i][z].display(brightness);
    }
  }
}


/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());
  println(" value: "+theOscMessage.get(0).intValue());

  if (theOscMessage.checkAddrPattern("/led") == true) {
    brightness = theOscMessage.get(0).intValue();
  }
}
