#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "BoundingBox.h"

enum collision { NO_COLLISION, FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM };
class BoundingSphere {
private:
	Vector3 center;
	float radius;
	bool visible;
	float _minX, _maxX, _minY, _maxY, _minZ, _maxZ;

public:
	BoundingSphere();
	BoundingSphere(Vector3& center, float radius);
	BoundingSphere(float x, float y, float z, float radius);
	~BoundingSphere();

	void set(Vector3& c, float r);
	void set(float x, float y, float z, float r);

	Vector3& getCenter() { return center; }
	void setCenter(float x, float y, float z) { set(x, y, z, this->radius); }

	float getRadius() { return radius; }
	void setRadius(float r) { set(this->center, r); }

	bool isVisible() { return visible; }
	void setVisible(bool v) { visible = v; }

	bool isInBounds(Vector3& p, Vector3& n);

	void draw(Matrix4 C);

	int collidesWith(BoundingBox&);

	bool collidesWithPlane(Vector3& p, Vector3& n);

	float minX() { return _minX; }
	float maxX() { return _maxX; }

	float minY() { return _minY; }
	float maxY() { return _maxY; }

	float minZ() { return _minZ; }
	float maxZ() { return _maxZ; }
};

