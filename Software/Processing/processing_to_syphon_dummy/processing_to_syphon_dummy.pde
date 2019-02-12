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
  canvas.noStroke();
  color white = color(200);
  canvas.set(0,y,white);
  canvas.set(1,y,white);
  canvas.set(2,y,white);
  canvas.set(3,y,white);
  canvas.set(4,y,white);
  canvas.set(5,y,white);
  canvas.set(6,y,white);
  canvas.set(7,y,white);
  canvas.set(8,y,white);
  canvas.set(9,y,white);
  canvas.endDraw();
  image(canvas, 0, 0);
  server.sendImage(canvas);
  y = (y+1)%height;
}