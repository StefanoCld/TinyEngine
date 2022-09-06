#include "sphereEntity.h"
#include "utils.h"

namespace mgd {

	SphereEntity::SphereEntity() : Entity()
	{
		radius = 1;
	}

	SphereEntity::SphereEntity(float _r) : Entity()
	{
		radius = _r;
	}
	
	SphereEntity::SphereEntity(float _r, Transform _t) : Entity(_t)
	{
		radius = _r;
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

		s->transform.translate = a.transformPoint(this->transform.translate);
		s->radius = a.transformfloat(this->radius);

		return s;
	}

	void SphereEntity::Move(Axis axis, float movAmount)
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

	void SphereEntity::Rotate(Axis axis, float rotAmount)
	{
		switch (axis)
		{
		case Axis::forward:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.forward());
			break;

		case Axis::up:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.up());
			break;

		case Axis::right:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.right());
			break;
		}
	}

}