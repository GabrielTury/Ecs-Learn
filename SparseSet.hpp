#pragma once
#include "Entity.h"
#include <vector>
#include <cassert>

template <typename T> class SparseSet {
private:
	std::vector<T> components; //component data
	std::vector<Entity> dense; //entities IDs
	std::vector<size_t> sparse;//index of entity in dense vector

	size_t count = 0;
public:
    SparseSet() { sparse.resize(MAX_ENTITIES, -1); };

	void Insert(Entity entity, T component) {
		assert(entity < MAX_ENTITIES && "Entity out of bounds");
		assert(sparse[entity] == -1 && "Entity already has a component");
		
		dense.push_back(entity);
		components.push_back(component);

		sparse[entity] = count;
		count++;
	}

    void Remove(Entity entity) {
        assert(Has(entity) && "Entity does not have this component");
        
        size_t indexToRemove = sparse[entity];
        size_t indexOfLast = count - 1;
        
        Entity lastEntity = dense[indexOfLast];
        dense[indexToRemove] = lastEntity;
        components[indexToRemove] = components[indexOfLast];
        
        sparse[lastEntity] = indexToRemove;

        sparse[entity] = -1;
        dense.pop_back();
        components.pop_back();
        count--;
    }

    bool Has(Entity entity) const {
        return entity < MAX_ENTITIES && sparse[entity] != -1;
    }

    T& Get(Entity entity) {
        assert(Has(entity) && "Entity does not have this component");
        return components[sparse[entity]];
    }
    
    std::vector<T>& GetComponents() { return components; }
    size_t GetCount() const { return count; }
};