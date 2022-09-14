#pragma once
#include "transform.h"
#include "shapes3d.h"
#include "utils.h"

namespace mgd {


	class Entity {

	public:
		Transform transform;

		Entity();

		Entity(Transform _t);

		virtual ~Entity() {};

		virtual bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) = 0;

		virtual Entity* apply(const Transform& a) = 0;

		virtual void Move(Axis axis, float movAmount) = 0;

		virtual void Rotate(Axis axis, float rotAmount) = 0;
		
		virtual float Lighting(Vector3 hitNorm, Vector3 watcherPos);

		virtual bool CanBePossessed() const = 0;
	};

}