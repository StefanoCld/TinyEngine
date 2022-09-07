#include "planeEntity.h"
#include "utils.h"

namespace mgd 
{

	PlaneEntity::PlaneEntity() : Entity(){}

	PlaneEntity::PlaneEntity(Transform _t) : Entity(_t){}

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

	void PlaneEntity::Move(Axis axis, float movAmount)
	{
		switch (axis)
		{
		case Axis::forward:
			this->transform.translate += this->transform.forward() * movAmount;
			break;

		case Axis::up:
			this->transform.translate += this->transform.up() * movAmount;
			break;

		case Axis::right:
			this->transform.translate += this->transform.right() * movAmount;
			break;
		}
	}

	void PlaneEntity::Rotate(Axis axis, float rotAmount)
	{
		switch (axis)
		{
		case Axis::forward:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.forward());
			this->n = this->transform.up();
			break;

		case Axis::up:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.up());
			this->n = this->transform.up();
			break;

		case Axis::right:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.right());
			this->n = this->transform.up();
			break;
		}
	}

}