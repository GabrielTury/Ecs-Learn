#pragma once
#include "EntityManager.h"
#include "ComponentArray.hpp"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <typeindex>

class Coordinator {
private:
    std::unique_ptr<EntityManager> entityManager;
    std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> componentArrays;

    template <typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray() {
        std::type_index typeID = typeid(T);
        if (componentArrays.find(typeID) == componentArrays.end()) {
            componentArrays[typeID] = std::make_shared<ComponentArray<T>>();
        }
        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeID]);
    }

public:
    Coordinator() {
        entityManager = std::make_unique<EntityManager>();
    }

    Entity CreateEntity() {
        return entityManager->CreateEntity();
    }

    void DestroyEntity(Entity entity) {
        entityManager->DestroyEntity(entity);

        // Automatically clean up all components associated with this entity
        for (auto const& pair : componentArrays) {
            pair.second->EntityDestroyed(entity);
        }
    }

    template <typename T>
    void AddComponent(Entity entity, T component) {
        GetComponentArray<T>()->Insert(entity, component);
    }

    template <typename T>
    void RemoveComponent(Entity entity) {
        GetComponentArray<T>()->Remove(entity);
    }

    template <typename T>
    T& GetComponent(Entity entity) {
        return GetComponentArray<T>()->Get(entity);
    }

    template <typename T>
    bool HasComponent(Entity entity) {
        return GetComponentArray<T>()->Has(entity);
    }

    template <typename T>
    void PrintComponents() {
        std::shared_ptr<ComponentArray<T>> componentArray = GetComponentArray<T>();
        auto& components = componentArray->GetComponents();
        for (size_t i = 0; i < componentArray->GetCount(); i++) {
            std::cout << "Component: " << components[i].x << ", " << components[i].y << "\n";
        }
    }
};