#include "Camera.h"


Camera::Camera() {
	// set(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));
	c.identity();
	bs = new BoundingSphere(e.x(), e.y(), e.z(), 4.0);
}

Camera::Camera(Vector3& e, Vector3& d, Vector3& up) {
	bs = new BoundingSphere(e.x(), e.y(), e.z(), 1.0);
	set(e, d, up);
}

Camera::Camera(float ex, float ey, float ez, float dx, float dy, float dz, float ux, float uy, float uz) {
	bs = new BoundingSphere(ex, ey, ez, 1.0);
	set(ex, ey, ez, dx, dy, dz, ux, uy, uz);
}

Camera::~Camera() {
	delete bs;
}

void Camera::set(Vector3& e, Vector3& d, Vector3& up) {
	this->e = e;
	this->d = d;
	this->up = up;

	Vector3 z = e - d;
	z.normalize();

	Vector3 x;
	x.cross(up, z);
	x.normalize();

	Vector3 y;
	y.cross(z, x);

	// create camera matrix
	c = Matrix4(x.get(0), y.get(0), z.get(0), e.get(0),
		x.get(1), y.get(1), z.get(1), e.get(1),
		x.get(2), y.get(2), z.get(2), e.get(2),
		0.0, 0.0, 0.0, 1.0);

	// create inverse camera matrix
	c_inv = c.inverse();

	bs->setCenter(e.x(), e.y(), e.z());
}

void Camera::set(float e0, float e1, float e2, float d0, float d1, float d2, float up0, float up1, float up2) {
	Vector3 e_new = Vector3(e0, e1, e2);
	Vector3 d_new = Vector3(d0, d1, d2);
	Vector3 up_new = Vector3(up0, up1, up2);
	set(e_new, d_new, up_new);
}


GLdouble* Camera::getGLMatrix() {

	GLdouble glm[16];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			glm[(i * 4) + j] = c.get(j, i);
		}
	}
	return &glm[0];
}


void Camera::invert() {
	Vector3 x, y, z;

	// z-axis -> z = (e - d) / |e - d|
	z = e - d;
	z.normalize();

	// x-axis -> x = (up X z) / |up X z|
	x.cross(up, z);
	x.normalize();

	// y-axis -> y = z X x
	y.cross(z, x);

	// create camera matrix
	/*Matrix4 m(x.get(0), y.get(0), z.get(0), e.get(0),
	x.get(1), y.get(1), z.get(1), e.get(1),
	x.get(2), y.get(2), z.get(2), e.get(2),
	0.0, 0.0, 0.0, 1.0);*/
	Matrix4 m(x.get(0), y.get(0), z.get(0), e.get(0),
		x.get(1), y.get(1), z.get(1), e.get(1),
		x.get(2), y.get(2), z.get(2), e.get(2),
		0.0, 0.0, 0.0, 1.0);
	//m.transpose();

	//Matrix4 cinv;
	Matrix4 rinv(m.get(0, 0), m.get(0, 1), m.get(0, 2), 0.0,
		m.get(1, 0), m.get(1, 1), m.get(1, 2), 0.0,
		m.get(2, 0), m.get(2, 1), m.get(2, 2), 0.0,
		0.0, 0.0, 0.0, 1.0);
	rinv.transpose();
	//rinv.print("RINV:");

	Matrix4 tinv(1.0, 0.0, 0.0, -e.get(0),
		0.0, 1.0, 0.0, -e.get(1),
		0.0, 0.0, 1.0, -e.get(2),
		0.0, 0.0, 0.0, 1.0);

	c = rinv * tinv;

}

Matrix4 Camera::cInv() {

	Vector3 x, y, z;

	// z-axis -> z = (e - d) / |e - d|
	z = e - d;
	z.normalize();

	// x-axis -> x = (up X z) / |up X z|
	x.cross(up, z);
	x.normalize();

	// y-axis -> y = z X x
	y.cross(z, x);

	// create camera matrix
	Matrix4 m(x.get(0), y.get(0), z.get(0), e.get(0),
		x.get(1), y.get(1), z.get(1), e.get(1),
		x.get(2), y.get(2), z.get(2), e.get(2),
		0.0, 0.0, 0.0, 1.0);

	return m;

	Matrix4 cinv;
	Matrix4 rinv(m.get(0, 0), m.get(0, 1), m.get(0, 2), 0.0,
		m.get(1, 0), m.get(1, 1), m.get(1, 2), 0.0,
		m.get(2, 0), m.get(2, 1), m.get(2, 2), 0.0,
		0.0, 0.0, 0.0, 1.0);
	rinv.transpose();
	//rinv.print("RINV:");

	Matrix4 tinv(1.0, 0.0, 0.0, -e.get(0),
		0.0, 1.0, 0.0, -e.get(1),
		0.0, 0.0, 1.0, -e.get(2),
		0.0, 0.0, 0.0, 1.0);

	cinv = rinv * tinv;
	//cinv.print("Cinv: ");
	return cinv;
}

void Camera::inverse() {

	// calculate determinant
	double det = c(0, 0)*c(1, 1)*c(2, 2)*c(3, 3) + c(0, 0)*c(1, 2)*c(2, 3)*c(3, 1) + c(0, 0)*c(1, 3)*c(2, 1)*c(3, 2)
		+ c(0, 1)*c(1, 0)*c(2, 3)*c(3, 2) + c(0, 1)*c(1, 2)*c(2, 0)*c(3, 3) + c(0, 1)*c(1, 3)*c(2, 2)*c(3, 0)
		+ c(0, 2)*c(1, 0)*c(2, 1)*c(3, 3) + c(0, 2)*c(1, 1)*c(2, 3)*c(3, 0) + c(0, 2)*c(1, 3)*c(2, 0)*c(3, 1)
		+ c(0, 3)*c(1, 0)*c(2, 2)*c(3, 1) + c(0, 3)*c(1, 1)*c(2, 0)*c(3, 2) + c(0, 3)*c(1, 2)*c(2, 1)*c(3, 0)
		- c(0, 0)*c(1, 1)*c(2, 3)*c(3, 2) - c(0, 0)*c(1, 2)*c(2, 1)*c(3, 3) - c(0, 0)*c(1, 3)*c(2, 2)*c(3, 1)
		- c(0, 1)*c(1, 0)*c(2, 2)*c(3, 3) - c(0, 1)*c(1, 2)*c(2, 3)*c(3, 0) - c(0, 1)*c(1, 3)*c(2, 0)*c(3, 2)
		- c(0, 2)*c(1, 0)*c(2, 3)*c(3, 1) - c(0, 2)*c(1, 1)*c(2, 0)*c(3, 3) - c(0, 2)*c(1, 3)*c(2, 1)*c(3, 0)
		- c(0, 3)*c(1, 0)*c(2, 1)*c(3, 2) - c(0, 3)*c(1, 1)*c(2, 2)*c(3, 0) - c(0, 3)*c(1, 2)*c(2, 0)*c(3, 1);

	// find inverse
	double b[4][4];

	b[0][0] = c(1, 1)*c(2, 2)*c(3, 3) + c(1, 2)*c(2, 3)*c(3, 1) + c(1, 3)*c(2, 1)*c(3, 2) - c(1, 1)*c(2, 3)*c(3, 2) - c(1, 2)*c(2, 1)*c(3, 3) - c(1, 3)*c(2, 2)*c(3, 1);
	b[0][1] = c(0, 1)*c(2, 3)*c(3, 2) + c(0, 2)*c(2, 1)*c(3, 3) + c(0, 3)*c(2, 2)*c(3, 1) - c(0, 1)*c(2, 2)*c(3, 3) - c(0, 2)*c(2, 3)*c(3, 1) - c(0, 3)*c(2, 1)*c(3, 2);
	b[0][2] = c(0, 1)*c(1, 2)*c(3, 3) + c(0, 2)*c(1, 3)*c(3, 1) + c(0, 3)*c(1, 1)*c(3, 2) - c(0, 1)*c(1, 3)*c(3, 2) - c(0, 2)*c(1, 1)*c(3, 3) - c(0, 3)*c(1, 2)*c(3, 1);
	b[0][3] = c(0, 1)*c(1, 3)*c(2, 2) + c(0, 2)*c(1, 1)*c(2, 3) + c(0, 3)*c(1, 2)*c(2, 1) - c(0, 1)*c(1, 2)*c(2, 3) - c(0, 2)*c(1, 3)*c(2, 1) - c(0, 3)*c(1, 1)*c(2, 2);
	b[1][0] = c(1, 0)*c(2, 3)*c(3, 2) + c(1, 2)*c(2, 0)*c(3, 3) + c(1, 3)*c(2, 2)*c(3, 0) - c(1, 0)*c(2, 2)*c(3, 3) - c(1, 2)*c(2, 3)*c(3, 0) - c(1, 3)*c(2, 0)*c(3, 2);
	b[1][1] = c(0, 0)*c(2, 2)*c(3, 3) + c(0, 2)*c(2, 3)*c(3, 0) + c(0, 3)*c(2, 0)*c(3, 2) - c(0, 0)*c(2, 3)*c(3, 2) - c(0, 2)*c(2, 0)*c(3, 3) - c(0, 3)*c(2, 2)*c(3, 0);
	b[1][2] = c(0, 0)*c(1, 3)*c(3, 2) + c(0, 2)*c(1, 0)*c(3, 3) + c(0, 3)*c(1, 2)*c(3, 0) - c(0, 0)*c(1, 2)*c(3, 3) - c(0, 2)*c(1, 3)*c(3, 0) - c(0, 3)*c(1, 0)*c(3, 2);
	b[1][3] = c(0, 0)*c(1, 2)*c(2, 3) + c(0, 2)*c(1, 3)*c(2, 0) + c(0, 3)*c(1, 0)*c(2, 2) - c(0, 0)*c(1, 3)*c(2, 2) - c(0, 2)*c(1, 0)*c(2, 3) - c(0, 3)*c(1, 2)*c(2, 0);
	b[2][0] = c(1, 0)*c(2, 1)*c(3, 3) + c(1, 1)*c(2, 3)*c(3, 0) + c(1, 3)*c(2, 0)*c(3, 1) - c(1, 0)*c(2, 3)*c(3, 1) - c(1, 1)*c(2, 0)*c(3, 3) - c(1, 3)*c(2, 1)*c(3, 0);
	b[2][1] = c(0, 0)*c(2, 3)*c(3, 1) + c(0, 1)*c(2, 0)*c(3, 3) + c(0, 3)*c(2, 1)*c(3, 0) - c(0, 0)*c(2, 1)*c(3, 3) - c(0, 1)*c(2, 3)*c(3, 0) - c(0, 3)*c(2, 0)*c(3, 1);
	b[2][2] = c(0, 0)*c(1, 1)*c(3, 3) + c(0, 1)*c(1, 3)*c(3, 0) + c(0, 3)*c(1, 0)*c(3, 1) - c(0, 0)*c(1, 3)*c(3, 1) - c(0, 1)*c(1, 0)*c(3, 3) - c(0, 3)*c(1, 1)*c(3, 0);
	b[2][3] = c(0, 0)*c(1, 3)*c(2, 1) + c(0, 1)*c(1, 0)*c(2, 3) + c(0, 3)*c(1, 1)*c(2, 0) - c(0, 0)*c(1, 1)*c(2, 3) - c(0, 1)*c(1, 3)*c(2, 0) - c(0, 3)*c(1, 0)*c(2, 1);
	b[3][0] = c(1, 0)*c(2, 2)*c(3, 1) + c(1, 1)*c(2, 0)*c(3, 2) + c(1, 2)*c(2, 1)*c(3, 0) - c(1, 0)*c(2, 1)*c(3, 2) - c(1, 1)*c(2, 2)*c(3, 0) - c(1, 2)*c(2, 0)*c(3, 1);
	b[3][1] = c(0, 0)*c(2, 1)*c(3, 2) + c(0, 1)*c(2, 2)*c(3, 0) + c(0, 2)*c(2, 0)*c(3, 1) - c(0, 0)*c(2, 2)*c(3, 1) - c(0, 1)*c(2, 0)*c(3, 2) - c(0, 2)*c(2, 1)*c(3, 0);
	b[3][2] = c(0, 0)*c(1, 2)*c(3, 1) + c(0, 1)*c(1, 0)*c(3, 2) + c(0, 2)*c(1, 1)*c(3, 0) - c(0, 0)*c(1, 1)*c(3, 2) - c(0, 1)*c(1, 2)*c(3, 0) - c(0, 2)*c(1, 0)*c(3, 1);
	b[3][3] = c(0, 0)*c(1, 1)*c(2, 2) + c(0, 1)*c(1, 2)*c(2, 0) + c(0, 2)*c(1, 0)*c(2, 1) - c(0, 0)*c(1, 2)*c(2, 1) - c(0, 1)*c(1, 0)*c(2, 2) - c(0, 2)*c(1, 1)*c(2, 0);

	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			c.set(i, j, b[i][j] / det);
		}
	}

}

void Camera::translate(double x, double y, double z) {
	Vector3 e_ = Vector3(x, y, z);
	e = e + e_;
	c.set(0, 3, e.x());
	c.set(1, 3, e.y());
	c.set(2, 3, e.z());
	c_inv = c.inverse();
}
