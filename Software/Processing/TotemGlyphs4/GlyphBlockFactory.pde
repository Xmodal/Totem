class GlyphBlockFactory {

  float[] typeWeights;
  float[] rotationWeights;
  float[] translationWeights;
  
  GlyphBlockFactory(float[] typeWeights, float[] rotationWeights, float[] translationWeights) {
    this.typeWeights = typeWeights;
    this.rotationWeights = rotationWeights;
    this.translationWeights = translationWeights;
  }
  
  GlyphBlock create() {
    // Randomly choose type, rotation and translation.
    int type        = weightedRandom(typeWeights);
    int rotation    = weightedRandom(rotationWeights);
    int translation = weightedRandom(translationWeights);
    // Create block.
    return new GlyphBlock(type, rotation, translation);
  }
}
