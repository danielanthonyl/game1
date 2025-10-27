#pragma once

#include <memory>
#include <type_traits>
#include "Entity.hpp"

template<typename T>
T* World::spawnEntity()
{
    static_assert(std::is_base_of<Entity, T>::value, "T must be a subclass of Entity");

    auto entity = std::make_unique<T>();
    entity->setWorld(this);
    entity->initialize();

    T* entityPtr = entity.get();
    entities.push_back(std::move(entity));

    return entityPtr;
}