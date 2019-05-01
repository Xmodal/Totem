#pragma once

#ifndef GLYPH_BLOCK_
#define GLYPH_BLOCK_

#include "Matrix3x3.h"
#include "defs.h"

class GlyphBlock
{
public:
	GlyphBlock();
	GlyphBlock(GlyphType type, GlyphRotation rotation, GlyphTranslation translation);
	GlyphBlock(bool left, bool top, bool right, bool bottom);


	Matrix3x3 createBase(GlyphType type) const;
	Matrix3x3 translate(const Matrix3x3& m, GlyphTranslation translation) const;
	Matrix3x3 rotate90(const Matrix3x3& m) const;

	// Returns the value of the pixel at (i, j).
	bool get(int x, int y) const {
		return matrix.getXY(x, y);
	}

	bool exists(int x, int y) {
		return (x >= 0 && x < BLOCK_SIDE && y >= 0 && y < BLOCK_SIDE);
	}

	bool getIfExists(int x, int y) {
		if (exists(x, y))
			return get(x, y);
		else
			return false;
	}

	bool getIfExists(int x, int y, GlyphBlock& prev, GlyphBlock& next) {
		if (y < 0)
			return prev.get(x, 2);
		else if (y >= 3)
			return next.get(x, 0);
		else
			return get(x, y);
	}

	void set(int x, int y, bool value) {
		matrix.setXY(x, y, value);
	}

	Matrix3x3 matrix;
};

#endif