#include "transform.h"

using namespace mgd;

extern Transform operator * (const Transform& a) {
	Transform t;
	t.rotate = a.rotate * b.rotate;
	t.scale = a.scale * b.scale;
	t.translate = a.transformVector(b.translate) + a.translate;
	return t;
}