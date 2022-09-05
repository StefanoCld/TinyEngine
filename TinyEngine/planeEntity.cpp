#include "planeEntity.h"

namespace mgd {

	PlaneEntity::PlaneEntity() : Entity(){}

	PlaneEntity::PlaneEntity(Transform _t) : Entity(_t){}

	PlaneEntity::PlaneEntity(Transform _t, Vector3 _n) : Entity(_t) 
	{
		n = _n;
	}

	bool PlaneEntity::rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax)
	{
		float dn = dot(ray.d, n);
		if (dn == 0) return false;

		float k = dot(transform.translate - ray.p, n) / dn;

		if (k < 0) return false;
		if (k > distMax) return false;
		distMax = k;
		hitPos = ray.p + k * ray.d;
		hitNorm = n;
		return true;
	}

	PlaneEntity* PlaneEntity::apply(const Transform& a)
	{
		PlaneEntity* p = new PlaneEntity();

		p->transform.translate = a.transformPoint(this->transform.translate);
		p->n = a.transformVersor(this->n);

		return p;
	}
}