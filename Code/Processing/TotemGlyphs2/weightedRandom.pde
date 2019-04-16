int weightedRandom(float[] weights) {
  // Sum the weights.
  float sum = 0;
  for (float w : weights)
    sum += w;
  // Pick random value.
  float rnd = random(sum);
  // Find index.
  int i = 0;
  for (float w : weights)
  {
    rnd -= w;
    if (rnd <= 0)
      return i;
    i++;
  }
  return i;
}

float[] generateSmoothWeights(float proportion, int nWeights, boolean wrapAround)
{
  float[] weights = new float[nWeights];
  for (int i=0; i<nWeights; i++)
    weights[i] = 0.1;
  int maxIndex = int(proportion * nWeights);
  weights[maxIndex] = 1.0;
  if (wrapAround)
  {
    weights[(maxIndex - 1 + nWeights) % nWeights] = 0.25;
    weights[(maxIndex + 1) % nWeights] = 0.25;
  }
  else
  {
    if (maxIndex > 0)
      weights[maxIndex - 1] = 0.25;
    if (maxIndex < nWeights-1)
      weights[maxIndex + 1] = 0.25;
  }
  return weights;
}
