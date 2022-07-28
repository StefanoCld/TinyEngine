#pragma once

#include "transform.h"
#include "shapes3d.h"


namespace mgd {
	class GameObj {
	public:
		Transform transform;

		GameObj() :
			transform()
		{

		}

		virtual void rayCast(const Ray& ray, Point3& hitPos, Versor3& hitNorm, float& distMax) = 0;
		virtual GameObj* applyTransform(const Transform& t) = 0;

		virtual ~GameObj() {};
	};
}