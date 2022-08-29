#pragma once
#include "vector3.h"

#define M_PI 3.14159265358979323846

namespace mgd {

	class Vector3;

	class Quaternion {
	public:
		Vector3 im;
		float re;

		Quaternion();

		Quaternion(Vector3 _im, float _re);

		Vector3 apply(Vector3 p) const;

		void conjugate();

		Quaternion conjugated() const;

		Quaternion operator -() const;

		static Quaternion fromVector3(Vector3 v);
		static Quaternion fromAngleAxis(float deg, Vector3 axis);
		static Quaternion identity();
	};

	inline Quaternion operator *(const Quaternion& a, const Quaternion& b) {
		return Quaternion(
			cross(a.im, b.im) + a.im * b.re + a.re * b.im,
			-dot(a.im, b.im) + a.re * b.re
		);
	}

	inline Vector3 Quaternion::apply(Vector3 p) const {
		Quaternion q = fromVector3(p);
		q = (*this) * q * this->conjugated();
		//assert(areEqual(q.re, 0));
		return q.im;
	}

	inline bool areEqual(const Quaternion& a, const Quaternion& b) {
		return areEqual(a.im, b.im) && areEqual(a.re, b.re);
	}

	inline bool areEquivalent(const Quaternion& a, const Quaternion& b) {
		return areEqual(a, b) || areEqual(a, -b);
	}

}