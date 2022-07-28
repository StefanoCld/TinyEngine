#pragma once

#include <assert.h>
#include <cmath>

namespace mgd {

	typedef float Scalar;

	inline Scalar randomBetween(Scalar min, Scalar max) {
		return  min + (std::rand() % 1001) / Scalar(1000) * (max - min);
	}

	struct Vector3 {
		Scalar x, y, z;

		Vector3(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}

		Vector3() :x(0), y(0), z(0) {}

		// linear operations
		Vector3 operator * (Scalar k) const { return Vector3(k * x, k * y, k * z); }
		void operator *= (Scalar k) { x *= k; y *= k; z *= k; }

		Vector3 operator / (Scalar k) const { return Vector3(x / k, y / k, z / k); }
		void operator /= (Scalar k) { x /= k; y /= k; z /= k; }

		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
		void operator += (const Vector3& v) { x += v.x; y += v.y; z += v.z; }

		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
		void operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; }

		Vector3 operator - () const { return Vector3(-x, -y, -z); }
		Vector3 operator + () const { return Vector3(+x, +y, +z); }

		/* accesses to individual coordinates as a vector */
		Scalar operator[] (int i) const {
			switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: assert(0); return 0;
			}
		}

		Scalar& operator[] (int i) {
			static Scalar dummy;
			switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: assert(0); return dummy;
			}
		}

		bool operator == (const Vector3& b) {
			return (x == x) && (y == y) && (z == z);
		}

		// norm (aka magnitude, length, intensity, Eucliden norm...)
		Scalar squaredNorm() const { return x * x + y * y + z * z; }
		Scalar norm() const { return std::sqrt(squaredNorm()); }
		Vector3 normalized() const {
			return (*this) / norm();
		}
		void normalize() {
			(*this) /= norm();
		}

		static Vector3 random(Scalar range) {
			return Vector3(
				randomBetween(-range, +range),
				randomBetween(-range, +range),
				randomBetween(-range, +range)
			);
		}

	};

	// vector scaling is commutative!
	inline Vector3 operator * (Scalar k, const Vector3& a) {
		return a * k;
	}


	const Scalar TOLERANCE = 1e-5;

	inline bool areEqual(Scalar a, Scalar b) {
		return std::abs(a - b) < TOLERANCE;
	}

	inline bool isZero(Scalar a) {
		return std::abs(a) < TOLERANCE;
	}

	inline bool areEqual(const Vector3& a, const Vector3& b) {
		return areEqual(a.x, b.x) && areEqual(a.y, b.y) && areEqual(a.z, b.z);
	}

	inline bool isZero(const Vector3& a) {
		return isZero(a.x) && isZero(a.y) && isZero(a.z);
	}


	inline Scalar dot(const Vector3& a, const Vector3& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline Vector3 cross(const Vector3& a, const Vector3& b) {
		return Vector3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}

	typedef Vector3 Point3;
	typedef Vector3 Versor3;

}; // end of namespace