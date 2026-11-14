/* MIT License
 * 
 * Copyright (c) 2026 Voronezh State University
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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