#include "triangleEntity.h"
#include "utils.h"

namespace mgd
{
	

	TriangleEntity::TriangleEntity() : Entity()
	{
		height = 1;
	}

	TriangleEntity::TriangleEntity(float _height) : Entity()
	{
		height = _height;
	}

	TriangleEntity::TriangleEntity(float _height, Transform _t) : Entity(_t)
	{
		height = _height;
	}

	bool TriangleEntity::rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax)
	{
		//This triangle behaves like a billboard
		//Since L = 2H/srqt(3)
		float halfL = (height) / (std::sqrt(3));
		Vector3 a = this->transform.translate - halfL *(this->transform.right());
		Vector3 b = this->transform.translate + height *(this->transform.up());
		Vector3 c = this->transform.translate + halfL *(this->transform.right());
		
		//This triangle behaves like a normal object (JOKING LOL IT'S A MESS)
		/*
		Vector3 a = this->transform.translate - 2 * (this->transform.right()) - this->transform.translate;
		Vector3 b = this->transform.translate + 2 * (this->transform.up()) - this->transform.translate;
		Vector3 c = this->transform.translate + 2 * (this->transform.right()) - this->transform.translate;
		*/

		Vector3 crossBACA = cross((b - a), (c - a));
		Vector3 n = crossBACA / crossBACA.norm();
		
		float dn = dot(ray.d, n);
		if (dn == 0) return false;

		float k = dot(transform.translate - ray.p, n) / dn;

		if (k < 0) return false;
		if (k > distMax) return false;
		distMax = k;
		hitPos = ray.p + k * ray.d;
		hitNorm = n;

		// Calculating if the point is inside the triangle, using the area-method
		float A = area(a.x, a.y, b.x, b.y, c.x, c.y);

		float A1 = area(hitPos.x, hitPos.y, b.x, b.y, c.x, c.y);

		float A2 = area(a.x, a.y, hitPos.x, hitPos.y, c.x, c.y);

		float A3 = area(a.x, a.y, b.x, b.y, hitPos.x, hitPos.y);

		float A123 = (A1 + A2 + A3);

		/* Check if sum of A1, A2 and A3 is same as A */
		return (std::abs(A - A123) < 0.05f);
	}

	TriangleEntity* TriangleEntity::apply(const Transform& a)
	{
		TriangleEntity* p = new TriangleEntity();

		p->transform.translate = a.transformPoint(this->transform.translate);

		return p;
	}

	void TriangleEntity::Move(Axis axis, float movAmount)
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

	void TriangleEntity::Rotate(Axis axis, float rotAmount)
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

	float TriangleEntity::Lighting(Vector3 hitNorm, Vector3 watcherPos)
	{
		return Entity::Lighting(hitNorm, watcherPos);
	}
}