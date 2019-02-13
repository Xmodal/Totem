import gab.opencv.*;
import processing.video.*;

Capture video;
OpenCV opencv;

void setup() {
  size(720, 480);
  video = new Capture(this, 640, 480, 15);
  opencv = new OpenCV(this, 640, 480);
  
  opencv.startBackgroundSubtraction(5, 3, 0.5);
  
  video.start();
}

void draw() {
  background(0);
  opencv.loadImage(video);
  
  opencv.updateBackground();
  
  opencv.dilate();
  opencv.erode();
  
  image(video, 0, 0);

  noFill();
  stroke(255, 0, 0);
  strokeWeight(3);
  for (Contour contour : opencv.findContours()) {
    contour.draw();
  }
}

void captureEvent(Capture c) {
  c.read();
}
