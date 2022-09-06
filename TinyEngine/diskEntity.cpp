#include "diskEntity.h"
#include "utils.h"

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

	DiskEntity::DiskEntity(float _r, Vector3 _n) : Entity()
	{
		radius = _r;
		n = _n;
	}

	DiskEntity::DiskEntity(float _r, Vector3 _n, Transform _t) : Entity(_t)
	{
		radius = _r;
		n = _n;
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
		d->n = a.transformVersor(this->n);

		return d;
	}

	void DiskEntity::Move(Axis axis, float movAmount)
	{
		switch (axis) 
		{
		case Axis::forward:
			this->transform.translate += this->transform.forward() * movAmount;

		case Axis::up:
			this->transform.translate += this->transform.up() * movAmount;

		case Axis::right:
			this->transform.translate += this->transform.right() * movAmount;
		}
	}

	void DiskEntity::Rotate(Axis axis, float rotAmount)
	{
		switch (axis)
		{
		case Axis::forward:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.forward());

		case Axis::up:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.up());

		case Axis::right:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.right());
		}

		this->n = this->transform.transformVersor(n);
	}

}

