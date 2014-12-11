#include "Matrix4.h"
#include <math.h>

Matrix4::Matrix4() {
	for (int i = 0; i<4; ++i) {
		for (int j = 0; j<4; ++j) {
			//m[i][j] = i == j ? 1.0 : 0.0;
			m[i][j] = 0.0;
		}
	}
}

Matrix4::Matrix4(float m0, float m1, float m2, float m3,
	float m4, float m5, float m6, float m7,
	float m8, float m9, float m10, float m11,
	float m12, float m13, float m14, float m15) {

	m[0][0] = m0;	m[0][1] = m1;	m[0][2] = m2;	m[0][3] = m3;
	m[1][0] = m4;	m[1][1] = m5;	m[1][2] = m6;	m[1][3] = m7;
	m[2][0] = m8;	m[2][1] = m9;	m[2][2] = m10;	m[2][3] = m11;
	m[3][0] = m12;	m[3][1] = m13;	m[3][2] = m14;	m[3][3] = m15;
}

Matrix4::Matrix4(const Matrix4& n) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m[i][j] = n(i, j);
		}
	}
}

Matrix4::~Matrix4() {
}


float* Matrix4::getPointer() {
	return &m[0][0];
}

void Matrix4::identity() {
	for (int i = 0; i<4; ++i) {
		for (int j = 0; j<4; ++j) {
			m[i][j] = i == j ? 1.0f : 0.0f;
		}
	}
}

void Matrix4::multiply(Matrix4& m2) {
	float c;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			c = 0.0f;
			for (int k = 0; k < 4; k++) {
				c += m[i][k] * m2.get(k, j);
			}
			m[i][j] = c;
		}
	}
}

void Matrix4::multiply(Matrix4 &a, Matrix4 &b) {
	float c;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			c = 0.0f;
			for (int k = 0; k < 4; k++) {
				c += a.get(i, k) * b.get(k, j);
			}
			m[i][j] = c;
		}
	}
}

Vector4& Matrix4::multiply(Vector4& v) {
	float c;
	Vector4 *res = new Vector4();

	for (int i = 0; i < 4; i++) {
		c = 0.0f;
		for (int j = 0; j < 4; ++j) {
			c += get(i, j) * v[j];
		}
		res->set(i, c);
	}
	return *res;
}

Matrix4& Matrix4::operator=(const Matrix4& m2) {
	if (this != &m2) {
		for (int i = 0; i<4; ++i) {
			for (int j = 0; j<4; ++j) {
				m[i][j] = m2.m[i][j];
			}
		}
	}
	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& m2) {
	float n[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			n[i][j] = 0.0;
			for (int k = 0; k < 4; k++) {
				n[i][j] += m[i][k] * m2.get(k, j);
			}
		}
	}
	return Matrix4(n[0][0], n[0][1], n[0][2], n[0][3],
		n[1][0], n[1][1], n[1][2], n[1][3],
		n[2][0], n[2][1], n[2][2], n[2][3],
		n[3][0], n[3][1], n[3][2], 1.0f);
}

Vector4 Matrix4::operator*(const Vector4& v) {
	float n[4];
	float c;
	for (int i = 0; i < 4; ++i) {
		c = 0.0f;
		for (int j = 0; j < 4; ++j) {
			c += m[i][j] * v[j];
		}
		n[i] = c;
	}
	return Vector4(n[0], n[1], n[2], n[3]);
}

Matrix4 Matrix4::operator*=(const Matrix4& m2) {
	*this = *this * m2;
	return *this;
}

float Matrix4::operator() (const int i, const int j) const {
	return get(i, j);
}

float Matrix4::get(int i, int j) const {
	return m[i][j];
}

void Matrix4::set(int i, int j, float n) {
	m[i][j] = n;
}

void Matrix4::transpose() {
	float temp;
	for (int i = 0; i<4; ++i) {
		for (int j = 0; j<4; ++j) {
			temp = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = temp;
		}
	}
}
/* Matrix inversion function by Matthew Fisher. Found at:
* https://graphics.stanford.edu/~mdfisher/Code/Engine/Matrix4.cpp.html
*/
Matrix4 Matrix4::inverse() {
	//
	// Inversion by Cramer's rule.  Code taken from an Intel publication
	//
	double Result[4][4];
	double tmp[12]; /* temp array for pairs */
	double src[16]; /* array of transpose source matrix */
	double det; /* determinant */
	/* transpose matrix */
	for (int i = 0; i < 4; i++) {
		src[i + 0] = (*this).get(i, 0);
		src[i + 4] = (*this).get(i, 1);
		src[i + 8] = (*this).get(i, 2);
		src[i + 12] = (*this).get(i, 3);
	}
	/* calculate pairs for first 8 elements (cofactors) */
	tmp[0] = src[10] * src[15];
	tmp[1] = src[11] * src[14];
	tmp[2] = src[9] * src[15];
	tmp[3] = src[11] * src[13];
	tmp[4] = src[9] * src[14];
	tmp[5] = src[10] * src[13];
	tmp[6] = src[8] * src[15];
	tmp[7] = src[11] * src[12];
	tmp[8] = src[8] * src[14];
	tmp[9] = src[10] * src[12];
	tmp[10] = src[8] * src[13];
	tmp[11] = src[9] * src[12];
	/* calculate first 8 elements (cofactors) */
	Result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
	Result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
	Result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
	Result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
	Result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	Result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	Result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	Result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	Result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
	Result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
	Result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
	Result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
	Result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	Result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	Result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	Result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
	/* calculate pairs for second 8 elements (cofactors) */
	tmp[0] = src[2] * src[7];
	tmp[1] = src[3] * src[6];
	tmp[2] = src[1] * src[7];
	tmp[3] = src[3] * src[5];
	tmp[4] = src[1] * src[6];
	tmp[5] = src[2] * src[5];

	tmp[6] = src[0] * src[7];
	tmp[7] = src[3] * src[4];
	tmp[8] = src[0] * src[6];
	tmp[9] = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];
	/* calculate second 8 elements (cofactors) */
	Result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
	Result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
	Result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
	Result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
	Result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
	Result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
	Result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
	Result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
	Result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
	Result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
	Result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
	Result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
	Result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
	Result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
	Result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
	Result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
	/* calculate determinant */
	det = src[0] * Result[0][0] + src[1] * Result[0][1] + src[2] * Result[0][2] + src[3] * Result[0][3];
	/* calculate matrix inverse */
	det = 1.0f / det;

	Matrix4 FloatResult;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			FloatResult.set(i, j, float(Result[i][j] * det));
		}
	}
	return FloatResult;
}

Matrix4 Matrix4::Identity() {
	Matrix4 res;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res.m[i][j] = i == j ? 1.0f : 0.0f;
		}
	}
	return res;
}

Matrix4 Matrix4::Scaling(const Vector3& s) {
	Matrix4 res;
	res.m[0][0] = s.x();
	res.m[1][0] = 0.0f;
	res.m[2][0] = 0.0f;
	res.m[3][0] = 0.0f;

	res.m[0][1] = 0.0f;
	res.m[1][1] = s.y();
	res.m[2][1] = 0.0f;
	res.m[3][1] = 0.0f;

	res.m[0][2] = 0.0f;
	res.m[1][2] = 0.0f;
	res.m[2][2] = s.z();
	res.m[3][2] = 0.0f;

	res.m[0][3] = 0.0f;
	res.m[1][3] = 0.0f;
	res.m[2][3] = 0.0f;
	res.m[3][3] = 1.0f;
	return res;
}

Matrix4 Matrix4::Translation(const Vector3& t) {
	Matrix4 res;
	res.m[0][0] = 1.0f;
	res.m[1][0] = 0.0f;
	res.m[2][0] = 0.0f;
	res.m[3][0] = t.x();

	res.m[0][1] = 0.0f;
	res.m[1][1] = 1.0f;
	res.m[2][1] = 0.0f;
	res.m[3][1] = t.y();

	res.m[0][2] = 0.0f;
	res.m[1][2] = 0.0f;
	res.m[2][2] = 1.0f;
	res.m[3][2] = t.z();

	res.m[0][3] = 0.0f;
	res.m[1][3] = 0.0f;
	res.m[2][3] = 0.0f;
	res.m[3][3] = 1.0f;
	return res;
}

Matrix4 Matrix4::Rotation(const Vector3& _v1, const Vector3& _v2, const Vector3& _v3) {
	Vector3 v1 = _v1;
	v1.normalize();
	Vector3 v2 = _v2;
	v2.normalize();
	Vector3 v3 = _v3;
	v3.normalize();

	Matrix4 res;
	res.m[0][0] = v1.x();
	res.m[1][0] = v1.y();
	res.m[2][0] = v1.z();
	res.m[3][0] = 0.0f;

	res.m[0][1] = v2.x();
	res.m[1][1] = v2.y();
	res.m[2][1] = v2.z();
	res.m[3][1] = 0.0f;

	res.m[0][2] = v3.x();
	res.m[1][2] = v3.y();
	res.m[2][2] = v3.z();
	res.m[3][2] = 0.0f;

	res.m[0][3] = 0.0f;
	res.m[1][3] = 0.0f;
	res.m[2][3] = 0.0f;
	res.m[3][3] = 1.0f;
	return res;
}

Matrix4 Matrix4::Rotation(const Vector3& axis, float angle) {

	float angleRad = angle / 180.0f * M_PI;

	float c = cosf(angleRad);
	float s = sinf(angleRad);
	float t = 1.0f - c;

	Vector3 normAxis = axis;
	normAxis.normalize();

	float ax = normAxis.x();
	float ay = normAxis.y();
	float az = normAxis.z();

	return Matrix4(c + ax*ax*t, ax*ay*t - az*s, ax*az*t + ay*s, 0.0,
		ay*ax*t + az*s, c + ay*ay*t, ay*az*t - ax*s, 0.0,
		az*ax*t + ay*s, az*ay*t + ax*s, c + az*az*t, 0.0,
		0.0, 0.0, 0.0, 1.0);
}

Matrix4 Matrix4::Rotation(const Vector3& axis, float angle, Vector3& center) {
	return Translation(center * -1.0f) * Rotation(axis, angle) * Translation(center);
}

Matrix4 Matrix4::Rotation(float yaw, float pitch, float roll) {
	return RotationY(yaw) * RotationX(pitch) * RotationZ(roll);
}

Matrix4 Matrix4::RotationX(float theta) {
	float angleRad = theta / 180.0f * M_PI;
	float cosT = cosf(angleRad);
	float sinT = sinf(angleRad);
	return Matrix4(1.0, 0.0, 0.0, 0.0,
		0.0, cosT, -sinT, 0.0,
		0.0, sinT, cosT, 0.0,
		0.0, 0.0, 0.0, 1.0);
}

Matrix4 Matrix4::RotationY(float theta) {
	float angleRad = theta / 180.0f * M_PI;
	float cosT = cosf(angleRad);
	float sinT = sinf(angleRad);
	return Matrix4(cosT, 0.0, sinT, 0.0,
		0.0, 1.0, 0.0, 0.0,
		-sinT, 0.0, cosT, 0.0,
		0.0, 0.0, 0.0, 1.0);
}

Matrix4 Matrix4::RotationZ(float theta) {
	float angleRad = theta / 180.0f * M_PI;
	float cosT = cosf(angleRad);
	float sinT = sinf(angleRad);
	return Matrix4(cosT, -sinT, 0.0, 0.0,
		sinT, cosT, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);
}

Matrix4 Matrix4::Camera(const Vector3 &_eye, const Vector3 &_lookAt, const Vector3 &_up) {
	Vector3 e = _eye;
	Vector3 d = _lookAt;
	Vector3 up = _up;

	Vector3 z = e - d;
	z.normalize();

	Vector3 x = up.cross(z);
	x.normalize();

	Vector3 y = z.cross(x);

	return Matrix4(x.get(0), y.get(0), z.get(0), e.get(0),
		x.get(1), y.get(1), z.get(1), e.get(1),
		x.get(2), y.get(2), z.get(2), e.get(2),
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::Orthogonal(float w, float h, float znear, float zfar) {
	return Matrix4(2.0f / w, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / h, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f / (znear - zfar), znear / (znear - zfar),
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::Perspective(float w, float h, float znear, float zfar) {
	return Matrix4(2.0f * znear / w, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f * znear / h, 0.0f, 0.0f,
		0.0f, 0.0f, zfar / (znear - zfar), zfar * znear / (znear - zfar),
		0.0f, 0.0f, -1.0f, 0.0f);
}

Matrix4 Matrix4::PerspectiveFOV(float fov, float aspect, float znear, float zfar) {
	float w = 1.0f / tanf(fov / 2.0f);
	float h = aspect / tanf(fov / 2.0f);

	return Matrix4(w, 0.0f, 0.0f, 0.0f,
		0.0f, h, 0.0f, 0.0f,
		0.0f, 0.0f, zfar / (znear - zfar), zfar * znear / (znear - zfar),
		0.0f, 0.0f, -1.0f, 0.0f);
}

Matrix4 Matrix4::Face(const Vector3& v0, const Vector3& v1) {
	// Rotate about the cross product of the two vectors by the angle between the two vectors
	Vector3 axis = v0.cross(v1);
	float angle = Vector3::angleBetween(v0, v1); // in degrees
	if (angle == 0.0f) return Identity();
	return Rotation(axis, angle);
}

Matrix4 Matrix4::Viewport(float w, float h) {
	return Scaling(Vector3(w * 0.5f, -h *0.5f, 1.0f)) * Translation(Vector3(w*0.5f, h*0.5f, 0.0f));
}

void Matrix4::print(std::string comment) {
	std::cout << comment << "\n";
	for (int i = 0; i < 4; i++) {
		std::cout << "[ ";
		for (int j = 0; j < 4; j++) {
			if (j < 3) printf("%.4f,\t", m[i][j]);
			else	   printf("%.4f ]\n", m[i][j]);
		}
	}
	std::cout << "\n";
}