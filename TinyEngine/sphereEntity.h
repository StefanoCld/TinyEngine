#pragma once
#include "entity.h"

namespace mgd {
	class SphereEntity : public Entity {

	float radius;

	public:
		SphereEntity();

		SphereEntity(float _r);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		SphereEntity* apply(const Transform& a) override;

	};
}