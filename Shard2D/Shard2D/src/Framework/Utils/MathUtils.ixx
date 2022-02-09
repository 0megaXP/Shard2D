module;

#define _USE_MATH_DEFINES

#include <math.h>
#include "MathVectors.h"

import BooleanUtils;

export module MathUtils;

/**
Returns a value clamped between the min and max values.
    \param The value to clamp
    \param The min value
    \param The max value
*/
export float Clamp(float value, float min, float max)
{
    if (value > max)
        return max;
    else if (value < min)
        return min;
    else
        return value;
}

/**
Returns a value clamped between 0 and 1. If lower than 0, returns 0. If greater than 1, returns 1.
    \param The value to clamp
*/
export float Clamp01(float value)
{
    return Clamp(value, 0, 1);
}

/**
Returns a value rounded to zero if it is lower than 0.0001 or higher than -0.0001
*/
export float RoundToZero(float value)
{
    if (value > 0)
        if (value < 0.0001)
            return 0;
        else
            return value;
    else
        if (value > -0.0001)
            return 0;
        else
            return value;
}

/**
Returns the legnth of the distance between 2 Vector2
*/
export float Distance(const Vector2& a, const Vector2& b)
{
    float distX = abs(a.x - b.x);
    float disty = abs(a.y - b.y);
    return sqrt(distX * distX + disty * disty);
}

/**
Returns the position inside a circumference of the given rotation as radians
*/
export Vector2 PositionFromRad(float rotation)
{
    float x = cos(rotation);
    float y = sin(rotation);
    return Vector2(RoundToZero(x), RoundToZero(y));
}

/**
Returns the position inside a circumference of the given rotation as degrees
*/
export Vector2 PositionFromDeg(float rotation)
{
    float radRotation = rotation * 2 * M_PI / 360;
    return PositionFromRad(radRotation);
}

/**
Returns the rotation as degree at a certain position of a circumference with the given centre
*/
export float DegFromPosition(Vector2 position, Vector2 centre)
{
    Vector2 normalizedPosition = (position - centre).Normalize();
    float rotation = (normalizedPosition.x * -1 + 1) / 2 * 180;
    if (normalizedPosition.y < 0)
        rotation = 360 - rotation;
    return rotation;
}

/**
Checks if the given point is inside the rect created with the given origin point, width, height and rotation
*/
export bool PointInsideRect(Vector2 point, Vector2 origin, float width, float height, float rotation)
{
    Vector2 rectPoints[4];

    rectPoints[0] = origin;
    rectPoints[1] = origin + (PositionFromDeg(rotation) * width);
    rectPoints[3] = origin + (PositionFromDeg(rotation + 90) * height);
    rectPoints[2] = origin + (rectPoints[1] - origin) + (rectPoints[3] - origin);

    int i, j, c = 0;
    for (i = 0, j = 4 - 1; i < 4; j = i++) {
        if (((rectPoints[i].y > point.y) != (rectPoints[j].y > point.y)) &&
            (point.x < (rectPoints[j].x - rectPoints[i].x) * (point.y - rectPoints[i].y) / (rectPoints[j].y - rectPoints[i].y) + rectPoints[i].x))
            c = ~c;
    }
    return c;
}