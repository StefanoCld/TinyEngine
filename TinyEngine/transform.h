#pragma once
#include "vector3.h"
#include "quaternion.h"

namespace mgd {

	class Transform {
	public:
		Transform();

		float scale;
		Vector3 translate;
		Quaternion rotate;

		Vector3 transformPoint(const Vector3& p) const;
		Vector3 transformVersor(const Vector3& p) const;
		Vector3 transformVector(const Vector3& p) const;
		float transformfloat(float p) const;

		// get the "local" forward vector
		Vector3 forward();
		// get the "local" right vector
		Vector3 right();
		// get the "local" up vector
		Vector3 up();

		Transform inverse() const;
		void invert();

		//  first b then a
		Transform operator * (const Transform& other) {
			Transform t;
			t.rotate = rotate * other.rotate;
			t.scale = scale * other.scale;
			t.translate = this->transformVector(other.translate) + translate;
			return t;
		}
	};

	//Variant
	/*
	Transform operator * (const Transform& a, const Transform& b) {
		Transform t;
		t.rotate = a.rotate * b.rotate;
		t.scale = a.scale * b.scale;
		t.translate = a.transformVector(b.translate) + a.translate;
		return t;
	}
	*/
}