#include "BoundingBox.h"
#include <math.h>
#include <GL\glut.h>

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(GLfloat *c, GLfloat w, GLfloat h, GLfloat d) : width(w), height(h), depth(d) {
	center[0] = c[0]; center[1] = c[1]; center[2] = c[2];
}
BoundingBox::BoundingBox(GLfloat xc, GLfloat yc, GLfloat zc, GLfloat w, GLfloat h, GLfloat d) : width(w), height(h), depth(d) {
	center[0] = xc; center[1] = yc; center[2] = zc;
}

BoundingBox::~BoundingBox() {
}

void BoundingBox::set(GLfloat *c, GLfloat w, GLfloat h, GLfloat d) {
	center[0] = c[0]; center[1] = c[1]; center[2] = c[2];
	width = w; height = h; depth = d;
}

bool BoundingBox::collidesWith(BoundingBox &other) {
	if (fabs(this->getCenterX() - other.getCenterX()) > this->getWidth() / 2.0 + other.getWidth() / 2.0) return false;
	if (fabs(this->getCenterY() - other.getCenterY()) > this->getHeight() / 2.0 + other.getHeight() / 2.0) return false;
	if (fabs(this->getCenterZ() - other.getCenterZ()) > this->getDepth() / 2.0 + other.getDepth() / 2.0) return false;
	return true;
}

void BoundingBox::draw() {
	glPushMatrix();

	glColor3f(1.0, 0.0, 0.0);

	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glLineWidth(1.0f);
	glBegin(GL_QUADS);



	//glNormal3f(0.0, 0.0, 1.0);
	glVertex3f((-1.0 * width) + getCenterX(), 1.0 + height, (1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), 1.0 + height, (1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), -0.9, (1.0 * width) + getCenterZ());
	glVertex3f((-1.0 * width) + getCenterX(), -0.9, (1.0 * width) + getCenterZ());

	//// Draw left side:
	//glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f((-1.0 * width) + getCenterX(), 1.0 + height, (1.0 * width) + getCenterZ());
	glVertex3f((-1.0 * width) + getCenterX(), 1.0 + height, -(1.0 * width) + getCenterZ());
	glVertex3f((-1.0 * width) + getCenterX(), -0.9, -(1.0 * width) + getCenterZ());
	glVertex3f((-1.0 * width) + getCenterX(), -0.9, (1.0 * width) + getCenterZ());

	//// Draw right side:
	//glNormal3f(1.0, 0.0, 0.0);
	glVertex3f((1.0 * width) + getCenterX(), 1.0 + height, (1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), 1.0 + height, -(1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), -0.9, -(1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), -0.9, (1.0 * width) + getCenterZ());

	//// Draw back face:
	//glNormal3f(0.0, 0.0, -1.0);
	glVertex3f((-1.0 * width) + getCenterX(), 1.0 + height, -(1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), 1.0 + height, -(1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), -0.9, -(1.0 * width) + getCenterZ());
	glVertex3f((-1.0 * width) + getCenterX(), -0.9, -(1.0 * width) + getCenterZ());

	//// Draw top side:
	//glNormal3f(0.0, 1.0, 0.0);
	glVertex3f((-1.0 * width) + getCenterX(), 1.0 + height, (1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), 1.0 + height, (1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), 1.0 + height, (-1.0 * width) + getCenterZ());
	glVertex3f((-1.0 * width) + getCenterX(), 1.0 + height, (-1.0 * width) + getCenterZ());

	// Draw bottom side:
	//glNormal3f(0.0, -1.0, 0.0);
	glVertex3f((-1.0 * width) + getCenterX(), -0.9, (-1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), -0.9, (-1.0 * width) + getCenterZ());
	glVertex3f((1.0 * width) + getCenterX(), -0.9, (1.0 * width) + getCenterZ());
	glVertex3f((-1.0 * width) + getCenterX(), -0.9, (1.0 * width) + getCenterZ());

	glEnd();
	glPopMatrix();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}