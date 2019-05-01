#pragma once

#ifndef MATRIX_3x3_
#define MATRIX_3x3_

#define O true
#define X false

class Matrix3x3 {
public:
	bool matrix[9];

	Matrix3x3();

	Matrix3x3(bool m00, bool m01, bool m02,
		bool m10, bool m11, bool m12,
		bool m20, bool m21, bool m22);

	void set(int i, int j, bool value) {
		matrix[i * 3 + j] = value;
	}

	bool get(int i, int j) const {
		return matrix[i * 3 + j];
	}

	void setXY(int x, int y, bool value) {
		set(y, x, value);
	}

	bool getXY(int x, int y) const {
		return get(y, x);
	}

	const bool* operator[] (int i) const { return &matrix[i * 3]; }

};

#endif