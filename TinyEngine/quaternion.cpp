#include "quaternion.h"
#include "vector3.h"
#include <cmath>

using namespace mgd;

Quaternion::Quaternion() {
	im = Vector3(0, 0, 0);
	re = 0;
}

Quaternion::Quaternion(Vector3 _im, float _re) {
	im = _im;
	re = _re;
}

void Quaternion::conjugate() {
	im = -im;
}

Quaternion Quaternion::conjugated() const {
	return Quaternion(-im, re);
}

Quaternion Quaternion::operator -() const {
	return Quaternion(-im, -re);
}

Quaternion Quaternion::fromVector3(Vector3 v) {
	return Quaternion(v, 0);
}

Quaternion Quaternion::fromAngleAxis(float deg, Vector3 axis) {
	float rad = deg * M_PI / 180;
	float s = std::sin(rad / 2);
	float c = std::cos(rad / 2);
	return Quaternion(axis.normalized() * s, c);
}

Quaternion Quaternion::identity() {
	return Quaternion(Vector3(0, 0, 0), 1);
}