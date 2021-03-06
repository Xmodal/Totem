#include "GlyphBlock.h"

GlyphBlock::GlyphBlock() {
	GlyphBlock(TYPE_VOID, ROTATION_0, TRANSLATION_MIDDLE);
}

GlyphBlock::GlyphBlock(GlyphType type, GlyphRotation rotation, GlyphTranslation translation, float activation_)
	: activation(activation_)
{
	// Get base block.
	matrix = createBase(type);

	// Translate.
	matrix = translate(matrix, translation);

	// Rotate.
	for (int r = 0; r < rotation; r++)
		matrix = rotate90(matrix);
}

GlyphBlock::GlyphBlock(bool left, bool top, bool right, bool bottom)
 	: activation(0) {
	matrix = Matrix3x3(
		false, top, false,
		left, true, right,
		false, bottom, false
	);
}

Matrix3x3 GlyphBlock::createBase(GlyphType type) const
{
	switch (type)
	{
		// I case
		case TYPE_I:
			// . * .
			// . * .
			// . * .
			return Matrix3x3(
				X, O, X,
				X, O, X,
				X, O, X);
		// F case
		case TYPE_F:
			// . * *
			// . * .
			// . * .
			return Matrix3x3(
				X, O, O,
				X, O, X,
				X, O, X);
		// Z case
		case TYPE_Z:
			// * * .
			// . * .
			// . * *
			return Matrix3x3(
				O, O, X,
				X, O, X,
				X, O, O);
		// T case
		case TYPE_T:
			// . * .
			// . * .
			// * * *
			return Matrix3x3(
				X, O, X,
				X, O, X,
				O, O, O);
		// L case
		case TYPE_L:
			// * . .
			// * . .
			// * * *
			return Matrix3x3(
				O, X, X,
				O, X, X,
				O, O, O);
		// Y case
		case TYPE_Y:
			// * . *
			// * * *
			// . * .
			return Matrix3x3(
				O, X, O,
				O, O, O,
				X, O, X);
		// H case
		case TYPE_H:
			// * . *
			// * * *
			// * . *
			return Matrix3x3(
				O, X, O,
				O, O, O,
				O, X, O);
		// J case
		case TYPE_J:
			// . . *
			// * . *
			// * * *
			return Matrix3x3(
				X, X, O,
				O, X, O,
				O, O, O);
		// U case
		case TYPE_U:
			// * . *
			// * . *
			// * * *
			return Matrix3x3(
				O, X, O,
				O, X, O,
				O, O, O);
		// O case
		case TYPE_O:
			// * * *
			// * . *
			// * * *
			return Matrix3x3(
				O, O, O,
				O, X, O,
				O, O, O);
		// X case
		case TYPE_X:
			// * * *
			// * * *
			// * * *
			return Matrix3x3(
				O, O, O,
			  O, O, O,
			  O, O, O);

    // VOID (default)
		case TYPE_VOID:
		default:
			return Matrix3x3(X, X, X, X, X, X, X, X, X);
	}

}Matrix3x3 GlyphBlock::translate(const Matrix3x3& m, GlyphTranslation translation) const
{
	switch (translation) {
	case TRANSLATION_TOP:
		return Matrix3x3(
			m[1][0], m[1][1], m[1][2],
			m[2][0], m[2][1], m[2][2],
			X, X, X);
	case TRANSLATION_BOTTOM:
		return Matrix3x3(
			X, X, X,
		    m[0][0], m[0][1], m[0][2],
		    m[1][0], m[1][1], m[1][2]);
	default:
		return m;
	}
}

Matrix3x3 GlyphBlock::rotate90(const Matrix3x3& m) const
{
	return Matrix3x3(
	  m[2][0], m[1][0], m[0][0],
	  m[2][1], m[1][1], m[0][1],
	  m[2][2], m[1][2], m[0][2]
	);
}
#include <iostream>
void GlyphBlock::debug() {
	for (int y=0; y<3; y++) {
		for (int x=0; x<3; x++)
			std::cout << matrix[y][x] << " ";
		std::cout << std::endl;
	}
}
