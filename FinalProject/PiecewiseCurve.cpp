#include "PiecewiseCurve.h"


PiecewiseCurve::PiecewiseCurve(int numCurves, GLfloat (*points)[4][3]) {
	this->numCurves = numCurves;
	numPoints = numCurves * 3 + 1;
	curves = new BezierCurve*[numCurves];
	for (int i = 0; i < numCurves; ++i) {
		curves[i] = new BezierCurve(points[i]);
		//curves[i].set(points[i]);
	}
}


PiecewiseCurve::~PiecewiseCurve() {
	for (int i = 0; i < numCurves; ++i) {
		if (curves[i]) delete curves[i];
	}
	delete[] curves;
}

void PiecewiseCurve::render() {
	for (int i = 0; i < numCurves; ++i) {
		curves[i]->render();
	}
}

int PiecewiseCurve::getNumIndices() {
	int sum = 0;
	for (int i = 0; i < numCurves; ++i) {
		sum += curves[i]->getNumIndices();
	}
	return sum;
}

BezierCurve* PiecewiseCurve::getCurve(int n) {
	if (n >= 0 && n < numCurves)
		return curves[n];
	return NULL;
}