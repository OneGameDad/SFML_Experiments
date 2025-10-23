#include "PerlinAnimator.hpp"

PerlinAnimator::PerlinAnimator(): APropertyAnimator("Perlin")
{}

PerlinAnimator::PerlinAnimator(double a_speedMultiplier, bool a_useUnscaledTime)
    : APropertyAnimator("Perlin"), samplingY(0.0), samplingXOffset(0.0), speedMultiplier(a_speedMultiplier), useUnscaledTime(a_useUnscaledTime)
{}

PerlinAnimator::~PerlinAnimator(){}
    
void    PerlinAnimator::reset()
{
    samplingXOffset = rand();
    samplingY = rand();
}

float   PerlinAnimator::update()
{
    if (useUnscaledTime)
        return (PerlinNoiseGenerator::Instance().getPerlinNoiseValue(GameTime::getInstance().getCurrrentTimeUnscaled() + samplingXOffset, samplingY, speedMultiplier) * 2.0f - 1.0f);
    else
        return (PerlinNoiseGenerator::Instance().getPerlinNoiseValue(GameTime::getInstance().getCurrentTime() + samplingXOffset, samplingY, speedMultiplier) * 2.0f - 1.0f);
}