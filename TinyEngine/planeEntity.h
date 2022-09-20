#pragma once
#include "entity.h"

namespace mgd {

	class PlaneEntity : public Entity {

		//By default, this versor will always be the transform.up vector
		Vector3 n;

	public:
		PlaneEntity();

		PlaneEntity(Transform _t);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		PlaneEntity* apply(const Transform& a) override;

		void Move(Axis axis, float movAmount) override;

		void Rotate(Axis axis, float rotAmount) override;

		float Lighting(Vector3 hitNorm, Vector3 watcherPos) override;

		bool CanBePossessed() const override { return false; }
	};
}