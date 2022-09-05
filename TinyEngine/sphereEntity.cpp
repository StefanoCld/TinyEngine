#include "sphereEntity.h"

namespace mgd {

	SphereEntity::SphereEntity() : Entity()
	{
		radius = 1;
	}

	SphereEntity::SphereEntity(float r) : Entity()
	{
		radius = r;
	}
	
	SphereEntity::SphereEntity(Transform t, float r) : Entity(t)
	{
		radius = r;
	}

	bool SphereEntity::rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax)
	{
		// the hitpos is (ray.p + k * ray.dir)
		// for some k such that a*k^2 + b*k + c  = 0
		float a = 1;
		float b = 2 * dot(ray.d, ray.p - transform.translate);
		float c = (ray.p - transform.translate).squaredNorm() - radius * radius;

		float delta = b * b - 4 * a * c;

		if (delta < 0) return false; // ray misses the sphere!

		float k = (-b - sqrt(delta)) / (2 * a);
		if (k < 0) return false;
		if (k > distMax) return false;
		distMax = k;

		hitPos = ray.p + k * ray.d;
		hitNorm = (hitPos - transform.translate).normalized();
		return true;
	}

	SphereEntity* SphereEntity::apply(const Transform& a)
	{
		SphereEntity* s = new SphereEntity();
		Vector3 v = this->transform.translate;
		Vector3 vt = a.transformPoint(v);
		s->transform.translate = a.translate;

		return s;
	}
}