#include "camera.h"
#include "vector3.h"
#include "shapes3d.h"

using namespace mgd;

Camera::Camera(float f, int sx, int sy){
	focal = f;
	pixelDimX = sx;
	pixelDimY = sy;
}

Ray Camera::primaryRay(int pixelX, int pixelY) {
	Ray r;
	r.p = Vector3(0, 0, 0); // the point of view is by definition on the origin
	float clipX = 2.0f * pixelX / pixelDimX - 1.0;
	float clipY = -2.0f * pixelY / pixelDimY + 1.0;

	r.d = Vector3(clipX, clipY, focal).normalized();

	return r;
}