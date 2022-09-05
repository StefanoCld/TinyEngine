#pragma once
#include "transform.h"
#include "vector3.h"
#include "shapes3d.h"
#include <iostream>
using namespace std;

namespace mgd {

	class Entity {

	public:
		Transform transform;

		Entity();

		Entity(Transform _t);

		virtual ~Entity() {};

		virtual bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) = 0;

		virtual Entity* apply(const Transform& a) = 0;
	};

}