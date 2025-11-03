#pragma once

#include <cmath>
#include <cstdlib>
#include "PerlinNoiseGenerator.h"
#include <SFML/Graphics.hpp>
#include "GameTime.h"
#include "APropertyAnimator.h"

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