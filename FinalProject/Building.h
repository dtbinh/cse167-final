#pragma once
#include "SGGeode.h"

class Building : public SGGeode {
	GLfloat pos[3];
	GLfloat width, height, depth;
public:
	Building();
	Building(GLfloat *p, GLfloat w, GLfloat h, GLfloat d);
	Building(GLfloat px, GLfloat py, GLfloat pz, GLfloat w, GLfloat h, GLfloat d);
	~Building();

	void set(GLfloat *p, GLfloat w, GLfloat h, GLfloat d);
	void set(GLfloat px, GLfloat py, GLfloat pz, GLfloat w, GLfloat h, GLfloat d);

	void setPos(GLfloat *p) { for (int i = 0; i < 3; ++i) pos[i] = p[i]; }
	void setPos(GLfloat x, GLfloat y, GLfloat z) { pos[0] = x; pos[1] = y; pos[2] = z; }
	GLfloat* getPos() { return pos; }
	GLfloat getPosX() { return pos[0]; }
	GLfloat getPosY() { return pos[1]; }
	GLfloat getPosZ() { return pos[2]; }

	void setWidth(GLfloat w) { width = w; }
	GLfloat getWidth() { return width; }

	void setHeight(GLfloat h) { height = h; }
	GLfloat getHeight() { return height; }

	void setDepth(GLfloat d) { depth = d; }
	GLfloat getDepth() { return depth; }

	void render();
};

