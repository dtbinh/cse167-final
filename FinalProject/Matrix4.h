#pragma once
#include <iostream>
#include "Vector3.h"
#include "Vector4.h"

#define M_PI 3.14159265358979323846

class Matrix4 {
private:
	float m[4][4];
public:
	Matrix4();
	Matrix4(float, float, float, float,
		float, float, float, float,
		float, float, float, float,
		float, float, float, float);
	Matrix4(const Matrix4&);
	
	~Matrix4();

	float* getPointer();

	void identity();
	void transpose();
	Matrix4 inverse();

	/* Multiplication function */
	void multiply(Matrix4&);
	void multiply(Matrix4&, Matrix4&);
	Vector4& multiply(Vector4&);

	/* Overloaded operators */
	Matrix4& operator=(const Matrix4&);
	Matrix4 operator*(const Matrix4& m2);
	Vector4 operator*(const Vector4& v);
	Matrix4 operator*=(const Matrix4& m2);
	float operator() (const int i, const int j) const;

	float get(int i, int j) const;
	void set(int i, int j, float n);

	// Transformation matrices
	static Matrix4 Identity();
	static Matrix4 Scaling(const Vector3& s);
	static Matrix4 Scaling(float s) { return Scaling(Vector3(s, s, s)); }
	static Matrix4 Translation(const Vector3& pos);
	static Matrix4 Rotation(const Vector3& axis, float angle, Vector3& center);
	static Matrix4 Rotation(const Vector3& axis, float angle);
	static Matrix4 Rotation(float yaw, float pitch, float roll);
	static Matrix4 Rotation(const Vector3& basis1, const Vector3& basis2, const Vector3& basis3);
	static Matrix4 RotationX(float theta);
	static Matrix4 RotationY(float theta);
	static Matrix4 RotationZ(float theta);
	static Matrix4 Camera(const Vector3 &eye, const Vector3 &lookAt, const Vector3 &up);
	static Matrix4 Orthogonal(float w, float h, float znear, float zfar);
	static Matrix4 Perspective(float w, float h, float znear, float zfar);
	static Matrix4 PerspectiveFOV(float fov, float aspect, float znear, float zfar);
	static Matrix4 Face(const Vector3 &v0, const Vector3 &v1);
	static Matrix4 Viewport(float w, float h);

	void print(std::string comment = ""); // print the matrix (display all 16 matrix components numerically on the screen in a 4x4 array)
};

