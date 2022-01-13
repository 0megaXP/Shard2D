module;

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
Return the position of a point on the perimeter of a square from a rotation angle.
    \param The rotation angle to evaluate
*/
export Vector2 SquarePositionFromAngle(int angle)
{
    int angleNormalized = angle % 360;

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

export float Distance(const Vector2& a, const Vector2& b)
{
    float cos1 = abs(a.x - b.x);
    float cos2 = abs(a.y - b.y);
    return sqrt(cos1 * cos1 + cos2 * cos2);
    
}

export int AngleFromPosition(Vector2 position)
{
    return 0;
}

export Vector2 GetPositionInTheCircumference(Vector2 position, float rotation)
{
    float radius = Distance(Vector2(0, 0), position);
    Vector2 normalizedPos = position.Normalize();

    //float actualRotation = 

    return Vector2();
}