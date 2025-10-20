#pragma once

#include <cmath>
#include <cstdlib>
#include "GameTime.hpp"
#include "APropteryAnimator.hpp"

class LinearAnimator: public APropertyAnimator
{
private:
    float   offset;
    float   speedMultiplier;

public:
    LinearAnimator();
    LinearAnimator(double a_speedMultiplier);
    ~LinearAnimator();

    void    reset();
    float   update(bool useUnscaledTime, bool useModulo);
};