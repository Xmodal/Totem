#include "GlyphBlock.h"

GlyphBlock::GlyphBlock(GlyphType type, GlyphRotation rotation, GlyphTranslation translation)
{
	// Get base block.
	matrix = createBase(type);

	// Translate.
	matrix = translate(matrix, translation);

	// Rotate.
	for (int r = 0; r < rotation; r++)
		matrix = rotate90(matrix);
}

Matrix3x3 GlyphBlock::createBase(GlyphType type) const 
{
	switch (type)
	{
		//L case
	case TYPE_L:
		// * . . 
		// * . .
		// * * *
		return Matrix3x3(
			O, X, X,
			O, X, X,
			O, O, O);
	case TYPE_I:
		// * * *
		// . * .
		// * * *
		return Matrix3x3(
			O, O, O,
			X, O, X,
			O, O, O);
	case TYPE_T:
		// * * *
		// . * .
		// . * .
		return Matrix3x3(
			O, O, O,
			X, O, X,
			X, O, X);
	case TYPE_U:
		// * . * 
		// * . *
		// * * *
		return Matrix3x3(
			O, X, O,
			O, X, O,
			O, O, O);

	case TYPE_O:
		// * * *
		// * . *
		// * * *
		return Matrix3x3(
			O, O, O,
			O, X, O,
			O, O, O);

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
