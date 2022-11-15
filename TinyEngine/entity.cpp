#include "entity.h"

namespace mgd 
{

	Entity::Entity()
	{
		transform = Transform();
	}

	Entity::Entity(Transform _t)
	{
		transform = _t;
	}

	float Entity::Lighting(Vector3 hitNorm)
	{
		Vector3 lightDir = Vector3(1, 2, -2).normalized();

		float diffuse = dot(hitNorm, lightDir);
		if (diffuse < 0) diffuse = 0;

		return diffuse;
	}

}