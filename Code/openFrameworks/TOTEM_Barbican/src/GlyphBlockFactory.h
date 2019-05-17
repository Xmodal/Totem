#pragma once

#ifndef GLYPH_FACTORY_INC_
#define GLYPH_FACTORY_INC_

#include "GlyphBlock.h"

class GlyphBlockFactory
{
public:
	GlyphBlockFactory(float* typeWeights, float* rotationWeights, float* translationWeights);
	~GlyphBlockFactory() {}

	// Creates a new GlyphBlock chosen randomly according to factory parameters (ie. weights).
	GlyphBlock create() const;

	static int weightedRandom(const float* weights, int nWeights);
	static void generateSmoothWeights(float* weights, float proportion, int nWeights, bool wrapAround,
		                                float peakProbability=0.5, float peakNeighborsProbability=0.3, float defaultProbability=0.2);
	static float random01();

	float typeWeights[N_TYPES];
	float rotationWeights[N_ROTATIONS];
	float translationWeights[N_TRANSLATIONS];

};

#endif
