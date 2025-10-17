#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "BitmapReader.hpp"

float getPerlinNoiseValue(double time, double speedMultiplier)
{
    static const double step = 0.01;
    // Convert time into x/y pixel coordinates
    float x = static_cast<float>((time * step * speedMultiplier) % 1.0);
    float y = static_cast<float>(((floor(time * step) / step) * speedMultiplier) % 1.0);
    
    float val = BitmapReader::Instance.GetFloatUV(x, y);
    return (val);
}