#pragma once

#ifndef GLYPH_BLOCK_
#define GLYPH_BLOCK_

#include "Matrix3x3.h"
#include "defs.h"

enum GlyphType {
	TYPE_I,
	TYPE_L,
	TYPE_T,
	TYPE_U,
	TYPE_O,
	TYPE_VOID,
	TYPE_CONNECTION,
	N_TYPES
};

enum GlyphRotation {
	ROTATION_0,
	ROTATION_90,
	ROTATION_180,
	ROTATION_270,
	N_ROTATIONS
};

enum GlyphTranslation {
	TRANSLATION_TOP,
	TRANSLATION_MIDDLE,
	TRANSLATION_BOTTOM,
	N_TRANSLATIONS
};

class GlyphBlock
{
public:
	GlyphBlock() {}
	GlyphBlock(GlyphType type, GlyphRotation rotation, GlyphTranslation translation);
	GlyphBlock(bool left, bool top, bool right, bool bottom);


	Matrix3x3 createBase(GlyphType type) const;
	Matrix3x3 translate(const Matrix3x3& m, GlyphTranslation translation) const;
	Matrix3x3 rotate90(const Matrix3x3& m) const;



	// Returns the value of the pixel at (i, j).
	bool get(int i, int j) const {
		return matrix.get(i, j);
	}

	bool exists(int i, int j) {
		return (i >= 0 && i < BLOCK_SIDE && j >= 0 && j < BLOCK_SIDE);
	}

	bool getIfExists(int i, int j) {
		if (exists(i, j))
			return get(i, j);
		else
			return false;
	}

	bool getIfExists(int i, int j, GlyphBlock prev, GlyphBlock next) {
		if (i < 0)
			return prev.get(2, j);
		else if (i >= 3)
			return next.get(0, j);
		else
			return get(i, j);
	}

	void set(int i, int j, bool value) {
		matrix.set(i, j, value);
	}

	Matrix3x3 matrix;
};

#endif