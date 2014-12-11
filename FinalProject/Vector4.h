#pragma once
#include <string>

class Vector4 {
private:
	float _x, _y, _z, _w;
public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector4&);
	~Vector4();

	Vector4 operator+(Vector4&);
	Vector4 operator-(Vector4&);
	Vector4& operator=(const Vector4&);
	float operator[](const int&) const;

	void add(Vector4& a, Vector4& b);
	void sub(Vector4& a, Vector4& b);

	void dehomogenize();

	void set(int i, float n);
	void setX(float x);
	float x() const;

	void setY(float y);
	float y() const;

	void setZ(float z);
	float z() const;

	void setW(float w);
	float w() const;

	float magnitude();
	void print(std::string comment = "");
};

