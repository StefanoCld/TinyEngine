#include "cylinderEntity.h"
#include "utils.h"

namespace mgd
{

	CylinderEntity::CylinderEntity() : Entity()
	{
		radius = 1;
		height = 2;
	}

	CylinderEntity::CylinderEntity(float _r, float _h) : Entity()
	{
		radius = _r;
		height = _h;
	}

	CylinderEntity::CylinderEntity(float _r, float _h, Transform _t) : Entity(_t)
	{
		radius = _r;
		height = _h;
	}

	bool CylinderEntity::rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax)
	{

		Vector3 ba = (transform.translate + ((this->height) * transform.up())) - transform.translate;
		Vector3 pa = ray.p - transform.translate;

		Vector3 v = ray.d - ((dot(ray.d, ba)) / ba.squaredNorm()) * (ba);
		Vector3 w = (pa - ((dot(pa, ba)) / ba.squaredNorm()) * (ba));

		float a = v.squaredNorm();
		float b = 2 * (dot(v, w));
		float c = w.squaredNorm() - (this->radius * this->radius);

		float delta = b * b - 4 * a * c;

		if (delta < 0) return false; // ray misses!

		float k = (-b - sqrt(delta)) / (2 * a);
		if (k < 0) return false;
		if (k > distMax) return false;
		distMax = k;

		hitPos = ray.p + k * ray.d;
		
		float t = dot((hitPos - transform.translate), ba) / ba.squaredNorm();

		if (t < 0 || t > 1)
			return false;
		/*
		if (t == 1)
			hitNorm = transform.up();
		else if (t == 0)
			hitNorm = -transform.up();
		*/
		else {

			hitNorm = (hitPos - Vector3(transform.translate.x, hitPos.y, transform.translate.z)).normalized();
			return true;
		}
		
	}

	CylinderEntity* CylinderEntity::apply(const Transform& a)
	{
		CylinderEntity* s = new CylinderEntity();

		s->transform.translate = a.transformPoint(this->transform.translate);
		s->radius = a.transformfloat(this->radius);
		s->height = a.transformfloat(this->height);

		return s;
	}

	void CylinderEntity::Move(Axis axis, float movAmount)
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

	void CylinderEntity::Rotate(Axis axis, float rotAmount)
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

	float CylinderEntity::Lighting(Vector3 hitNorm, Vector3 watcherPos)
	{
		return Entity::Lighting(hitNorm, watcherPos);
	}

}