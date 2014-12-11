#pragma once

#include <string>

class Vector3 {
private:
	float _x, _y, _z;
public:
	Vector3();
	Vector3(const Vector3&);
	Vector3(float x, float y, float z);
	virtual ~Vector3();

	// Operator overloading
	Vector3 operator+(const Vector3&);
	Vector3 operator-(const Vector3&);
	Vector3& operator=(const Vector3&);
	float operator[](const int&) const;
	Vector3 operator*(const float);

	void add(const Vector3& a, const Vector3& b);
	void sub(const Vector3& a, const Vector3& b);

	float* asArray() { float *a = new float[3]; a[0] = x(); a[1] = y(); a[2] = z(); return a; }

	void set(float x, float y, float z);
	void setX(float x);
	float x() const;
	void setY(float y);
	float y() const;
	void setZ(float z);
	float z() const;

	float get(int i);

	void negate();
	void scale(float s);
	void scale(float s, Vector3& v);

	float dot(const Vector3&) const;
	Vector3 cross(const Vector3&) const ;
	void cross(const Vector3& a, const Vector3& b);

	float magnitude() const;
	void normalize();

	void print(std::string comment = "");

	static float angleBetween(const Vector3& a, const Vector3& b);
};
