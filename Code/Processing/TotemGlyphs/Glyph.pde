/**
 * This class represents a single glyph. A glyph is made out of
 * several GlyphBlock each of which represents a 3x3 atomic item.
 */
class Glyph
{
  // The blocks.
  GlyphBlock[] blocks;
  
  // The matrix of on/off pixels representing the glyph.
  ArrayList<boolean[]> matrix;
  
  // Creates a new glyph by using the given generative parameters.
  Glyph(float[] typeWeights, float[] rotationWeights, float[] translationWeights)
  {
    // Create blocks.
    blocks = new GlyphBlock[N_BLOCKS];
    
    // Choose all blocks.
    for (int i=0; i<N_BLOCKS; i++)
    {
      // Randomly choose type, rotation and translation.
      int type        = weightedRandom(typeWeights);
      int rotation    = weightedRandom(rotationWeights);
      int translation = weightedRandom(translationWeights);
      blocks[i] = new GlyphBlock(type, rotation, translation);
    }
    
    // Create matrix using blocks. Each row is 9 pixels wide. Number
    // of rows vary between 1 and 3.
    matrix = new ArrayList<boolean[]>();
    for (int r=0; r<BLOCK_SIDE; r++)
    {
      // Fill up one row.
      boolean[] row = new boolean[N_PIXELS_WIDTH];
      int c=0; // column
      boolean rowIsEmpty = true;
      for (int b=0; b<N_BLOCKS; b++)
      {
        for (int j=0; j<BLOCK_SIDE; j++, c++)
        {
          boolean val = blocks[b].get(r, j);
          if (val)
            rowIsEmpty = false;
          row[c] = val;
        }
      }
      
      // If row is empty don't copy to main matrix.
      if (!rowIsEmpty)
        matrix.add(row);
    }
  }
  
  // Displays the glyph starting at given vertical coordinate.
  void display(int y)
  {
    noStroke();
    for (int i=0; i<nRows(); i++)
    {
      for (int j=0; j<N_PIXELS_WIDTH; j++)
      {
        boolean isOn = get(i, j);
        int x = j*PIXEL_SIDE;
        fill(isOn ? 255 : 0);
        rect(x, y, PIXEL_SIDE, PIXEL_SIDE);
      }
      y += PIXEL_SIDE;
    }
  }
  
  // Returns the number of rows.
  int nRows() {
    return matrix.size();
  }
  
  // Returns the value of the pixel at (i, j).
  boolean get(int i, int j) {
    return matrix.get(i)[j];
  }
}
