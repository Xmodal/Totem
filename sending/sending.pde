/*
  Dynamic Light
  Matthew Loewen
  2/12/2019
*/

import processing.serial.*;

final int COLAMT = 9;
final int ROWAMT = 360;

Serial myPort;  

Pixel[][] pixel = new Pixel[COLAMT][ROWAMT];

int myTimer = millis();

void setup() {

  //list serial ports
  //connect to one
  println("Available Serials :");
  println(Serial.list());
  String portName = "COM4";
  myPort = new Serial(this, portName, 2500000);

  //make new pixels
  for (int i = 0; i < COLAMT; i++) {
    for (int z = 0; z < ROWAMT; z++) {
      pixel[i][z] = new Pixel();
    }
  }
}

void draw() {

   //turn on the leds w/ ranomd vals
  myPort.clear();
  myPort.write(255);
  for (int i = 0; i < COLAMT; i++) {
    for (int z = 0; z < ROWAMT; z++) {
      //send data
      myPort.write(byte(random(0,254)));
    }
  } 
  
  //wait 2 seconds
  delay(2000);
  
  //turn off the leds
  myPort.clear();
  myPort.write(255);
  for (int i = 0; i < COLAMT; i++) {
    for (int z = 0; z < ROWAMT; z++) {
      //send data
      myPort.write(byte(0));
    }
  } 
}
