#include "BoundingBox.h"
#include <math.h>
#include <GL\glut.h>

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(GLfloat *c, GLfloat w, GLfloat h, GLfloat d) : width(w), height(h), depth(d) {
	center[0] = c[0]; center[1] = c[1]; center[2] = c[2];
	_minX = center[0] - width / 2.0;
	_maxX = center[0] + width / 2.0;
	_minY = center[1] - height / 2.0;
	_maxY = center[1] + height / 2.0;
	_minZ = center[2] - depth / 2.0;
	_maxZ = center[2] + depth / 2.0;
}
BoundingBox::BoundingBox(GLfloat xc, GLfloat yc, GLfloat zc, GLfloat w, GLfloat h, GLfloat d) : width(w), height(h), depth(d) {
	center[0] = xc; center[1] = yc; center[2] = zc;
	_minX = center[0] - width / 2.0;
	_maxX = center[0] + width / 2.0;
	_minY = center[1] - height / 2.0;
	_maxY = center[1] + height / 2.0;
	_minZ = center[2] - depth / 2.0;
	_maxZ = center[2] + depth / 2.0;
}

BoundingBox::~BoundingBox() {
}

void BoundingBox::set(GLfloat *c, GLfloat w, GLfloat h, GLfloat d) {
	center[0] = c[0]; center[1] = c[1]; center[2] = c[2];
	width = w; height = h; depth = d;
	_minX = center[0] - width / 2.0;
	_maxX = center[0] + width / 2.0;
	_minY = center[1] - height / 2.0;
	_maxY = center[1] + height / 2.0;
	_minZ = center[2] - depth / 2.0;
	_maxZ = center[2] + depth / 2.0;

	//printf("Center: (%f, %f, %f)\n", center[0], center[1], center[2]);
	

}

void BoundingBox::set(float cx, float cy, float cz, float w, float h, float d) {
	center[0] = cx;
	center[1] = cy;
	center[2] = cz;
	width = w; height = h; depth = d;
	_minX = center[0] - width / 2.0;
	_maxX = center[0] + width / 2.0;
	_minY = center[1] - height / 2.0;
	_maxY = center[1] + height / 2.0;
	_minZ = center[2] - depth / 2.0;
	_maxZ = center[2] + depth / 2.0;
}

bool BoundingBox::collidesWith(BoundingBox &other) {
	// check if it collides
	if (fabs(this->getCenterX() - other.getCenterX()) > this->getWidth() / 2.0 + other.getWidth() / 2.0) return false;
	if (fabs(this->getCenterY() - other.getCenterY()) > this->getHeight() / 2.0 + other.getHeight() / 2.0) return false;
	if (fabs(this->getCenterZ() - other.getCenterZ()) > this->getDepth() / 2.0 + other.getDepth() / 2.0) return false;

	// if we get here, it does collide
	return true;
}

void BoundingBox::draw() {
	glPushMatrix();

	glColor3f(1.0, 0.0, 0.0);

	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);
	glBegin(GL_QUADS);



	// Front
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(minX(), minY(), maxZ());
	glVertex3f(maxX(), minY(), maxZ());
	glVertex3f(maxX(), maxY(), maxZ());
	glVertex3f(minX(), maxY(), maxZ());

	// Right
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(maxX(), minY(), maxZ());
	glVertex3f(maxX(), minY(), minZ());
	glVertex3f(maxX(), maxY(), minZ());
	glVertex3f(maxX(), maxY(), maxZ());

	// Back
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(maxX(), minY(), minZ());
	glVertex3f(minX(), minY(), minZ());
	glVertex3f(minX(), maxY(), minZ());
	glVertex3f(maxX(), maxY(), minZ());

	// Left
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(minX(), minY(), minZ());
	glVertex3f(minX(), minY(), maxZ());
	glVertex3f(minX(), maxY(), maxZ());
	glVertex3f(minX(), maxY(), minZ());

	// Top
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(minX(), maxY(), maxZ());
	glVertex3f(maxX(), maxY(), maxZ());
	glVertex3f(maxX(), maxY(), minZ());
	glVertex3f(minX(), maxY(), minZ());

	// Bottom
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(maxX(), minY(), maxZ());
	glVertex3f(minX(), minY(), maxZ());
	glVertex3f(minX(), minY(), minZ());
	glVertex3f(maxX(), minY(), minZ());

	glEnd();
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}