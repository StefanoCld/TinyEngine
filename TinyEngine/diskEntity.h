#pragma once
#include "vector3.h"
#include "entity.h"

namespace mgd {
	class DiskEntity : public Entity {

		Vector3 n;
		float radius;

	public:
		DiskEntity();

		DiskEntity(float _r);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		DiskEntity* apply(const Transform& a) override;

	};
}