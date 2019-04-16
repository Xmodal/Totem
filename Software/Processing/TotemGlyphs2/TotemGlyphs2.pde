final int N_PIXELS_WIDTH  = 9;
final int N_PIXELS_HEIGHT = 36;
final int BLOCK_SIDE = 3;

final int N_TOP_BLOCKS = 4;

int PIXEL_SIDE;

ArrayList<Glyph> text = new ArrayList<Glyph>();

int row;
Glyph currentGlyph;

void setup()
{
  size(90, 360);
  frameRate(5);
  PIXEL_SIDE = width / N_PIXELS_WIDTH;
  
  currentGlyph = addGlyph();
  row = 0;
}

void draw()
{
  // Reset background.
  background(0);
  
  // Draw glyph.
  currentGlyph.display();
}

void keyPressed() {
  if (key == ' ') {
    currentGlyph = addGlyph();
  }
}
Glyph addGlyph() {
  // Build random weights.
  float[] typeWeights = generateSmoothWeights(float(mouseX) / width, 5, false);
  float[] rotationWeights = new float[] { 1, 0.5, 1, 0.5 };
  float[] translationWeights = generateSmoothWeights(float(mouseY) / height, 3, false);

  // Create glyph.
  Glyph nextGlyph = new Glyph(typeWeights, rotationWeights, translationWeights);
  text.add(nextGlyph);
  return nextGlyph;
}
