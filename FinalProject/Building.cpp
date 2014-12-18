#include "Building.h"


Building::Building(){
}

Building::Building(GLfloat *p, GLfloat w, GLfloat h, GLfloat d) {
	set(p, w, h, d);
}

Building::Building(GLfloat px, GLfloat py, GLfloat pz, GLfloat w, GLfloat h, GLfloat d) {
	set(px, py, pz, w, h, d);
}


Building::~Building(){
	delete bb;
}

void Building::set(GLfloat *p, GLfloat w, GLfloat h, GLfloat d) {
	for (int i = 0; i < 3; ++i) {
		pos[i] = p[i];
	}
	width = w;
	height = h;
	depth = d;

	// set bounding box
	if (bb) delete bb;
	bb = new BoundingBox(p, w, h, d);
}
void Building::set(GLfloat px, GLfloat py, GLfloat pz, GLfloat w, GLfloat h, GLfloat d) {
	pos[0] = px;
	pos[1] = py;
	pos[2] = pz;
	width = w;
	height = h;
	depth = d;

	// set bounding box
	if (bb) delete bb;
	bb = new BoundingBox(px, py, pz, w, h, d);

	printf("Pos: (%f, %f, %f), W: %f, H: %f, D: %f\n", px, py, pz, w, h, d);
}

void Building::render() {
	GLfloat minX = pos[0] - width / 2.0;
	GLfloat maxX = pos[0] + width / 2.0;
	GLfloat minY = pos[1] - height / 2.0;
	GLfloat maxY = pos[1] + height / 2.0;
	GLfloat minZ = pos[2] - depth / 2.0;
	GLfloat maxZ = pos[2] + depth / 2.0;
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.1);
	glBegin(GL_QUADS);


	// Front
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(minX, minY, maxZ);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(minX, maxY, maxZ);

	// Right
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, maxY, maxZ);

	// Back
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(maxX, minY, minZ);
	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, maxY, minZ);
	glVertex3f(maxX, maxY, minZ);

	// Left
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, minY, maxZ);
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, maxY, minZ);

	// Top
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(minX, maxY, minZ);

	// Bottom
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(minX, minY, maxZ);
	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ);


	/*
	glVertex3f((-1.0 * width) + getPosX(), 1.0 + height, (1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), 1.0 + height, (1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), -0.9, (1.0 * width) + getPosZ());
	glVertex3f((-1.0 * width) + getPosX(), -0.9, (1.0 * width) + getPosZ());

	//// Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f((-1.0 * width) + getPosX(), 1.0 + height, (1.0 * width) + getPosZ());
	glVertex3f((-1.0 * width) + getPosX(), 1.0 + height, -(1.0 * width) + getPosZ());
	glVertex3f((-1.0 * width) + getPosX(), -0.9, -(1.0 * width) + getPosZ());
	glVertex3f((-1.0 * width) + getPosX(), -0.9, (1.0 * width) + getPosZ());

	//// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f((1.0 * width) + getPosX(), 1.0 + height, (1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), 1.0 + height, -(1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), -0.9, -(1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), -0.9, (1.0 * width) + getPosZ());

	//// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f((-1.0 * width) + getPosX(), 1.0 + height, -(1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), 1.0 + height, -(1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), -0.9, -(1.0 * width) + getPosZ());
	glVertex3f((-1.0 * width) + getPosX(), -0.9, -(1.0 * width) + getPosZ());

	//// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f((-1.0 * width) + getPosX(), 1.0 + height, (1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), 1.0 + height, (1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), 1.0 + height, (-1.0 * width) + getPosZ());
	glVertex3f((-1.0 * width) + getPosX(), 1.0 + height, (-1.0 * width) + getPosZ());

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f((-1.0 * width) + getPosX(), -0.9, (-1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), -0.9, (-1.0 * width) + getPosZ());
	glVertex3f((1.0 * width) + getPosX(), -0.9, (1.0 * width) + getPosZ());
	glVertex3f((-1.0 * width) + getPosX(), -0.9, (1.0 * width) + getPosZ());
	*/
	glEnd();
	glPopMatrix();

	//bb->draw();
}