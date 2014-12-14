#pragma once
#include "BezierCurve.h"

using namespace std;

class PiecewiseCurve {
private:
	int numPoints, numCurves;
	BezierCurve **curves;
public:
	PiecewiseCurve(int numCurves, GLfloat (*points)[4][3]);
	~PiecewiseCurve();

	void render();
};

