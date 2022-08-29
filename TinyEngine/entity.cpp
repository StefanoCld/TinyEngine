#include "entity.h"

namespace mgd {

	Entity::Entity()
	{
		transform = Transform();
	}

	Entity::Entity(Transform t)
	{
		transform = t;
	}
}

