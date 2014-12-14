#include "BezierCurve.h"
#include "GL\glut.h"

BezierCurve::BezierCurve(Vector3 *p0, Vector3 *p1, Vector3 *p2, Vector3 *p3) {

	cp[0][0] = p0->x();
	cp[0][1] = p0->y();
	cp[0][2] = p0->z();
	cp[0][3] = 1.0f;

	cp[1][0] = p1->x();
	cp[1][1] = p1->y();
	cp[1][2] = p1->z();
	cp[1][3] = 1.0f;
	
	cp[2][0] = p2->x();
	cp[2][1] = p2->y();
	cp[2][2] = p2->z();
	cp[2][3] = 1.0f;

	cp[3][0] = p3->x();
	cp[3][1] = p3->y();
	cp[3][2] = p3->z();
	cp[3][3] = 1.0f;
	
	createMatrix();
}

BezierCurve::BezierCurve(GLfloat points[4][3]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			cp[i][j] = points[i][j];
		}
	}
	cp[0][3] = 1.0f;
	cp[1][3] = 1.0f;
	cp[2][3] = 1.0f;
	cp[3][3] = 1.0f;

	createMatrix();

	// calc indices & tangents
	for (int i = 0; i < bc_detail; ++i) {
		float t = (float)i / (bc_detail - 1);
		indices[i] = calcPoint(t);
		tangents[i] = calcTangent(indices[i], t + 0.000001f);
	}
}

void BezierCurve::set(GLfloat points[4][3]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			cp[i][j] = points[i][j];
		}
	}
	cp[0][3] = 1.0f;
	cp[1][3] = 1.0f;
	cp[2][3] = 1.0f;
	cp[3][3] = 1.0f;

	createMatrix();

	// calc indices & tangents
	for (int i = 0; i < bc_detail; ++i) {
		float t = (float)i / (bc_detail - 1);
		indices[i] = calcPoint(t);
		tangents[i] = calcTangent(indices[i], t + 0.000001f);
	}
}

BezierCurve::~BezierCurve() {
	delete[] cp;
	for (int i = 0; i < bc_detail; ++i) {
		delete[] indices[i];
		delete[] tangents[i];
	}
	delete[] indices;
	delete[] tangents;
	delete bezMatrix;
}

GLfloat* BezierCurve::calcPoint(float t) {
	GLfloat T[4] = { t*t*t, t*t, t, 1.0 };
	GLfloat *res = new GLfloat[4];

	GLfloat c;
	for (int i = 0; i < 4; ++i) {
		c = 0.0f;
		for (int j = 0; j < 4; ++j) {
			c += bezMatrix->get(i, j) * T[j];
		}
		res[i] = c;
	}
	return res;
}

GLfloat* BezierCurve::calcTangent(GLfloat *point, float t2) {
	// second point on curve (very close to original)
	GLfloat* temp = calcPoint(t2);
	
	// calc tangent at point
	GLfloat *tan = new GLfloat[3];
	for (int i = 0; i < 3; ++i) {
		tan[i] = temp[i] - point[i];
	}

	// normalize tangent
	float length = sqrtf(tan[0] * tan[0] + tan[1] * tan[1] + tan[2] * tan[2]);
	for (int i = 0; i < 3; ++i) {
		tan[i] /= length;
	}

	// clean up
	delete[] temp;

	return tan;
}

void BezierCurve::render() {
	
	// Curve (OpenGL)
	/*glColor3f(1.0, 1.0, 1.0);
	glMap1f(GL_MAP1_VERTEX_3, 0.0f, 1.0f, 3, 4, &cp[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glLineWidth(5.0f);
	glBegin(GL_LINE_STRIP);
	
	for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
		glEvalCoord1f((GLfloat)t);
	}
	glEnd();*/

	// Curve (manual)
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(5.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < bc_detail; ++i) {
		glVertex3fv(indices[i]);
	}
	glEnd();

	// Tangents
	/*glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < bc_detail; ++i) {
		GLfloat t[3];
		for (int j = 0; j < 3; ++j) {
			t[j] = tangents[i][j] + indices[i][j];
		}
		
		glVertex3fv(t);
		glVertex3fv(indices[i]);
	}
	glEnd();*/

	// Control Points
	/*glPointSize(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		for (int i = 0; i < 4; ++i) {
			glVertex3fv(&cp[i][0]);
		}
	glEnd();*/

	// Lines
	/*glColor3f(0.0, 0.5, 1.0);
	glLineWidth(1.0f);
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 4; ++i) {
			glVertex3fv(&cp[i][0]);
		}
	glEnd();*/

}

void BezierCurve::createMatrix() {
	if (bezMatrix) delete bezMatrix;

	Matrix4 G(cp[0][0], cp[1][0], cp[2][0], cp[3][0],
		cp[0][1], cp[1][1], cp[2][1], cp[3][1],
		cp[0][2], cp[1][2], cp[2][2], cp[3][2],
		0.0f, 0.0f, 0.0f, 0.0f);

	Matrix4 B(-1.0f, 3.0f, -3.0f, 1.0f,
		3.0f, -6.0f, 3.0f, 0.0f,
		-3.0f, 3.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f);

	bezMatrix = new Matrix4();
	bezMatrix->multiply(G, B);	// maybe order should be switched????
}