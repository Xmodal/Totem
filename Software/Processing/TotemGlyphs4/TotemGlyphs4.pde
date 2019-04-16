// Look at the options in keyPressed()
// Each key press changes one of the preferences.
// Uppercases letters will change the look of top-level glyphs
// Lowercase letters will change the look of sub-level glyphs 
//    which are introduced randomly inside the top-level glyph
// +/- change the chance of making a sub-level glyphs (ie. introduce noise)
// Spacebar just generates a new glyph

final int N_PIXELS_WIDTH  = 9;
final int N_PIXELS_HEIGHT = 36;
final int BLOCK_SIDE = 3;

final int N_TOP_BLOCKS = 4;

float subdivisionProbability = 0.05;

final int TYPE_I = 0;
final int TYPE_L = 1;
final int TYPE_T = 2;
final int TYPE_U = 3;
final int TYPE_O = 4;
final int TYPE_VOID = -1;
final int N_TYPES = 5;
final int MAX_TYPE = TYPE_O;

final int ROTATION_0   = 0;
final int ROTATION_90  = 1;
final int ROTATION_180 = 2;
final int ROTATION_270 = 3;
final int N_ROTATIONS = 4;
final int MAX_ROTATION = ROTATION_270;

final int TRANSLATION_TOP    = 0;
final int TRANSLATION_MIDDLE = 1;
final int TRANSLATION_BOTTOM = 2;
final int N_TRANSLATIONS = 3;
final int MAX_TRANSLATION = TRANSLATION_BOTTOM;

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

int topPreferredType = TYPE_T;
int topPreferredRotation = ROTATION_0;
int topPreferredTranslation = TRANSLATION_MIDDLE;

int subPreferredType = TYPE_T;
int subPreferredRotation = ROTATION_0;
int subPreferredTranslation = TRANSLATION_MIDDLE;

void keyPressed() {
  switch (key) {
    
    case 'I': topPreferredType = TYPE_I; break;
    case 'L': topPreferredType = TYPE_L; break;
    case 'T': topPreferredType = TYPE_T; break;
    case 'U': topPreferredType = TYPE_U; break;
    case 'O': topPreferredType = TYPE_O; break;
    
    case 'i': subPreferredType = TYPE_I; break;
    case 'l': subPreferredType = TYPE_L; break;
    case 't': subPreferredType = TYPE_T; break;
    case 'u': subPreferredType = TYPE_U; break;
    case 'o': subPreferredType = TYPE_O; break;

    case 'S': topPreferredRotation = ROTATION_0; break;
    case 'D': topPreferredRotation = ROTATION_90; break;
    case 'F': topPreferredRotation = ROTATION_180; break;
    case 'G': topPreferredRotation = ROTATION_270; break;

    case 's': subPreferredRotation = ROTATION_0; break;
    case 'd': subPreferredRotation = ROTATION_90; break;
    case 'f': subPreferredRotation = ROTATION_180; break;
    case 'g': subPreferredRotation = ROTATION_270; break;

    case 'Q': topPreferredTranslation = TRANSLATION_TOP; break;
    case 'A': topPreferredTranslation = TRANSLATION_MIDDLE; break;
    case 'Z': topPreferredTranslation = TRANSLATION_BOTTOM; break;

    case 'q': subPreferredTranslation = TRANSLATION_TOP; break;
    case 'a': subPreferredTranslation = TRANSLATION_MIDDLE; break;
    case 'z': subPreferredTranslation = TRANSLATION_BOTTOM; break;
    
    case '+': subdivisionProbability = constrain(subdivisionProbability+0.05, 0, 1); break;
    case '-': subdivisionProbability = constrain(subdivisionProbability-0.05, 0, 1); break;
  }
  // Add glyph after any keypress.
  currentGlyph = addGlyph();
}

Glyph addGlyph() {
  GlyphBlockFactory topFactory = new GlyphBlockFactory(
    generateSmoothWeights(map(topPreferredType, 0, MAX_TYPE, 0, 1), N_TYPES, false),
    generateSmoothWeights(map(topPreferredRotation, 0, MAX_ROTATION, 0, 1), N_ROTATIONS, true),
    generateSmoothWeights(map(topPreferredTranslation, 0, MAX_TRANSLATION, 0, 1), N_TRANSLATIONS, false)
  );

  GlyphBlockFactory subFactory = new GlyphBlockFactory(
    generateSmoothWeights(map(subPreferredType, 0, MAX_TYPE, 0, 1), N_TYPES, false),
    generateSmoothWeights(map(subPreferredRotation, 0, MAX_ROTATION, 0, 1), N_ROTATIONS, true),
    generateSmoothWeights(map(subPreferredTranslation, 0, MAX_TRANSLATION, 0, 1), N_TRANSLATIONS, false)
  );

  // Create glyph.
  return new Glyph(topFactory, subFactory);
}
