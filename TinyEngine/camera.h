#pragma once
#include "shapes3d.h"

namespace mgd { 
	class Camera {
	public:
		float focal;

		int pixelDimX, pixelDimY;

		Camera(float f, int sx, int sy);

		Ray primaryRay(int pixelX, int pixelY);
	};
}