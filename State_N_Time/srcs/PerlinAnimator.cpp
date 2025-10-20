#include "PerlinAnimator.hpp"

PerlinAnimator::PerlinAnimator(): APropertyAnimator("Perlin")
{}

PerlinAnimator::PerlinAnimator(double a_speedMultiplier)
    : APropertyAnimator("Perlin"), samplingY(0.0), samplingXOffset(0.0), speedMultiplier(a_speedMultiplier)
{}

PerlinAnimator::~PerlinAnimator(){}
    
void    PerlinAnimator::reset()
{
    samplingXOffset = rand();
    samplingY = rand();
}

float   PerlinAnimator::update(bool useUnscaledTime)
{
    if (useUnscaledTime)
        return (PerlinNoiseGenerator::Instance().getPerlinNoiseValue(GameTime::getInstance().getDeltaTimeUnscaled() + samplingXOffset, samplingY, speedMultiplier) * 2.0f - 1.0f);
    else
        return (PerlinNoiseGenerator::Instance().getPerlinNoiseValue(GameTime::getInstance().getDeltaTime() + samplingXOffset, samplingY, speedMultiplier) * 2.0f - 1.0f);
}