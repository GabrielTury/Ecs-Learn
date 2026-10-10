#pragma once
#include "SparseSet.hpp"
#include <string>

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public SparseSet<T>, public IComponentArray {
public:

    void EntityDestroyed(Entity entity) override {
        if (this->Has(entity)) {
            this->Remove(entity);
        }
    }
};