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

}