#pragma once

class BoundingBox {
private:
	float center[3];
	float width, height, depth;
	float minX, maxX, minY, maxY, minZ, maxZ;
public:
	BoundingBox();
	BoundingBox(float *c, float w, float h, float d);
	BoundingBox(float xc, float yc, float zc, float w, float h, float d);
	~BoundingBox();

	void set(float *c, float w, float h, float d);
	void setCenter(float *c) { for (int i = 0; i < 3; ++i) center[i] = c[i]; }
	void setCenter(float x, float y, float z) { center[0] = x; center[1] = y; center[2] = z; }

	float* getCenter() { return center; }
	float getCenterX() { return center[0]; }
	float getCenterY() { return center[1]; }
	float getCenterZ() { return center[2]; }


	float getWidth() { return width; }
	float getHeight() { return height; }
	float getDepth() { return depth; }


	bool collidesWith(BoundingBox &other);

	void draw();
};

