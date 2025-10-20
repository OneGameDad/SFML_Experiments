#pragma once

#include <cmath>
#include <cstdlib>
#include "PerlinNoiseGenerator.hpp"
#include <SFML/Graphics.hpp>
#include "GameTime.hpp"
#include "APropteryAnimator.hpp"

class PerlinAnimator: public APropertyAnimator
{
private:
    float samplingY;
    float samplingXOffset;
    float speedMultiplier;

public:
    PerlinAnimator();
    PerlinAnimator(double a_speedMultiplier);
    ~PerlinAnimator();
    
    void    reset();
    float   update(bool useUnscaledTime);
};