#include "sphere.h"

using namespace mgd;

Sphere::Sphere() {
	c = Vector3(0, 0, 0);
	r = 1;
}

Sphere::Sphere(Point3 _c, Scalar _r)
{
	c = _c;
	r = _r;
}

void Sphere::rayCast(const Ray& ray, Point3& hitPos, Versor3& hitNorm, float& distMax)
{
	sphereRayCast(ray, *this, hitPos, hitNorm, distMax);
}

bool Sphere::sphereRayCast(Ray ray, Sphere& sphere, Point3& hitPos, Versor3& hitNorm, float& distMax) {
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

GameObj* Sphere::applyTransform(const Transform& t)
{
	return new Sphere(
		t.transformPoint(c),
		t.transformScalar(r)
	);
}