#include "diskEntity.h"

namespace mgd {

	DiskEntity::DiskEntity() : Entity()
	{
		radius = 1;
		n = Vector3(0, 1, 0);
	}

	DiskEntity::DiskEntity(float _r) : Entity()
	{
		radius = _r;
		n = Vector3(0, 1, 0);
	}

	DiskEntity::DiskEntity(float r, Vector3 n) : Entity()
	{
		radius = r;
		n = n;
	}

	DiskEntity::DiskEntity(float r, Vector3 n, Transform t) : Entity(t)
	{
		radius = r;
		n = n;
	}

	bool DiskEntity::rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) {
		float dn = dot(ray.d, n);
		if (dn == 0) return false;

		float k = dot(transform.translate - ray.p, n) / dn;

		if (k < 0) return false;
		if (k > distMax) return false;

		distMax = k;
		hitPos = ray.p + k * ray.d;

		if ((hitPos - transform.translate).norm() < radius) {
			hitNorm = n;
			return true;
		}
		else
			return false;
	}

	DiskEntity* DiskEntity::apply(const Transform& a)
	{
		DiskEntity* d = new DiskEntity();

		d->transform.translate = a.transformPoint(this->transform.translate);
		d->radius = a.transformfloat(this->radius);
		d->n = a.transformVector(this->n);

		return d;
	}

}

