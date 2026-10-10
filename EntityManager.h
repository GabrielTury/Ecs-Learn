#pragma once
#include "Entity.h"
#include <queue>

class EntityManager{
private:
	std::queue<Entity>availableEntities;;
	int32_t livingEntityCount = 0;

public:
	EntityManager()
	{
		for (Entity e = 0; e < MAX_ENTITIES; e++)
		{
			availableEntities.push(e);
		}
	}

	Entity CreateEntity();

	void DestroyEntity(Entity entity);
};