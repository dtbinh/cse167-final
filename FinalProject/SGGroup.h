#pragma once
#include "SGNode.h"
#include <list>

class SGGroup : public SGNode {
protected:
	std::list<SGNode*> *children;

public:
	SGGroup(char* n = "");
	SGGroup(const SGGroup&);
	virtual ~SGGroup();

	void addChild(SGNode*); // Add child
	bool removeChild(SGNode*); // Remove child
	bool removeChild(char* nodeName); // Remove child by name
	bool removeChild(int i); // Remove child by index

	void setParent(SGNode& p) { *this->parent = p; }

	void draw(Matrix4 C);
};

