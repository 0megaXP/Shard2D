/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MathVectors.h"
#include "MathUtils.h"

#include <iostream>
#include <math.h>

//import MathUtils;

namespace Shard2D
{
    Vector2::Vector2()
        : x(0), y(0) { }

    Vector2::Vector2(const float newX, const float newY)
        : x(newX), y(newY) { }

    Vector2 const Vector2::Normalize()
    {
        return Vector2(x / MathUtils::Distance(Vector2(), *this), y / MathUtils::Distance(Vector2(), *this));
    }

    const Vector2 Vector2::SquareNormalize()
    {
        return Vector2(x / (abs(x) + abs(y)), y / (abs(x) + abs(y)));
    }

    Vector2 Vector2::operator+(const Vector2& other)
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator-(const Vector2& other)
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator*(const Vector2& other)
    {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 Vector2::operator*(const float& other)
    {
        return Vector2(x * other, y * other);
    }

    Vector2 Vector2::operator/(const Vector2& other)
    {
        return Vector2(x / other.x, y / other.y);
    }

    Vector2 Vector2::operator/(const float& other)
    {
        return Vector2(x / other, y / other);
    }

    std::ostream& operator<<(std::ostream& out, const Vector2& vector)
    {
        out << "Vector(" << vector.x << ", " << vector.y << ')';

        return out;
    }
}