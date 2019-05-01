#include "Glyph.h"
#include <iostream>

Glyph::Glyph(float* typeWeights, float* rotationWeights, float* translationWeights)
{
	// Choose all blocks.
	for (int i = 0; i < N_BLOCKS; i++)
	{
		// Randomly choose type, rotation and translation
		
		//double check this stuff is it working properly? 
		GlyphType type = (GlyphType) weightedRandom(typeWeights, N_TYPES);
		GlyphRotation rotation = (GlyphRotation)weightedRandom(rotationWeights, N_ROTATIONS);
		GlyphTranslation translation = (GlyphTranslation)weightedRandom(translationWeights, N_TRANSLATIONS);
		blocks[i] = GlyphBlock(type, rotation, translation);

		//Sofian this was here twice? Was it needed? 
		//blocks[i] = GlyphBlock(type, rotation, translation);
	}

	// Create matrix using blocks. Each row is 9 pixels wide. Number
	// of rows vary between 1 and 3.
	matrix.clear();
	for (int r = 0; r < BLOCK_SIDE; r++)
	{
		// Fill up one row.
		std::array<bool, LED_MATRIX_WIDTH> row;
		int c = 0; // column
		bool rowIsEmpty = true;
		for (int b = 0; b < N_BLOCKS; b++)
		{
			for (int j = 0; j < BLOCK_SIDE; j++, c++)
			{
				bool val = blocks[b].get(r, j);
				if (val)
					rowIsEmpty = false;
				row[c] = val;
			}
		}
		// If row is empty don't copy to main matrix.
		if (!rowIsEmpty)
			matrix.push_back(row);
	}
	
}

int Glyph::weightedRandom(const float* weights, int nWeights) {
	// Sum the weights.
	float sum = 0;
	for (int i=0; i<nWeights; i++)
		sum += weights[i];
	// Pick random value.
	float rnd = (rand() * sum) / RAND_MAX;
	std::cout << rnd << std::endl;
	// Find index.
	int i = 0;
	for (int i = 0; i < nWeights; i++)
	{
		rnd -= weights[i];
		if (rnd <= 0)
			return i;
		i++;
	}
	return i;
}

void Glyph::generateSmoothWeights(float* weights, float proportion, int nWeights, bool wrapAround)
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