module;

export module MathUtils;

export float Clamp(float value, float min, float max)
{
    if (value > max)
        return max;
    else if (value < min)
        return min;
    else
        return value;
}

export float Clamp01(float value)
{
    return Clamp(value, 0, 1);
}