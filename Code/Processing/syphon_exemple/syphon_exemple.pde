import codeanticode.syphon.*;

SyphonServer server;

void settings() {
  size(9,360, P3D);
  PJOGL.profile=1;
}

void setup() {
  // Create syhpon server to send frames out.
  server = new SyphonServer(this, "Processing Syphon");
}

void draw() {
  background(0);
  lights();
  translate(width/2, 0);
  rotateX(frameCount * 0.01);
  rotateY(frameCount * 0.01);  
  box(15);
  server.sendScreen();
}

void stop()
{
  super.exit();
  println("sdfsdf");
}