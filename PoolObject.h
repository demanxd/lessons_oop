#pragma once

#include <memory>
#include <vector>
#include <type_traits>
#include <algorithm>


class Poolable {
public:
    virtual ~Poolable() = default;
    virtual void reset() = 0;
};

template <typename T>
class ObjectPool {
public:
    ObjectPool() = default;
    ~ObjectPool() {
        for (auto* obj : _available) delete obj;
        for (auto* obj : _in_use) delete obj;
    }

    T* acquire() {
        if (_available.empty()) {
            return new T;
        }
        T* obj = _available.back();
        _available.pop_back();
        _in_use.push_back(obj);
        return obj;
    }

    void release(T* obj) {
        static_assert(std::is_base_of<Poolable, T>::value, "T must inherit from Poolable");
        obj->reset();
        auto it = std::find(_in_use.begin(), _in_use.end(), obj);
        if (it != _in_use.end()) {
            _in_use.erase(it);
        }
        _available.push_back(obj);
    }

    size_t available_count() const { return _available.size(); }
    size_t in_use_count() const { return _in_use.size(); }


private:
    std::vector<T*> _available;
    std::vector<T*> _in_use;
}