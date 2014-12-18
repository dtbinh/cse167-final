#pragma once
#include <iostream>
using namespace std;

class BoundingBox {
private:
	float center[3];
	float width, height, depth;
	float _minX, _maxX, _minY, _maxY, _minZ, _maxZ;
public:
	BoundingBox();
	BoundingBox(float *c, float w, float h, float d);
	BoundingBox(float xc, float yc, float zc, float w, float h, float d);
	~BoundingBox();

	void set(float *c, float w, float h, float d);
	void set(float cx, float cy, float cz, float w, float h, float d);

	void setCenter(float *c) { set(c, this->width, this->height, this->depth); }
	void setCenter(float x, float y, float z) { set(x, y, z, this->width, this->height, this->depth); }

	float* getCenter() { return center; }
	float getCenterX() { return center[0]; }
	float getCenterY() { return center[1]; }
	float getCenterZ() { return center[2]; }


	float getWidth() { return width; }
	float getHeight() { return height; }
	float getDepth() { return depth; }

	float minX() { return _minX; }
	float maxX() { return _maxX; }

	float minY() { return _minY; }
	float maxY() { return _maxY; }

	float minZ() { return _minZ; }
	float maxZ() { return _maxZ; }


	bool collidesWith(BoundingBox &other);

	void draw();
};

