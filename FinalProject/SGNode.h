#pragma once
#include "BoundingBox.h"
#include "Matrix4.h"
#include <math.h>

class SGNode {
protected:
	char* name;
	SGNode* parent;
	BoundingBox *bb;
public:
	SGNode();
	virtual ~SGNode();
	char* getName() { return name; }
	void setName(char* n) { this->name = n; }

	virtual void draw(Matrix4 C) = 0;

	bool operator==(SGNode& n) const { return strcmp(this->name, n.name) == 0; }

	BoundingBox& getBoundingBox() { return *bb; }
};

