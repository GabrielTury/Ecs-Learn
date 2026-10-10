#include "EntityManager.h"

#include <cassert>

Entity EntityManager::CreateEntity()
{
	assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence!");

	Entity id = availableEntities.front();
	availableEntities.pop();
	++livingEntityCount;

	return id;	
}

void EntityManager::DestroyEntity(Entity entity) {
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	// Recycle the ID
	availableEntities.push(entity);
	--livingEntityCount;
}