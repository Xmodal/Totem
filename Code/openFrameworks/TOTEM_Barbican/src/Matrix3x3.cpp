#include "Matrix3x3.h"

Matrix3x3::Matrix3x3() {
	for (int i = 0; i < 9; i++)
		matrix[i] = X;
}

Matrix3x3::Matrix3x3(bool m00, bool m01, bool m02,
	bool m10, bool m11, bool m12,
	bool m20, bool m21, bool m22)
{
	int i = 0;
	matrix[i++] = m00;
	matrix[i++] = m01;
	matrix[i++] = m02;
	matrix[i++] = m10;
	matrix[i++] = m11;
	matrix[i++] = m12;
	matrix[i++] = m20;
	matrix[i++] = m21;
	matrix[i++] = m22;
}