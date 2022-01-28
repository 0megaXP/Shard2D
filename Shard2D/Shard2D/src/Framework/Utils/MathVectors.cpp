#include "MathVectors.h"

#include <iostream>
#include <math.h>

import MathUtils;

Vector2::Vector2()
    : x(0), y(0) { }

Vector2::Vector2(const float newX, const float newY)
    : x(newX), y(newY) { }

Vector2 const Vector2::Normalize()
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

Vector2 Vector2::operator/(const Vector2& other)
{
    return Vector2(x / other.x, y / other.y);
}

std::ostream& operator<<(std::ostream& out, const Vector2& vector)
{
    out << "Vector(" << vector.x << ", " << vector.y << ')';

    return out;
}