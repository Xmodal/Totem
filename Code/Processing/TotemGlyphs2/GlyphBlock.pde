final int TYPE_I = 0;
final int TYPE_L = 1;
final int TYPE_T = 2;
final int TYPE_U = 3;
final int TYPE_O = 4;
final int TYPE_VOID = 5;

final int ROTATION_0   = 0;
final int ROTATION_90  = 1;
final int ROTATION_180 = 2;
final int ROTATION_270 = 3;

final int TRANSLATION_TOP    = 0;
final int TRANSLATION_MIDDLE = 1;
final int TRANSLATION_BOTTOM = 2;

class GlyphBlock
{
  boolean[][] matrix;

  GlyphBlock(int type, int rotation, int translation)
  {
    // Get base block.
    matrix = createBase(type);
    
    // Translate.
    matrix = translate(matrix, translation);

    // Rotate.
    for (int r = 0; r < rotation; r++)
      matrix = rotate90(matrix);
  }
  
  // Returns the value of the pixel at (i, j).
  boolean get(int i, int j) { return matrix[i][j]; }
  
  void set(int i, int j, boolean value) {
    matrix[i][j] = value;
  }
  
  boolean[][] createBase(int type)
  {
    switch (type) 
    {
      case TYPE_I:
      // . . . 
      // * * *
      // . . .
        return new boolean[][] { { false, false, false },
                                 { true,  true,  true  },
                                 { false, false, false } };
                                   
      case TYPE_L:
      // * . . 
      // * . .
      // * * *
        return new boolean[][] { { true,  false, false },
                                 { true,  false, false },
                                 { true,  true,  true  } };
      case TYPE_T:
      // * . . 
      // * * *
      // * . .
        return new boolean[][] { { false, true,  false  },
                                 { true,  true,  true   },
                                 { false, false, false  } };
      case TYPE_U:
      // * . * 
      // * . *
      // * * *
        return new boolean[][] { { true,  false, true  },
                                 { true,  false, true  },
                                 { true,  true,  true  } };
      case TYPE_O:
      // * * *
      // * . *
      // * * *
        return new boolean[][] { { true,  true,  true  },
                                 { true,  false, true  },
                                 { true,  true,  true  } };
      case TYPE_VOID:
      // . . .
      // . . .
      // . . .
        return new boolean[][] { { false, false, false  },
                                 { false, false, false  },
                                 { false, false, false  } };
      default: return null;
    }
  }
    
  boolean[][] rotate90(boolean[][] m) {
      return new boolean[][] {
        { m[2][0], m[1][0], m[0][0] },
        { m[2][1], m[1][1], m[0][1] },
        { m[2][2], m[1][2], m[0][2] }
      };
  }
    
  boolean[][] translate(boolean[][] m, int translation) {
    switch (translation) {
      case TRANSLATION_TOP:
        return new boolean[][] {
          { m[1][0], m[1][1], m[1][2] },
          { m[2][0], m[2][1], m[2][2] },
          { false,   false,   false   } };
      case TRANSLATION_BOTTOM:
        return new boolean[][] {
          { false,   false,   false   },
          { m[0][0], m[0][1], m[0][2] },
          { m[1][0], m[1][1], m[1][2] } };
      default:
        return m;
    }
  }
  
  boolean rowIsEmpty(int row) {
    for (int i=0; i<BLOCK_SIDE; i++)
      if (matrix[row][i])
        return false;
    return true;
  }
  
}
