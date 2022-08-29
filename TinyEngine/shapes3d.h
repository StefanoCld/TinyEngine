#pragma once
#include"vector3.h"
#include"transform.h"

namespace mgd {

	struct Ray { // POD
		Vector3 p;
		Vector3 d;

		Ray(Vector3 _p, Vector3 _d);
		Ray();
	};

	struct Sphere { // POD
		Vector3 c;
		float r;
		Sphere(Vector3 _c, float _r) :c(_c), r(_r) {}
	};

	struct Plane { // POD
		Vector3 n;
		Vector3 p;
		Plane(Vector3 _p, Vector3 _n) :p(_p), n(_n) {}
	};

	struct Disk { // POD
		Vector3 n;
		Vector3 p;
		float r;
		Disk(Vector3 _p, Vector3 _n, float _r) :p(_p), n(_n), r(_r) {}
	};

	Sphere apply(const Transform& a, const Sphere& s);

	Plane apply(const Transform& a, const Plane& p);

	Disk apply(const Transform& a, const Disk& p);

	bool rayCast(Ray ray, Sphere& sphere, Vector3& hitPos, Vector3& hitNorm, float& distMax);

	bool rayCast(Ray ray, Plane plane, Vector3& hitPos, Vector3& hitNorm, float& distMax);

	bool rayCast(Ray ray, Disk disk, Vector3& hitPos, Vector3& hitNorm, float& distMax);

} // end of namespace