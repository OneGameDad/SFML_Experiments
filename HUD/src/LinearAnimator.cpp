#include "LinearAnimator.h"

LinearAnimator::LinearAnimator() : APropertyAnimator("Linear"), currentValue(0.0)
{}

LinearAnimator::LinearAnimator(double a_duration, bool a_useUnscaledTime)
    : APropertyAnimator("Linear"), currentValue(0.0), duration(a_duration), useUnscaledTime(a_useUnscaledTime)
{}

LinearAnimator::~LinearAnimator(){}

void    LinearAnimator::reset()
{
    currentValue = 0.0;
}

float   LinearAnimator::update()
{
    if (useUnscaledTime)
    {
        currentValue += GameTime::getInstance().getDeltaTimeUnscaled() * duration;
        return (currentValue);
    }
    else
    {
        currentValue += GameTime::getInstance().getDeltaTime() * duration;
        return (currentValue);
    }
}