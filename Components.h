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
