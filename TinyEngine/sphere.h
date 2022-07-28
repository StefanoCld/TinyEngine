#pragma once

#include "gameobj.h"

namespace mgd {
	class Sphere : public GameObj {
	public:
		Point3 c;
		Scalar r;
		Sphere(Point3 _c, Scalar _r);
		Sphere();

		void rayCast(const Ray& ray, Point3& hitPos, Versor3& hitNorm, float& distMax) override;
		GameObj* applyTransform(const Transform& t) override;

		bool sphereRayCast(Ray ray, Sphere& sphere, Point3& hitPos, Versor3& hitNorm, float& distMax);
	};
}