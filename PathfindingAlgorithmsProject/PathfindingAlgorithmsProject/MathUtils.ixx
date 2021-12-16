module;

export module MathUtils;

/**
Returns a value clamped between the min and max values.
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
*/
export float Clamp01(float value)
{
    return Clamp(value, 0, 1);
}