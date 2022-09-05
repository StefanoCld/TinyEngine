#pragma once
#include "vector3.h"
#include "entity.h"

namespace mgd {
	class PlaneEntity : public Entity {

		Vector3 n;

	public:
		PlaneEntity();
		PlaneEntity(Transform t);
		PlaneEntity(Transform t, Vector3 _n);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		PlaneEntity* apply(const Transform& a) override;
	};
}