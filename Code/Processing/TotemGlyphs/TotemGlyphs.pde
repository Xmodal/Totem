final int N_PIXELS_WIDTH  = 9;
final int N_PIXELS_HEIGHT = 3;
final int N_BLOCKS = 3;
final int BLOCK_SIDE = 3;
int PIXEL_SIDE;

ArrayList<Glyph> text = new ArrayList<Glyph>();

int row;
Glyph currentGlyph;

void setup()
{
  size(360, 600);
  frameRate(5);
  PIXEL_SIDE = width / N_PIXELS_WIDTH;
  
  currentGlyph = addGlyph();
  row = 0;
}

void draw()
{
  // Reset background.
  background(0);
  
  // Add glyph when ready.
  if (row == currentGlyph.nRows() + 1)
  {
    currentGlyph = addGlyph();
    row = 0;
  }
  
  // Draw glyphs.
  int y = -(currentGlyph.nRows() - row) * PIXEL_SIDE;
  for (int i=text.size()-1; i>=0; i--)
  {
    Glyph g = text.get(i);
    g.display(y);
    y += PIXEL_SIDE * (g.nRows() + 1);
  }
  
  row++;
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
