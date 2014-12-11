#include "SGMatrixTransform.h"


SGMatrixTransform::SGMatrixTransform() {
	M.identity();
}

SGMatrixTransform::SGMatrixTransform(Matrix4 m) {
	M = m;
}

SGMatrixTransform::~SGMatrixTransform() {
}

void SGMatrixTransform::draw(Matrix4 C) {
	Matrix4 tm = C * M;

	for (SGNode* child : *children) {
		child->draw(tm);
	}
}
