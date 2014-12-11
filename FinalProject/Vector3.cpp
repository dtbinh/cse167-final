#include "Vector3.h"
#include <math.h>


Vector3::Vector3() {
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

Vector3::Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) {}

Vector3::Vector3(const Vector3& a) {
	_x = a.x();
	_y = a.y();
	_z = a.z();
}

Vector3::~Vector3() {

}

Vector3 Vector3::operator+(const Vector3& a) {
	return Vector3(_x + a.x(), _y + a.y(), _z + a.z());
}

Vector3 Vector3::operator-(const Vector3& a) {
	return Vector3(_x - a.x(), _y - a.y(), _z - a.z());
}

Vector3& Vector3::operator=(const Vector3& a) {
	_x = a.x();
	_y = a.y();
	_z = a.z();
	return *this;
}

float Vector3::operator[](const int &i) const {
	switch (i) {
	case 0: return _x;
	case 1: return _y;
	case 2: return _z;
	default: return 0;
	}
}

Vector3 Vector3::operator*(const float m) {
	Vector3 v;
	v._x = _x *m;
	v._y = _y * m;
	v._z = _z * m;
	return v;
}


void Vector3::add(const Vector3& a, const Vector3& b) {
	_x = a.x() + b.x();
	_y = a.y() + b.y();
	_z = a.z() + b.z();
}

void Vector3::sub(const Vector3& a, const Vector3& b) {
	_x = a.x() - b.x();
	_y = a.y() - b.y();
	_z = a.z() - b.z();
}

void Vector3::set(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

void Vector3::setX(float x) {
	_x = x;
}
float Vector3::x() const {
	return _x;
}
void Vector3::setY(float y) {
	_y = y;
}
float Vector3::y() const {
	return _y;
}
void Vector3::setZ(float z) {
	_z = z;
}
float Vector3::z() const {
	return _z;
}

float Vector3::get(int i) {
	switch (i) {
	case 0: return _x;
	case 1: return _y;
	case 2: return _z;
	default: return 0.0f;
	}
}

void Vector3::negate() {
	_x = -_x;
	_y = -_y;
	_z = -_z;
}

void Vector3::scale(float s) {
	_x *= s;
	_y *= s;
	_z *= s;
}
void Vector3::scale(float s, Vector3& v) {
	_x = v.x() * s;
	_y = v.y() * s;
	_z = v.z() * s;
}

float Vector3::dot(const Vector3& a) const {
	return (_x * a.x()) + (_y * a.y()) + (_z * a.z());
}

Vector3 Vector3::cross(const Vector3& b) const {
	Vector3 v;
	v.setX(_y * b.z() - _z * b.y());
	v.setY(_z * b.x() - _x * b.z());
	v.setZ(_x * b.y() - _y * b.x());
	return v;
}

void Vector3::cross(const Vector3& a, const Vector3& b) {
	setX(a.y() * b.z() - a.z() * b.y());
	setY(a.z() * b.x() - a.x() * b.z());
	setZ(a.x() * b.y() - a.y() * b.x());
}

float Vector3::magnitude() const {
	return sqrtf(_x * _x + _y * _y + _z * _z);
}

void Vector3::normalize() {
	float l = magnitude();
	if (l <= 0.0f) return;
	scale(1.0f / l);
}

void Vector3::print(std::string comment) {
	printf("%s (%.4f, %.4f, %.4f)\n", comment.c_str(), _x, _y, _z);
}

float Vector3::angleBetween(const Vector3& a, const Vector3& b) {
	return (acosf(a.dot(b) / (a.magnitude() * b.magnitude()))) * 180.0f / 3.14159265358979323846;
}