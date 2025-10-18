#pragma once

#include <cmath>
#include <cstdlib>
#include "PerlinNoiseGenerator.hpp"

class PropertyAnimator
{
private:
    float samplingY;
    float samplingXOffset;
    float speedMultiplier;

public:
    PropertyAnimator();
    PropertyAnimator(double a_speedMultiplier);
    ~PropertyAnimator();
    
    void reset();
    float update(double t);
};