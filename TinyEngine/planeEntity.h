#pragma once
#include "vector3.h"
#include "entity.h"

namespace mgd {

	class PlaneEntity : public Entity {
		
		Vector3 n;

	public:
		PlaneEntity();

		PlaneEntity(Transform _t);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		PlaneEntity* apply(const Transform& a) override;

		void Move(Axis axis, float movAmount) override;

		void Rotate(Axis axis, float rotAmount) override;

	};
}