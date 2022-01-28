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
Return the position of a point on the perimeter of a square from a rotation angle.
    \param The rotation angle to evaluate
*/
export Vector2 SquarePositionFromAngle(int angle)
{
    int angleNormalized = angle % 360;

    if (angleNormalized < 0)
        angleNormalized += 360;

    Vector2 dot;

    if (angleNormalized % 90 == 0)
    {
        dot.x = Between(angleNormalized / 90, 1, 2, true) ? -1 : 1;
        dot.y = angleNormalized / 90 <= 1 ? 1 : -1;
    }
    else
    {
        if (Between(angleNormalized, 0, 90, false))
        {
            dot.y = 1;
            dot.x = (((float)(angleNormalized % 90) / 90) * 2 - 1) * -1;
        }
        else if (Between(angleNormalized, 90, 180, false))
        {
            dot.x = -1;
            dot.y = (((float)(angleNormalized % 90) / 90) * 2 - 1) * -1;
        }
        else if (Between(angleNormalized, 180, 270, false))
        {
            dot.y = -1;
            dot.x = (((float)(angleNormalized % 90) / 90) * 2 -1);
        }
        else if (Between(angleNormalized, 270, 360, false))
        {
            dot.x = 1;
            dot.y = (((float)(angleNormalized % 90) / 90) * 2 - 1);
        }
    }

    return dot;
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