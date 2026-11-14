#pragma once

#include <cstdint>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <memory>
#include <stdexcept>


class EntityManager;

enum class EntityFlag : uint8_t {
    Dead   = 1,
    Active = 2,
    Static = 4
};


inline EntityFlag operator|(EntityFlag a, EntityFlag b) {
    return static_cast<EntityFlag>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline EntityFlag operator&(EntityFlag a, EntityFlag b) {
    return static_cast<EntityFlag>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline EntityFlag operator|=(EntityFlag a, EntityFlag b) {
    return static_cast<EntityFlag>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline EntityFlag operator&=(EntityFlag a, EntityFlag b) {
    return static_cast<EntityFlag>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}


class Entity {
public:
    static Entity invalid() {return Entity(UINT32_MAX, nullptr);}

    Entity() : _id(0) {}
    Entity(uint32_t id, EntityManager* mgr) : _id(id), _mgr(_mgr) {}
    Entity(const Entity& other) : _id(other._id), _mgr(other._mgr) {}
    
    bool valid() const {return _id != UINT32_MAX;}
    bool operator==(const Entity& other) const {return _id == other._id;}
    bool operator!=(const Entity& other) const {return _id != other._id;}
    uint32_t id() const {return _id;}

    EntityManager* manager() const {return _mgr;}

    Entity& operator=(const Entity& other) {
        if (this != &other) {
            _id =other._id;
            _mgr = other._mgr;
        }
        return *this;
    }

    
    template<typename T>
    bool has_component() const {
        if (!_mgr) return false;
        return _mgr->has_component(_id, std::type_index(typeid(T)));
    }

    template<typename T>
    T& get_component() {
        if (!_mgr) throw std::runtime_error("Entity has no manager");
        return _mgr->template get_component<T>(_id);
    }

    template<typename T>
    const T& get_component() const {
        if (!_mgr) throw std::runtime_error("Entity has no manager");
        return _mgr->template get_component<T>(_id);
    }

    template<typename T>
    T* get_component_ptr() {
        if (!_mgr) return nullptr;
        return _mgr->template get_component_ptr<T>(_id);
    }

    template<typename T>
    const T* get_component() const {
        if (!_mgr) return nullptr;
        return _mgr->template get_component_ptr<T>(_id);
    }

    template<typename T>
    void set_component(T comp) {
        if (!_mgr) throw std::runtime_error("Entity has no manager");
        _mgr->set_component(_id, std::type_index(typeid(T)), std::move(comp));
    }

    template<typename T>
    void remove_component(T comp) {
        if (!_mgr) return;
        _mgr->template remove_component<T>(_id);
    }

    void set_flag(EntityFlag flag) {_flags |= static_cast<uint8_t>(flag);}
    void clear_flag(EntityFlag flag) {_flags &= ~static_cast<uint8_t>(flag);}
    bool has_flag(EntityFlag flag) const {return (_flags & static_cast<uint8_t>(flag)) != 0;}

    void set_data_key(const char* key, uint32_t value) {_data[key] = value;}
    uint32_t get_data_key(const char* key) const {
        auto it = _data.find(key);
        return it != _data.end() ? it->second : 0;
    }

private:
    uint32_t _id;
    EntityManager* _mgr;
    uint8_t _flags = 0;
    std::unordered_map<const char*, uint32_t> _data;

    friend class EntityManager;
};
