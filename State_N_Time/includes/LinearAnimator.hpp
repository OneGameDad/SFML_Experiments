#pragma once

#include <cmath>
#include <cstdlib>
#include "GameTime.hpp"
#include "APropertyAnimator.hpp"

class LinearAnimator: public APropertyAnimator
{
private:
    float   currentValue;
    float   duration;
    bool    useUnscaledTime =  false;

    LinearAnimator();
public:
    LinearAnimator(double a_duration, bool a_useUnscaledTime);
    ~LinearAnimator();

    void    reset();
    float   update();
};