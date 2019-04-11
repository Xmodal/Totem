#pragma once

#ifndef GLYPH_BLOCK_
#define GLYPH_BLOCK_

#include "Matrix3x3.h"

enum GlyphType {
	TYPE_I,
	TYPE_L,
	TYPE_T,
	TYPE_U,
	TYPE_O,
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

	Matrix3x3 createBase(GlyphType type) const;
	Matrix3x3 translate(const Matrix3x3& m, GlyphTranslation translation) const;
	Matrix3x3 rotate90(const Matrix3x3& m) const;

	// Returns the value of the pixel at (i, j).
	bool get(int i, int j) const {
		return matrix.get(i, j);
	}

	void set(int i, int j, bool value) {
		matrix.set(i, j, value);
	}

	Matrix3x3 matrix;
};

#endif