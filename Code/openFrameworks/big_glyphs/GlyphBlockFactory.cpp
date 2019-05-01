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
	return GlyphBlock(type, rotation, translation);
}

int GlyphBlockFactory::weightedRandom(const float* weights, int nWeights) {
	// Sum the weights.
	float sum = 0;
	for (int i = 0; i < nWeights; i++)
		sum += weights[i];
	// Pick random value.
	float rnd = (rand() * sum) / RAND_MAX;
	// Find index.
	for (int i = 0; i < nWeights; i++)
	{
		rnd -= weights[i];
		if (rnd <= 0)
			return i;
	}
	return (nWeights - 1);
}

void GlyphBlockFactory::generateSmoothWeights(float* weights, float proportion, int nWeights, bool wrapAround)
{
	for (int i = 0; i < nWeights; i++)
		weights[i] = 0.1f;
	int maxIndex = int(proportion * nWeights);
	weights[maxIndex] = 1.0f;
	if (wrapAround)
	{
		weights[(maxIndex - 1 + nWeights) % nWeights] = 0.25f;
		weights[(maxIndex + 1) % nWeights] = 0.25f;
	}
	else
	{
		if (maxIndex > 0)
			weights[maxIndex - 1] = 0.25f;
		if (maxIndex < nWeights - 1)
			weights[maxIndex + 1] = 0.25f;
	}
}