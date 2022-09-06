#include "shapes3d.h"
#include "vector3.h"
#include "transform.h"

namespace mgd {
	Ray::Ray() {

	}

	Ray::Ray(Vector3 _p, Vector3 _d) {
		p = _p;
		d = _d.normalized();
	}
}
