#include "transform.h"

using namespace mgd;

Transform::Transform(){
	scale = 1; 
	mgd::Transform::translate = mgd::Vector3(0,0,0);
	mgd::Transform::rotate = mgd::Quaternion::identity();
}

Vector3 Transform::transformPoint(const Vector3& p) const {
	return rotate.apply(p * scale) + translate;
}
Vector3 Transform::transformVersor(const Vector3& p) const {
	return rotate.apply(p);
}
Vector3 Transform::transformVector(const Vector3& p) const {
	return rotate.apply(p * scale);
}
float Transform::transformfloat(float p) const {
	return p * scale;
}

Vector3 Transform::forward() {
	// get the "local" forward vector
	return rotate.apply(Vector3(0, 0, 1));
}

Transform Transform::inverse() const {
	Transform t;
	t.scale = (1 / scale);
	t.rotate = rotate.conjugated();
	t.translate = t.rotate.apply(-translate * t.scale);
	// alt: t.translate = t.applyToVector( -translate );
	return t;
}

void Transform::invert() {
	scale = (1 / scale);
	rotate.conjugate();
	translate = rotate.apply(-translate * scale);
	// alt: translate = applyToVector(-translate);
}