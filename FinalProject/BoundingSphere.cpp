#include "BoundingSphere.h"
#include "GL\glut.h"


BoundingSphere::BoundingSphere() {
	center.set(0.0, 0.0, 0.0);
	radius = 0.0;
	visible = true;
	_minX = center[0] - radius;
	_maxX = center[0] + radius;
	_minY = center[1] - radius;
	_maxY = center[1] + radius;
	_minZ = center[2] - radius;
	_maxZ = center[2] + radius;
}

BoundingSphere::BoundingSphere(Vector3& c, float radius) {
	set(c, radius);
}

BoundingSphere::BoundingSphere(float x, float y, float z, float radius) {
	set(x, y, z, radius);
}


BoundingSphere::~BoundingSphere() {
}

void BoundingSphere::set(Vector3& c, float r) {
	this->center = c;
	radius = r;
	_minX = center[0] - radius;
	_maxX = center[0] + radius;
	_minY = center[1] - radius;
	_maxY = center[1] + radius;
	_minZ = center[2] - radius;
	_maxZ = center[2] + radius;
}

void BoundingSphere::set(float x, float y, float z, float r) {
	center.set(x, y, z);
	radius = r;
	_minX = center[0] - radius;
	_maxX = center[0] + radius;
	_minY = center[1] - radius;
	_maxY = center[1] + radius;
	_minZ = center[2] - radius;
	_maxZ = center[2] + radius;
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
	
	float halfW = other.getWidth() / 2.0;
	float halfH = other.getHeight() / 2.0;
	float halfD = other.getDepth() / 2.0;

	// check if it collides
	if (fabs(this->center.x() - other.getCenterX()) > this->radius + halfW) return NO_COLLISION;
	if (fabs(this->center.y() - other.getCenterY()) > this->radius + halfH) return NO_COLLISION;
	if (fabs(this->center.z() - other.getCenterZ()) > this->radius + halfD) return NO_COLLISION;
	
	// if we get here, it does collide
	// now determine which side it collides with

	Vector3 p;	// point on plane
	Vector3 n;	// normal
	
	// Front
	p = Vector3(other.getCenterX(), other.getCenterY(), other.maxZ());
	n = Vector3(0.0, 0.0, -1.0);
	// check x
	if (this->maxX() > other.minX() && 
		this->minX() < other.maxX()) {
		// check y
		if (this->maxY() > other.minY() &&
			this->minY() < other.maxY()) {
			// check z
			//if (collidesWithPlane(p, n))
			printf("Sphere minZ: %f, maxZ: %f\n", _minZ, _maxZ);
			printf("Cube MinZ: %f, maxZ: %f\n", other.minZ(), other.maxZ());
			if (this->minZ() >= other.maxZ() - 1.1)
				return FRONT;
		}
	}

	// Back
	p = Vector3(other.getCenterX(), other.getCenterY(), other.minZ());
	n = Vector3(0.0, 0.0, 1.0);
	// check x
	if (this->maxX() > other.minX() && this->minX() < other.maxX()) {
		// check y
		if (this->maxY() > other.minY() && this->minY() < other.maxY()) {
			// check z
			//if (collidesWithPlane(p, n))
			if (this->maxZ() <= other.minZ() + 1.1)
				return BACK;
		}
	}

	// Left
	p = Vector3(other.getCenterX() - other.getWidth() / 2.0, other.getCenterY(), other.getCenterZ());
	n = Vector3(-1.0, 0.0, 0.0);
	// check z
	if (this->maxZ() > other.minZ() && this->minZ() < other.maxZ()) {
		// check y
		if (this->maxY() > other.minY() && this->minY() < other.maxY()) {
			// check x
			//if (collidesWithPlane(p, n))
			if (this->maxX() <= other.minX() + 1.1)
				return LEFT;
		}
	}
		

	// Right
	p = Vector3(other.getCenterX() + other.getWidth() / 2.0, other.getCenterY(), other.getCenterZ());
	n = Vector3(1.0, 0.0, 0.0);
	// check z
	if (this->maxZ() > other.minZ() && this->minZ() < other.maxZ()) {
		// check y
		if (this->maxY() > other.minY() && this->minY() < other.maxY()) {
			// check x
			//if (collidesWithPlane(p, n))
			if (this->minX() >= other.maxX() - 1.1)
				return RIGHT;
		}
	}

	// Top
	p = Vector3(other.getCenterX(), other.getCenterY() + other.getHeight() / 2.0, other.getCenterZ());
	n = Vector3(0.0, 1.0, 0.0);
	// check z
	if (this->maxZ() > other.minZ() && this->minZ() < other.maxZ()) {
		// check x
		if (this->maxX() > other.minX() && this->minX() < other.maxX()) {
			// check y
			//if (collidesWithPlane(p, n))
			if (this->minY() >= other.maxY() - 1.1)
				return TOP;
		}
	}
	

	// Bottom
	p = Vector3(other.getCenterX(), other.getCenterY() - other.getHeight() / 2.0, other.getCenterZ());
	n = Vector3(0.0, -1.0, 0.0);
	// check z
	if (this->maxZ() > other.minZ() && this->minZ() < other.maxZ()) {
		// check x
		if (this->maxX() > other.minX() && this->minX() < other.maxX()) {
			// check y
			//if (collidesWithPlane(p, n))
			if (this->maxY() <= other.minY() + 1.1)
				return BOTTOM;
		}
	}

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