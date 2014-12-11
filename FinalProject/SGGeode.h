#pragma once
#include "SGNode.h"
#include <GL\glut.h>

class SGGeode : public SGNode {
public:
	SGGeode(char *name = "");
	virtual ~SGGeode();

	void draw(Matrix4);

	virtual void render() = 0;

};

