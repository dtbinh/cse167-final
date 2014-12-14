#pragma once
#include "SGGeode.h"
#include <vector>

static const int bc_detail = 25; // number of points on each curve

class BezierCurve : public SGGeode {
protected:
	Matrix4 *bezMatrix;

	GLfloat cp[4][4]; // control points

	GLfloat *indices[bc_detail]; // vertices on curve
	GLfloat *tangents[bc_detail]; // tangents on curve

	void createMatrix();

public:
	BezierCurve();
	BezierCurve(Vector3* p0, Vector3* p1, Vector3* p2, Vector3* p3);
	BezierCurve(GLfloat[4][3]);

	void set(GLfloat[4][3]);
	virtual ~BezierCurve();

	GLfloat* calcPoint(float t);
	GLfloat* calcTangent(GLfloat* point, float t2);

	GLfloat** getIndices() { return indices; }

	void render();
};

