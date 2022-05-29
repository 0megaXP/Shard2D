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

#pragma once

#include <math.h>
#include "../Utils/MathVectors.h"

namespace Shard2D
{
	class MathUtils
	{
	public:
        /**
        Returns a value clamped between the min and max values.
            \param value: The value to clamp.
            \param min: The min value.
            \param max: The max value.
        */
		static float Clamp(float value, float min, float max);
        /**
        Returns a value clamped between 0 and 1. If lower than 0, returns 0. If greater than 1, returns 1.
            \param value: The value to clamp.
        */
        static float Clamp01(float value);
        /**
        Returns a value rounded to zero if it is lower than 0.0001 or higher than -0.0001.
        */
        static float RoundToZero(float value);
        /**
        Returns the legnth of the distance between 2 Vector2.
        */
        static float Distance(const Vector2& a, const Vector2& b);
        /**
        Returns the position inside a circumference of the given rotation as radians.
        */
        static Vector2 PositionFromRad(float rotation);
        /**
        Returns the position inside a circumference of the given rotation as degrees.
        */
        static Vector2 PositionFromDeg(float rotation);
        /**
        Returns the rotation as degree at a certain position of a circumference with the given centre.
        */
        static float DegFromPosition(Vector2 position, Vector2 centre);
        /**
        Generate a rect with the given informations.
        */
        static void GenerateRect(Vector2* rectPoints, Vector2 origin, float width, float height, float rotation, bool centerPivot);
        /**
        Checks if the given point is inside the rect created with the given origin point, width, height and rotation.
        */
        static bool PointInsideRect(Vector2 point, Vector2 origin, float width, float height, float rotation, bool centerPivot);
	};
}

