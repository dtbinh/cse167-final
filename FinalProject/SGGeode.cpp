#include "SGGeode.h"


SGGeode::SGGeode(char *name) {
	this->name = name;
}


SGGeode::~SGGeode() {
}

void SGGeode::draw(Matrix4 C) {
	glMatrixMode(GL_MODELVIEW);
	Matrix4 cnew = C;
	cnew.transpose();
	glLoadMatrixf(cnew.getPointer());
	render();
}