#pragma once
#include "entity.h"

namespace mgd {

	class SphereEntity : public Entity {

	float radius;

	public:
		SphereEntity();

		SphereEntity(float _r);

		SphereEntity(float _r, Transform _t);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		SphereEntity* apply(const Transform& a) override;

		void Move(Axis axis, float movAmount) override;

		void Rotate(Axis axis, float rotAmount) override;

		float Lighting(Vector3 hitNorm, Vector3 watcherPos) override;

	};

}