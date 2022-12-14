#pragma once
#include "vector3.h"
#include "entity.h"

namespace mgd 
{

	class DiskEntity : public Entity {

		//By default, this versor will always be the transform.up vector
		Vector3 n;

		float radius;

	public:
		DiskEntity();

		DiskEntity(float _r);

		DiskEntity(float _r, Transform _t);

		bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) override;

		DiskEntity* apply(const Transform& a) override;

		void Move(Axis axis, float movAmount) override;

		void Rotate(Axis axis, float rotAmount) override;

		float Lighting(Vector3 hitNorm) override;

		bool CanBePossessed() const override { return false; }
	};

}