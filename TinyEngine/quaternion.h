#pragma once

#pragma once
#include <cmath>
#include "vector3.h"

#define M_PI 3.14159265358979323846

namespace mgd {

	class Quaternion {
	public:
		Vector3 im;
		Scalar re;

		Quaternion(Vector3 _im, Scalar _re) :im(_im), re(_re) { }

		Vector3 apply(Vector3 p) const;

		void conjugate() {
			im = -im;
		}

		Quaternion conjugated() const {
			return Quaternion(-im, re);
		}

		Quaternion operator -() const {
			return Quaternion(-im, -re);
		}

		static Quaternion fromVector3(Vector3 v) {
			return Quaternion(v, 0);
		}
		static Quaternion fromAngleAxis(Scalar deg, Vector3 axis) {
			Scalar rad = deg * M_PI / 180;
			Scalar s = std::sin(rad / 2);
			Scalar c = std::cos(rad / 2);
			return Quaternion(axis.normalized() * s, c);
		}
		static Quaternion identity() {
			return Quaternion(Vector3(0, 0, 0), 1);
		}

	};

	inline Quaternion operator * (const Quaternion& a, const Quaternion& b) {
		return Quaternion(
			cross(a.im, b.im) + a.im * b.re + a.re * b.im,
			-dot(a.im, b.im) + a.re * b.re
		);
	}

	inline Vector3 Quaternion::apply(Vector3 p) const {
		Quaternion q = fromVector3(p);
		q = (*this) * q * this->conjugated();
		assert(areEqual(q.re, 0));
		return q.im;
	}

	inline bool areEqual(const Quaternion& a, const Quaternion& b) {
		return areEqual(a.im, b.im) && areEqual(a.re, b.re);
	}

	inline bool areEquivalent(const Quaternion& a, const Quaternion& b) {
		return areEqual(a, b) || areEqual(a, -b);
	}

}