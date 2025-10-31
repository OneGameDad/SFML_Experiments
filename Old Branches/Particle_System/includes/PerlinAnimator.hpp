#pragma once

#include <cmath>
#include <cstdlib>
#include "PerlinNoiseGenerator.hpp"
#include <SFML/Graphics.hpp>
#include "GameTime.hpp"
#include "APropertyAnimator.hpp"

class PerlinAnimator: public APropertyAnimator
{
private:
    float   samplingY;
    float   samplingXOffset;
    float   speedMultiplier;
    bool    useUnscaledTime = false;

    PerlinAnimator();
public:
    PerlinAnimator(double a_speedMultiplier, bool a_useUnscaledTime);
    ~PerlinAnimator();
    
    void    reset();
    float   update();
};