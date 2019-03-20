import processing.serial.*;
import codeanticode.syphon.*;

PGraphics canvas;
Serial myPort;  
SyphonClient client;


void setup()
{
  size(9, 72, P3D); //window size has to be the same dimension as the totem pixel array
  
  println("Available Serials :");
  println(Serial.list());
  String portName = "/dev/cu.usbmodem4621901";
  myPort = new Serial(this, portName, 2500000);
  
  println();
  
  println("Available Syphon servers:");
  println(SyphonClient.listServers());
  client = new SyphonClient(this);
  
  background(0);
}

void draw()
{
  if (client.newFrame()) {
    canvas = client.getGraphics(canvas);
    image(canvas, 0, 0, width, height);   
    myPort.write(255);
    for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < height; j++)
      {
        myPort.write((get(i, j) > 254) ? 254 : get(i, j));
      }
    }    
  }  
}


void keyPressed() {
  if (key == ' ') {
    client.stop();  
  } else if (key == 'd') {
    println(client.getServerName());
  }
}