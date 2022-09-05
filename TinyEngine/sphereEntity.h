#pragma once
#include "entity.h"

namespace mgd {
	class SphereEntity : public Entity {

	float radius;

	public:
		SphereEntity();
		SphereEntity(float r);
		SphereEntity(float r, Transform t);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		SphereEntity* apply(const Transform& a) override;
	};
}