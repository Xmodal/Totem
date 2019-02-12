import codeanticode.syphon.*;

PGraphics canvas;
SyphonServer server;

void setup() { 
  size(9,72, P3D);
  canvas = createGraphics(9, 72, P3D);
  frameRate(10);
  // Create syhpon server to send frames out.
  server = new SyphonServer(this, "Processing_Syphon");
}

int y = 0;

void draw() {
  canvas.beginDraw();
  canvas.background(0);
  canvas.stroke(255);
  canvas.line(0, y, width, y);
  canvas.endDraw();
  image(canvas, 0, 0);
  server.sendImage(canvas);
  y = (y+1)%height;
}