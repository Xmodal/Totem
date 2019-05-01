#pragma once

#ifndef GLYPH_INC_
#define GLYPH_INC_

#include <vector>
#include <array>
#include "GlyphBlock.h"
#include "defs.h"

#define N_BLOCKS 3
#define BLOCK_SIDE 3

class Glyph
{
public:
	Glyph() {}

	// Creates a new glyph by using the given generative parameters.
	Glyph(float* typeWeights, float* rotationWeights, float* translationWeights);

	// Returns the number of rows.
	int nRows() const {
		return matrix.size();
	}

	// Returns the value of the pixel at row i and column j.
	bool get(int i, int j) const {
		return matrix[i][j];
	}

	static int weightedRandom(const float* weights, int nWeights);
	static void generateSmoothWeights(float* weights, float proportion, int nWeights, bool wrapAround);

	// The blocks.
	GlyphBlock blocks[N_BLOCKS];

	// The matrix of on/off pixels representing the glyph.
	std::vector<std::array<bool, LED_MATRIX_WIDTH> > matrix;
};

#endif