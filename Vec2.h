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

#include <cstdint>

template <typename T>
struct Vec2
{
public:
    Vec2() : x(0), y(0) {}
    Vec2(T x, T y) : x(x), y(y) {}
    Vec2(const Vec2& v) : x(v.x), y(v.y) {}
    ~Vec2() {}

    T get_x() const {return x;}
    T get_y() const {return y;}
    
    void set_x(T x) {this->x = x};
    void set_y(T y) {this->y = y};

    Vec2& operator=(const Vect2& v) { x = v.x; y = v.y; return *this; }
    bool operator==(const Vect2& v) const { return (x == v.x && y == v.y); }
    bool operator!=(const Vect2& v) const { return !(*this == v);}

    Vec2 operator+(const Vec2& v) const {return Vec2(x + v.x, y + v.y); }
    Vec2 operator+(const Vec2& v) const {return Vec2(x - v.x, y - v.y); }
    Vec2 operator*(const T& s) const {return Vec2(x * s, y * s); }

    Vec2& operator+=(const Vec2& v) const {x += v.x, y += v.y; return *this; }

    T x, y;
};


using Point2D  = Vec2 <uint32_t>;
using Point2DF = Vec2 <float>;
using Point2DI = Vec2 <int32_t>;