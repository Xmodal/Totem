/**
 * This class represents a single glyph. A glyph is made out of
 * several GlyphBlock each of which represents a 3x3 atomic item.
 *
 * It is organized so that one glyph fills a 9x36 box. The glyph
 * follows a hierarchical generative structure.
 * 
 * At the top-level: 4 GlyphBlock are selected each representing
 * the sub-levels will be organized:
 * T0
 * T1
 * T2
 * T3
 *
 * At the sub-level, a set of GlyphBlocks is generated for each of the
 * "pixels" of the Ti GlyphBlocks.
 * 
 */
class Glyph
{
  // The top-level blocks.
  GlyphBlock[] topBlocks;

  // The sub-level blocks.
  GlyphBlock[][][] blocks;

  // The matrix of on/off pixels representing the glyph.
  boolean[][] matrix;

  // Creates a new glyph by using the given generative parameters.
  Glyph(float[] typeWeights, float[] rotationWeights, float[] translationWeights)
  {
    // Create top-level blocks.
    topBlocks = new GlyphBlock[N_TOP_BLOCKS];
    blocks = new GlyphBlock[N_TOP_BLOCKS][BLOCK_SIDE][BLOCK_SIDE];
    for (int i=0; i<N_TOP_BLOCKS; i++)
    {
      GlyphBlock currentTopBlock = topBlocks[i] = generateGlyphBlock(typeWeights, rotationWeights, translationWeights);

      for (int j=0; j<BLOCK_SIDE; j++) {
        for (int k=0; k<BLOCK_SIDE; k++) {
          GlyphBlock newBlockOnTheBlock;
          if (topBlocks[i].get(j, k)) {
            if (random(1) < subdivisionProbability)
            {
              newBlockOnTheBlock = generateGlyphBlock(typeWeights, rotationWeights, translationWeights);
            }
            else {
              newBlockOnTheBlock = new GlyphBlock(
                currentTopBlock.getIfExists(j, k-1),
                currentTopBlock.getIfExists(j-1, k),
                currentTopBlock.getIfExists(j, k+1),
                currentTopBlock.getIfExists(j+1, k));
            }
          }
          else
            newBlockOnTheBlock = new GlyphBlock(TYPE_VOID, ROTATION_0, TRANSLATION_TOP);
          blocks[i][j][k] = newBlockOnTheBlock;
        }
      }
    }

    // Create matrix using blocks.
    matrix = new boolean[N_PIXELS_WIDTH][N_PIXELS_HEIGHT];
    // Each top block.
    for (int i=0, yOffset=0; i<N_TOP_BLOCKS; i++) {
      // Each row.
      for (int j=0; j<BLOCK_SIDE; j++, yOffset+=BLOCK_SIDE) {
        // Each column.
        for (int k=0, xOffset=0; k<BLOCK_SIDE; k++, xOffset+=BLOCK_SIDE) {
          // Get current block.
          GlyphBlock currentBlock = blocks[i][j][k];
          // Copy it into the matrix in the right spot.
          for (int x=0; x<BLOCK_SIDE; x++) {
            for (int y=0; y<BLOCK_SIDE; y++) {
              matrix[xOffset+x][yOffset+y] = currentBlock.get(y, x);
            }
          }
        }
      }
    }

    //for (int r=0; r<BLOCK_SIDE; r++)
    //{
    //  // Fill up one row.
    //  boolean[] row = new boolean[N_PIXELS_WIDTH];
    //  int c=0; // column
    //  boolean rowIsEmpty = true;
    //  for (int b=0; b<N_BLOCKS; b++)
    //  {
    //    for (int j=0; j<BLOCK_SIDE; j++, c++)
    //    {
    //      boolean val = blocks[b].get(r, j);
    //      if (val)
    //        rowIsEmpty = false;
    //      row[c] = val;
    //    }
    //  }

    //// If row is empty don't copy to main matrix.
    //if (!rowIsEmpty)
    //  matrix.add(row);
  }

  GlyphBlock generateGlyphBlock(float[] typeWeights, float[] rotationWeights, float[] translationWeights) {
    // Randomly choose type, rotation and translation.
    int type        = weightedRandom(typeWeights);
    int rotation    = weightedRandom(rotationWeights);
    int translation = weightedRandom(translationWeights);
    // Create block.
    return new GlyphBlock(type, rotation, translation);
  }

  // Displays the glyph.
  void display()
  {
    noStroke();
    for (int i=0; i<N_PIXELS_WIDTH; i++)
    {
      for (int j=0; j<N_PIXELS_HEIGHT; j++)
      {
        boolean isOn = matrix[i][j];
        int x = i*PIXEL_SIDE;
        int y = j*PIXEL_SIDE;
        fill(isOn ? 255 : 0);
        rect(x, y, PIXEL_SIDE, PIXEL_SIDE);
      }
    }
  }

//  // Returns the value of the pixel at (i, j).
//  boolean get(int i, int j) {
//    return matrix[j][i];
//  }
}
