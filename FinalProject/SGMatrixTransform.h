#pragma once
#include "SGGroup.h"

class SGMatrixTransform : public SGGroup {
protected:
	Matrix4 M; // Transformation matrix
public:
	SGMatrixTransform();
	SGMatrixTransform(Matrix4 m);
	~SGMatrixTransform();

	void draw(Matrix4);

	void setM(Matrix4 M) { this->M = M; }
	Matrix4 getM() { return M; }
};

