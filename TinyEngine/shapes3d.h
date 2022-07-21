#pragma once

#include "vector3.h"
#include "transform.h"

namespace mgd {


	struct Ray {
		Point3 p;
		Versor3 d;

		Ray(Point3 _p, Vector3 _d) : p(_p), d(_d.normalized()) { }
		Ray() {}
	};

	struct Sphere { // POD
		Point3 c;
		Scalar r;
		Sphere(Point3 _c, Scalar _r) :c(_c), r(_r) {}
	};

	struct Plane { // POS
		Versor3 n;
		Point3 p;
		Plane(Point3 _p, Versor3 _n) :p(_p), n(_n) {}
	};


	Sphere apply(const Transform& a, const Sphere& s) {
		return Sphere(
			a.transformPoint(s.c),
			a.transformScalar(s.r)
		);
	}

	bool rayCast(Ray ray, Sphere& sphere, Point3& hitPos, Versor3& hitNorm, float& distMax) {
		// see exercise on paper...
		// the hitpos is (ray.p + k * ray.dir)
		// for some k such that a*k^2 + b*k + c  = 0
		Scalar a = 1;
		Scalar b = 2 * dot(ray.d, ray.p - sphere.c);
		Scalar c = (ray.p - sphere.c).squaredNorm() - sphere.r * sphere.r;

		Scalar delta = b * b - 4 * a * c;

		if (delta < 0) return false; // ray misses the sphere!

		Scalar k = (-b - sqrt(delta)) / (2 * a);
		if (k < 0) return false;
		if (k > distMax) return false;
		distMax = k;

		hitPos = ray.p + k * ray.d;
		hitNorm = (hitPos - sphere.c).normalized();
		return true;

	}

	bool rayCast(Ray ray, Plane plane, Point3& hitPos, Versor3& hitNorm, float& distMax) {
		Scalar dn = dot(ray.d, plane.n);
		if (dn == 0) return false;

		Scalar k = dot(plane.p - ray.p, plane.n) / dn;

		if (k < 0) return false;
		if (k > distMax) return false;
		distMax = k;
		hitPos = ray.p + k * ray.d;
		hitNorm = plane.n;
		return true;
	}


} // end of namespace

