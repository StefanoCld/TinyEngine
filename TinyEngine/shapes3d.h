#pragma once
#include "vector3.h"

namespace mgd 
{
	struct Ray 
	{ 
		// POD
		Vector3 p;
		Vector3 d;

		Ray(Vector3 _p, Vector3 _d);
		Ray();
	};

} // end of namespace