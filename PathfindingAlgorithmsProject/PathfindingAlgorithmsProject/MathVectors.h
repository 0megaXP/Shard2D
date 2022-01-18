#pragma once

#include <iosfwd>

struct Vector2
{
    Vector2();

    Vector2(const float newX, const float newY);

    float x;
    float y;

    const Vector2 Normalize();

    Vector2 operator+(const Vector2& other);

    Vector2 operator-(const Vector2& other);

    Vector2 operator*(const Vector2& other);

    Vector2 operator/(const Vector2& other);

    friend std::ostream& operator<<(std::ostream& out, const Vector2& vector);
};

