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

#include "Vec2.h"
#include "ObjectPool.h"
#include <cstdint>


struct Position {
    float x = 0, y = 0;
}


struct Velocity {
    float dx = 0, dy = 0;
};


struct Sprite {
    uint32_t color = 0;
}


struct LifeIcon {
    int icon_index = 0;
}


struct Collider {
    uint16_t layer = 0;
    uint16_t mask  = 0;
}


struct InputComponent {
    bool enable = false;
    float speed = 0;
}


struct Size {
    float x = 0, y = 0;
}


struct ProjectileData : Poolable {
    bool active = false;
    ProjectileData* pool_obj = nullptr;
    ProjectileData() = default;
    explicit ProjectileData(bool a) : active(a) {}
    void reset() override { active = false; }
};


struct AsteroidData : Poolable {
    int type = 0;
    int split_count = 0;
    AsteroidData* pool_obj = nullptr;
    AsteroidData() = default;
    AsteroidData(int t, int sc) : type(t), split_count(sc) {};
    void reset() override { type = 0; split_count = 0; }
};
