#include "SGGroup.h"

SGGroup::SGGroup(char* n) {
	this->name = n;
	children = new std::list<SGNode*>();
}

SGGroup::SGGroup(const SGGroup& other) {

}

SGGroup::~SGGroup() {
	for (std::list<SGNode*>::iterator it = children->begin(); it != children->end(); it++) {
		delete *it;
	}
	delete children;
}

void SGGroup::addChild(SGNode* child) {
	children->push_back(child);
}

bool SGGroup::removeChild(SGNode* child) {
	for (std::list<SGNode*>::iterator it = children->begin(); it != children->end(); it++) {
		if (*it == child) {
			children->erase(it);
			return true;
		}
	}
	return false;
}

bool SGGroup::removeChild(char* childName) {
	for (SGNode* child : *children) {
		if (strcmp(childName, child->getName())) {
			children->remove(child);
			return true;
		}
	}
	return false;
}

bool SGGroup::removeChild(int index) {
	std::list<SGNode*>::iterator it = children->begin();
	std::advance(it, index);
	children->erase(it);
	return true;
}

void SGGroup::draw(Matrix4 C) {
	for (SGNode* child : *children) {
		child->draw(C);
		// draw(C);
	}
}
