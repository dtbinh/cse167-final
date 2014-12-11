#pragma once
#include "SGGeode.h"
#include <vector>

class BezierCurve : public SGGeode {
protected:
	Vector3* _p0;
	Vector3* _p1;
	Vector3* _p2;
	Vector3* _p3;

	Matrix4* bezMatrix;

	GLfloat cp[4][3];

	std::vector<Vector3*> controlPoints;

public:
	BezierCurve(Vector3* p0, Vector3* p1, Vector3* p2, Vector3* p3);
	virtual ~BezierCurve();

	std::vector<Vector3*>& points();
	const std::vector<Vector3*>& points() const;

	void render();
};

