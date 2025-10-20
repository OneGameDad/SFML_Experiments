#include "LinearAnimator.hpp"

LinearAnimator::LinearAnimator() : APropertyAnimator("Linear"), offset(0.0)
{}

LinearAnimator::LinearAnimator(double a_speedMultiplier)
    : APropertyAnimator("Linear"), offset(0.0), speedMultiplier(a_speedMultiplier)
{}

LinearAnimator::~LinearAnimator(){}

void    LinearAnimator::reset()
{
    offset = 0.0;
}

float   LinearAnimator::update(bool useUnscaledTime, bool useModulo) //TODO Fix calculation
{
    if (useModulo)
    {
        if (useUnscaledTime)
            return (GameTime::getInstance().getDeltaTimeUnscaled() + offset, speedMultiplier);
        else
            return (GameTime::getInstance().getDeltaTime() + offset, speedMultiplier);
    }
    if (useUnscaledTime)
        return (GameTime::getInstance().getDeltaTimeUnscaled() + offset, speedMultiplier);
    else
        return (GameTime::getInstance().getDeltaTime() + offset, speedMultiplier);
}