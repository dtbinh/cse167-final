#include "BoundingSphere.h"
#include "GL\glut.h"


BoundingSphere::BoundingSphere() {
	center.set(0.0, 0.0, 0.0);
	radius = 0.0;
	visible = true;
}

BoundingSphere::BoundingSphere(Vector3& center, float radius) {
	this->center = center;
	this->radius = radius;
	visible = true;
}

BoundingSphere::BoundingSphere(double x, double y, double z, float radius) {
	center.set(x, y, z);
	this->radius = radius;
	visible = true;
}


BoundingSphere::~BoundingSphere() {
}


/* Check to determine if any part of bounding sphere is in bounds.
* ( dist > 0 && |r| < |dist| ) = sphere compeletely inside bounds -> return TRUE
* ( dist > 0 && |r| > |dist| ) = sphere colliding with plane, center inside bounds -> return TRUE
* ( dist < 0 && |r| > |dist| ) = sphere colliding with plane, center outside bounds -> return TRUE
* ( dist < 0 && |r| < |dist| ) = sphere completely outside bounds -> return FALSE
*/
bool BoundingSphere::isInBounds(Vector3& p, Vector3& n) {
	// calculate distance between center of sphere and plane p lies on
	double dist = (center - p).dot(n);

	if (dist >= 0.0 && radius <= fabs(dist)) return true;
	if (dist >= 0.0 && radius >= fabs(dist)) return true;
	if (dist <= 0.0 && radius >= fabs(dist)) return true;
	return false;
}

void BoundingSphere::draw(Matrix4 C) {
	glPushMatrix();
	glLoadIdentity();
	//glMatrixMode(GL_PROJECTION);
	Matrix4 cnew = C;
	//cnew.transpose();
	//glLoadMatrixf(cnew.getPointer());
	glColor3f(1.0, 0.0, 0.0);
	glutWireSphere(radius, 20, 20);
	
	glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
}

int BoundingSphere::collidesWith(BoundingBox& other) {
	// check if it collides
	if (fabs(this->center.x() - other.getCenterX()) > this->radius + other.getWidth() / 2.0) return NO_COLLISION;
	if (fabs(this->center.y() - other.getCenterY()) > this->radius + other.getHeight() / 2.0) return NO_COLLISION;
	if (fabs(this->center.z() - other.getCenterZ()) > this->radius + other.getDepth() / 2.0) return NO_COLLISION;
	
	// if we get here, it does collide
	// now determine which side it collides with

	Vector3 p;	// point on plane
	Vector3 n;	// normal

	// Front
	p = Vector3(other.getCenterX(), other.getCenterY(), other.getCenterZ() - other.getDepth() / 2.0);
	n = Vector3(0.0, 0.0, -1.0);
	if (collidesWithPlane(p, n)) return FRONT;

	// Back
	p = Vector3(other.getCenterX(), other.getCenterY(), other.getCenterZ() + other.getDepth() / 2.0);
	n = Vector3(0.0, 0.0, 1.0);
	if (collidesWithPlane(p, n)) return BACK;

	// Left
	p = Vector3(other.getCenterX() - other.getWidth() / 2.0, other.getCenterY(), other.getCenterZ());
	n = Vector3(-1.0, 0.0, 0.0);
	if (collidesWithPlane(p, n)) return LEFT;

	// Right
	p = Vector3(other.getCenterX() + other.getWidth() / 2.0, other.getCenterY(), other.getCenterZ());
	n = Vector3(1.0, 0.0, 0.0);
	if (collidesWithPlane(p, n)) return RIGHT;

	// Top
	p = Vector3(other.getCenterX(), other.getCenterY() + other.getHeight() / 2.0, other.getCenterZ());
	n = Vector3(0.0, 1.0, 0.0);
	if (collidesWithPlane(p, n)) return TOP;

	// Bottom
	p = Vector3(other.getCenterX(), other.getCenterY() - other.getHeight() / 2.0, other.getCenterZ());
	n = Vector3(0.0, -1.0, 0.0);
	if (collidesWithPlane(p, n)) return BOTTOM;

	return NO_COLLISION;
}

bool BoundingSphere::collidesWithPlane(Vector3& p, Vector3& n) {
	// calculate distance between center of sphere and plane p lies on
	double dist = (center - p).dot(n);

	if (dist >= 0.0 && radius <= fabs(dist)) return false;
	if (dist >= 0.0 && radius >= fabs(dist)) return false;
	if (dist <= 0.0 && radius >= fabs(dist)) return false;
	return true;
}