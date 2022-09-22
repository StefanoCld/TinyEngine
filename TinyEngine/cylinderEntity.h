#pragma once
#include "entity.h"

namespace mgd {

	class CylinderEntity : public Entity {

		float radius;
		float height;

	public:
		CylinderEntity();

		CylinderEntity(float _r, float _h);

		CylinderEntity(float _r, float _h, Transform _t);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		CylinderEntity* apply(const Transform& a) override;

		void Move(Axis axis, float movAmount) override;

		void Rotate(Axis axis, float rotAmount) override;

		float Lighting(Vector3 hitNorm, Vector3 watcherPos) override;

		bool CanBePossessed() const override { return true; }
	};

}