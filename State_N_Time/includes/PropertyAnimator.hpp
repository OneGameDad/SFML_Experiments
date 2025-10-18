#pragma once

#include <cmath>
#include <cstdlib>
#include "PerlinNoiseGenerator.hpp"
#include <SFML/Graphics.hpp>
#include "GameTime.hpp"

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
    float update(bool useUnscaledTime);
};