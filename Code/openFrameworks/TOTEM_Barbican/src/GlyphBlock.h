#pragma once

#ifndef GLYPH_BLOCK_
#define GLYPH_BLOCK_

#include "Matrix3x3.h"
#include "DefsLedMatrix.h"

class GlyphBlock
{
public:
	GlyphBlock();
	GlyphBlock(GlyphType type, GlyphRotation rotation, GlyphTranslation translation, float activation=0);
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

	// void setActivation(float activation_) {
	// 	activation = activation_;
	// }
	float getActivation() const { return activation; }
	bool isActivated(float activationThreshold) { return activation > activationThreshold; }
	float getPresence(float activationThreshold) {
		if (activation >= activationThreshold)
			return 1;
		else {
			float diff = (activationThreshold - activation) / (1 - (activation + 0.00001));
			diff *= diff;
			return diff;
		}
	}


	void debug();

	Matrix3x3 matrix;

	// A value in [0, 1] that tells the likelihood of the glyph to "activate".
	// (only used for sub-blocks).
	float activation;
};

#endif
