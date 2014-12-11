#include "Vector4.h"
#include <math.h>

Vector4::Vector4() {
	_x = _y = _z = _w = 0.0f;
}

Vector4::Vector4(float x, float y, float z, float w) : _x(x), _y(y), _z(z), _w(w) {}

Vector4::Vector4(const Vector4 &v) {
	_x = v.x();
	_y = v.y();
	_z = v.z();
	_w = v.w();
}
Vector4::~Vector4() {
}

Vector4 Vector4::operator+(Vector4 &v) {
	return Vector4(_x + v.x(), _y + v.y(), _z + v.z(), _w + v.w());
}

Vector4 Vector4::operator-(Vector4 &v) {
	return Vector4(_x - v.x(), _y - v.y(), _z - v.z(), _w - v.w());
}

Vector4& Vector4::operator=(const Vector4 &a) {
	_x = a.x();
	_y = a.y();
	_z = a.z();
	_w = a.w();
	return *this;
}

float Vector4::operator[](const int& i) const {
	switch (i) {
	case 0: return _x;
	case 1: return _y;
	case 2: return _z;
	case 3: return _w;
	default: return 0.0f;
	}
}

void Vector4::add(Vector4& a, Vector4& b) {
	_x = a.x() + b.x();
	_y = a.y() + b.y();
	_z = a.z() + b.z();
	_w = a.w() + b.w();
}

void Vector4::sub(Vector4& a, Vector4& b) {
	_x = a.x() - b.x();
	_y = a.y() - b.y();
	_z = a.z() - b.z();
	_w = a.w() - b.w();
}

void Vector4::dehomogenize() {
	if (_w != 0.0) {
		_x /= _w;
		_y /= _w;
		_z /= _w;
		_w = 1.0;
	}
}

void Vector4::set(int i, float n) {
	switch (i) {
	case 0: _x = n; break;
	case 1: _y = n; break;
	case 2: _z = n; break;
	case 3: _w = n; break;
	default:		break;
	}
}

void Vector4::setX(float x) {
	_x = x;
}
float Vector4::x() const {
	return _x;
}

void Vector4::setY(float y) {
	_y = y;
}
float Vector4::y() const {
	return _y;
}
void Vector4::setZ(float z) {
	_z = z;
}
float Vector4::z() const {
	return _z;
}
void Vector4::setW(float w) {
	_w = w;
}
float Vector4::w() const {
	return _w;
}

float Vector4::magnitude() {
	return sqrtf(_x * _x + _y * _y + _z * _z);
}

void Vector4::print(std::string comment) {
	printf("%s (%.2f, %.2f, %.2f, %.2f)\n", comment.c_str(), x(), y(), z(), w());

}