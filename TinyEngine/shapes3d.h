#pragma once


namespace mgd {

	struct Ray {
		Point3 p;
		Versor3 d;

		Ray(Point3 _p, Vector3 _d) : p(_p), d(_d.normalized()) { }
		Ray() {}
	};
	/*
	struct Sphere { // POD
		Point3 c;
		Scalar r;
		Sphere(Point3 _c, Scalar _r) :c(_c), r(_r) {}
	};
	
	struct Plane { // POD
		Versor3 n;
		Point3 p;
		Plane(Point3 _p, Versor3 _n) :p(_p), n(_n) {}
	};

	struct Disk { // POD
		Versor3 n;
		Point3 p;
		Scalar r;
		Disk(Point3 _p, Versor3 _n, Scalar _r) :p(_p), n(_n), r(_r) {}
	};
	
	Sphere apply(const Transform& a, const Sphere& s) {
		return Sphere(
			a.transformPoint(s.c),
			a.transformScalar(s.r)
		);
	}
	
	Plane apply(const Transform& a, const Plane& p) {
		return Plane(
			a.transformPoint(p.p),
			a.transformVersor(p.n)
		);
	}

	Disk apply(const Transform& a, const Disk& p) {
		return Disk(
			a.transformPoint(p.p),
			a.transformVersor(p.n),
			a.transformScalar(p.r)
		);
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

	bool rayCast(Ray ray, Disk disk, Point3& hitPos, Versor3& hitNorm, float& distMax) {
		Scalar dn = dot(ray.d, disk.n);
		if (dn == 0) return false;

		Scalar k = dot(disk.p - ray.p, disk.n) / dn;

		if (k < 0) return false;
		if (k > distMax) return false;

		distMax = k;
		hitPos = ray.p + k * ray.d;

		if ((hitPos - disk.p).norm() < disk.r) {
			hitNorm = disk.n;
			return true;
		}
		else
			return false;
	}
	*/
} // end of namespace

