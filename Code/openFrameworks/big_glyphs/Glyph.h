#pragma once

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
#ifndef GLYPH_INC_
#define GLYPH_INC_

#include <vector>
#include <array>
#include "GlyphBlock.h"
#include "GlyphBlockFactory.h"
#include "defs.h"

#define GLYPH_WIDTH LED_MATRIX_WIDTH
#define GLYPH_HEIGHT LED_MATRIX_HEIGHT_PER_BOX


class Glyph
{
public:
	Glyph() {}

	// Creates a new glyph by using the given generative parameters.
	Glyph(const GlyphBlockFactory& topFactory, const GlyphBlockFactory& subFactory, float subdivisionProbability);

	// Returns the value of the pixel at row i and column j.
	bool get(int x, int y) const {
		return matrix[x][y];
	}

	// The top-level blocks.
	GlyphBlock topBlocks[N_TOP_BLOCKS];

	// The sub-level blocks.
	GlyphBlock blocks[N_TOP_BLOCKS][BLOCK_SIDE][BLOCK_SIDE];

	// The matrix of on/off pixels representing the glyph.
	bool matrix[GLYPH_WIDTH][GLYPH_HEIGHT];
};

#endif