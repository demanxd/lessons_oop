#pragma once

#include "Entity.h"
#include <unordered_map>
#include <typeindex>
#include <any>
#include <memory>
#include <vector>


class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    Entity create_entity () {
        uint32_t id = _next_id++;
        _entities[id] = std::make_shared<EntityData>();
        Entity e{id, this};
        return e;
    }

    void destroy_entity(Entity e) {
        _entities.erase(e.id());
    }

    Entity get_entity(uint32_t id) {
        return Entity{id, this};
    }


    bool has_component(uint32_t id, const std::type_index& type) const {
        auto it = _entities.find(id);
        if (it == _entities.end()) return false;
        return it->second->components.count(type) > 0;
    }

    template<typename T>
    T& get_component(uint32_t id) {
        auto it = _entities.find(id);
        if (it == _entities.end()) throw std::runtime_error("Entity not found");
        auto cit = it->second->components.find(std::type_index(typeid(T)));
        if (cit == it->second->components.end()) throw std::runtime_error("Component not found");
        return *std::any_cast<T>(&cit->second);
    }

    template<typename T>
    const T& get_component(uint32_t id) const {
        auto it = _entities.find(id);
        if (it == _entities.end()) throw std::runtime_error("Entity not found");
        auto cit = it->second->components.find(std::type_index(typeid(T)));
        if (cit == it->second->components.end()) throw std::runtime_error("Component not found");
        return *std::any_cast<T>(&cit->second);
    }

    template<typename T>
    T* get_component_ptr(uint32_t id) {
        auto it = _entities.find(id);
        if (it == _entities.end()) return nullptr;
        auto cit = it->second->components.find(std::type_index(typeid(T)));
        if (cit == it->second->components.end()) return nullptr;
        return std::any_cast<T>(&cit->second);
    }

    template<typename T>
    const T* get_component_ptr(uint32_t id) const {
        auto it = _entities.find(id);
        if (it == _entities.end()) return nullptr;
        auto cit = it->second->components.find(std::type_index(typeid(T)));
        if (cit == it->second->components.end()) return nullptr;
        return std::any_cast<T>(&cit->second);
    }

    template<typename T>
    void set_component(uint32_t id, const std::type_index& type, T comp) {
        auto& entity = _entities[id];
        entity->components[type] = std::move(comp);
    }

    template<typename T>
    void set_component(uint32_t id, T comp) {
        set_component(id, std::type_index(typeid(T)), comp)
    }

    template<typename T>
    void remove_component(uint32_t id, const std::type_index& type) {
        auto it = _entities.find(id);
        if (it == _entities.end()) return ;
        it->second->components.erase(type);
    }

    void set_entity_flag(uint32_t id, EntityFlag flag) {
        auto it = _entities.find(id);
        if (it == _entities.end()) {
            it->second->flags |= static_cast<uint8_t>(flag);
        }
    }

    void clear_entity_flag(uint32_t id, EntityFlag flag) {
        auto it = _entities.find(id);
        if (it != _entities.end()) {
            it->second->flags &= ~static_cast<uint8_t>(flag);
        }
    }

    bool get_entity_flag(uint32_t id, EntityFlag flag) {
        auto it = _entities.find(id);
        if (it == _entities.end()) return false;
        return (it->second->flags & static_cast<uint8_t>(flag)) != 0;
    }


private:
    uint32_t _next_id = 1;
    struct EntityData
    {
        std::unordered_map<std::type_index, std::any> components;
        uint8_t flags = 0;
    };
    
    std::unordered_map<uint32_t, std::shared_ptr<EntityData>> _entities;
}