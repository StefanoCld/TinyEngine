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

		// Every derived entity will implement..
		
		//..their ray-intersection algorithm 
		virtual bool rayCast(Ray ray, Vector3& hitPos, Vector3& hitNorm, float& distMax) = 0;

		//..their way of applying their relative transform
		virtual Entity* apply(const Transform& a) = 0;

		//..their way of moving..
		virtual void Move(Axis axis, float movAmount) = 0;

		//..and rotating the object.
		virtual void Rotate(Axis axis, float rotAmount) = 0;
		
		//Also, if their lighting-behaviour differs from the standard one, they will implement their own
		virtual float Lighting(Vector3 hitNorm, Vector3 watcherPos);

		//Return true, if the the object can be controlled (moved and rotated) by the player
		virtual bool CanBePossessed() const = 0;
	};

}