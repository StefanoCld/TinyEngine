#include "shapes3d.h"
#include "vector3.h"
#include "transform.h"

namespace mgd {
	Ray::Ray() {

	}

	Ray::Ray(Vector3 _p, Vector3 _d) {
		p = _p;
		d = _d.normalized();
	}

	Sphere apply(const Transform& a, const Sphere& s) {
		return Sphere(
			a.transformPoint(s.c),
			a.transformfloat(s.r)
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
			a.transformfloat(p.r)
		);
	}

	bool rayCast(Ray ray, Sphere& sphere, Vector3& hitPos, Vector3& hitNorm, float& distMax) {
		// the hitpos is (ray.p + k * ray.dir)
		// for some k such that a*k^2 + b*k + c  = 0
		float a = 1;
		float b = 2 * dot(ray.d, ray.p - sphere.c);
		float c = (ray.p - sphere.c).squaredNorm() - sphere.r * sphere.r;

		float delta = b * b - 4 * a * c;

		if (delta < 0) return false; // ray misses the sphere!

		float k = (-b - sqrt(delta)) / (2 * a);
		if (k < 0) return false;
		if (k > distMax) return false;
		distMax = k;

		hitPos = ray.p + k * ray.d;
		hitNorm = (hitPos - sphere.c).normalized();
		return true;

	}

	bool rayCast(Ray ray, Plane plane, Vector3& hitPos, Vector3& hitNorm, float& distMax) {
		float dn = dot(ray.d, plane.n);
		if (dn == 0) return false;

		float k = dot(plane.p - ray.p, plane.n) / dn;

		if (k < 0) return false;
		if (k > distMax) return false;
		distMax = k;
		hitPos = ray.p + k * ray.d;
		hitNorm = plane.n;
		return true;
	}

	bool rayCast(Ray ray, Disk disk, Vector3& hitPos, Vector3& hitNorm, float& distMax) {
		float dn = dot(ray.d, disk.n);
		if (dn == 0) return false;

		float k = dot(disk.p - ray.p, disk.n) / dn;

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

}
