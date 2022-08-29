#pragma once

namespace mgd {
	class Ray;

	class Camera {
	public:
		float focal;

		int pixelDimX, pixelDimY;

		Camera(float f, int sx, int sy);

		Ray primaryRay(int pixelX, int pixelY);
	};
}