#include "triangleEntity.h"
#include "utils.h"

namespace mgd
{
	float area(float x1, float y1, float x2, float y2, float x3, float y3)
	{
		return std::abs(((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2))) / 2.0f);
	}

	TriangleEntity::TriangleEntity() : Entity()
	{

	}

	TriangleEntity::TriangleEntity(Transform _t) : Entity(_t)
	{

	}

	bool TriangleEntity::rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax)
	{
		//This tri behaves like a billboard right now

		Vector3 a = this->transform.translate - 2*(this->transform.right());
		Vector3 b = this->transform.translate + 2*(this->transform.up());
		Vector3 c = this->transform.translate + 2*(this->transform.right());

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

		float A = area(a.x, a.y, b.x, b.y, c.x, c.y);

		/* Calculate area of triangle PBC */
		float A1 = area(hitPos.x, hitPos.y, b.x, b.y, c.x, c.y);

		/* Calculate area of triangle PAC */
		float A2 = area(a.x, a.y, hitPos.x, hitPos.y, c.x, c.y);

		/* Calculate area of triangle PAB */
		float A3 = area(a.x, a.y, b.x, b.y, hitPos.x, hitPos.y);

		float A123 = (A1 + A2 + A3);

		/* Check if sum of A1, A2 and A3 is same as A */
		return (std::abs(A - A123) < 0.05f);

		//return true;
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
			//this->n = this->transform.up();
			break;

		case Axis::up:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.up());
			//this->n = this->transform.up();
			break;

		case Axis::right:
			this->transform.rotate = this->transform.rotate * Quaternion::fromAngleAxis(rotAmount, this->transform.right());
			//this->n = this->transform.up();
			break;
		}
	}

	float TriangleEntity::Lighting(Vector3 hitNorm, Vector3 watcherPos)
	{
		return Entity::Lighting(hitNorm, watcherPos);
	}

}