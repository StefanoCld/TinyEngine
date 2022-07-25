#pragma once

#include "quaternion.h"

namespace mgd {

	class Transform {
	public:
		Scalar scale;
		Vector3 translate;
		Quaternion rotate;

		Transform() : scale(1), translate(0, 0, 0), rotate(Quaternion::identity()) {
		}

		Vector3 transformPoint(const Vector3& p) const {
			return rotate.apply(p * scale) + translate;
		}
		Vector3 transformVersor(const Vector3& p) const {
			return rotate.apply(p);
		}
		Vector3 transformVector(const Vector3& p) const {
			return rotate.apply(p * scale);
		}
		Scalar transformScalar(Scalar p) const {
			return p * scale;
		}

		//Get the "local" forward vector
		Vector3 forward() {
			return rotate.apply(Vector3(0, 0, 1));
		}

		Transform inverse() const {
			Transform t;
			t.scale = (1 / scale);
			t.rotate = rotate.conjugated();
			t.translate = t.rotate.apply(-translate * t.scale);
			// alt: t.translarte = t.applyToVector( -translate );
			return t;
		}

		void invert() {
			scale = (1 / scale);
			rotate.conjugate();
			translate = rotate.apply(-translate * scale);
			// alt: translate = applyToVector(-translate);
		}
	};

	//  first b then a
	Transform operator * (const Transform& a, const Transform& b) {
		Transform t;
		t.rotate = a.rotate * b.rotate;
		t.scale = a.scale * b.scale;
		t.translate = a.transformVector(b.translate) + a.translate;
		return t;
	}

}