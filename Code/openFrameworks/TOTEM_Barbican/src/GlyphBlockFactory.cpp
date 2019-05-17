#include "GlyphBlockFactory.h"

#include <algorithm>

GlyphBlockFactory::GlyphBlockFactory(float* typeWeights_, float* rotationWeights_, float* translationWeights_) {
	// Deep copy arrays.
	std::copy(typeWeights_, typeWeights_ + N_TYPES, typeWeights);
	std::copy(rotationWeights_, rotationWeights_ + N_ROTATIONS, rotationWeights);
	std::copy(translationWeights_, translationWeights_ + N_TRANSLATIONS, translationWeights);
}

GlyphBlock GlyphBlockFactory::create() const {
	// Randomly choose type, rotation and translation.
	GlyphType type = (GlyphType)weightedRandom(typeWeights, N_TYPES);
	GlyphRotation rotation = (GlyphRotation)weightedRandom(rotationWeights, N_ROTATIONS);
	GlyphTranslation translation = (GlyphTranslation)weightedRandom(translationWeights, N_TRANSLATIONS);
	// Create block.
	return GlyphBlock(type, rotation, translation, random01());
}

int GlyphBlockFactory::weightedRandom(const float* weights, int nWeights) {
	// Sum the weights.
	float sum = 0;
	for (int i = 0; i < nWeights; i++)
		sum += weights[i];
	// Pick random value.
	float rnd = random01() * sum;
	// Find index.
	for (int i = 0; i < nWeights; i++)
	{
		rnd -= weights[i];
		if (rnd <= 0)
			return i;
	}
	return (nWeights - 1);
}

void GlyphBlockFactory::generateSmoothWeights(float* weights, float proportion, int nWeights, bool wrapAround,
																							float peakProbability, float peakNeighborsProbability, float defaultProbability)
{
	// Determine n. neighbors and default weights.
	int nNeighbors = (nWeights >= 3 ? 2 : nWeights-1);
	int nDefault   = nWeights - nNeighbors - 1;
	if (nDefault < 0)
		nDefault = 0;
	else {
		defaultProbability /= nDefault;
		// Just set everything to default at first.
		for (int i=0; i<nWeights; i++)
			weights[i] = defaultProbability;
	}

	// Split neighbors probability.
	peakNeighborsProbability /= nNeighbors;

	// Set max weight.
	int maxIndex = int(proportion * nWeights);
    if (maxIndex < 0)
        maxIndex = 0;
    if (maxIndex >= nWeights)
        maxIndex = nWeights-1;
	weights[maxIndex] = peakProbability;
	if (wrapAround)
	{
		weights[(maxIndex - 1 + nWeights) % nWeights] = peakNeighborsProbability;
		weights[(maxIndex + 1) % nWeights] = peakNeighborsProbability;
	}
	else
	{
		if (maxIndex > 0)
			weights[maxIndex - 1] = peakNeighborsProbability;
		if (maxIndex < nWeights - 1)
			weights[maxIndex + 1] = peakNeighborsProbability;
	}
}

float GlyphBlockFactory::random01() {
	return float(rand()) / RAND_MAX;
}
