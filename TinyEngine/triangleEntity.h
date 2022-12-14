#pragma once
#include "entity.h"

namespace mgd 
{

	class TriangleEntity : public Entity {

		//By default, this versor will always be the -transform.forward vector
		Vector3 n;

		float height;

		inline float area(float x1, float y1, float x2, float y2, float x3, float y3)
		{
			return std::abs(((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2))) / 2.0f);
		}

	public:
		bool bBillboardMode = false;

		TriangleEntity();

		TriangleEntity(float _h);

		TriangleEntity(float _h, Transform _t);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		TriangleEntity* apply(const Transform& a) override;

		void Move(Axis axis, float movAmount) override;

		void Rotate(Axis axis, float rotAmount) override;

		float Lighting(Vector3 hitNorm) override;

		bool CanBePossessed() const override { return false; }
	};
}