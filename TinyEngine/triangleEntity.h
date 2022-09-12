#pragma once
#include "entity.h"

namespace mgd {

	class TriangleEntity : public Entity {


	public:
		TriangleEntity();

		TriangleEntity(Transform _t);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		TriangleEntity* apply(const Transform& a) override;

		void Move(Axis axis, float movAmount) override;

		void Rotate(Axis axis, float rotAmount) override;

		float Lighting(Vector3 hitNorm, Vector3 watcherPos) override;

	};
}