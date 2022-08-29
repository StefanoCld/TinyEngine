#pragma once
#include "transform.h"
#include "vector3.h"
#include "shapes3d.h"

namespace mgd {
	class Entity {
	public:
		Transform transform;

		Entity() : transform() {}

		Entity(Transform _t);

		virtual ~Entity() {};

		virtual bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) {
			return true;
		};

		virtual Entity* apply(const Transform& a) {
			return nullptr;
		};
	};
}