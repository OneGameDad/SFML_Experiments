#include "PropertyAnimator.hpp"


PropertyAnimator::PropertyAnimator(){}

PropertyAnimator::PropertyAnimator(double a_speedMultiplier)
    : samplingY(0.0f), samplingXOffset(0.0f), speedMultiplier(a_speedMultiplier)
{}

PropertyAnimator::~PropertyAnimator(){}

void PropertyAnimator::reset()
{
    samplingY = rand();
    samplingXOffset = rand();
}
    
float PropertyAnimator::update(bool useScaledTime)
{
    if (useScaledTime)
        return (PerlinNoiseGenerator::Instance().getPerlinNoiseValue(GameTime::getInstance().getDeltaTimeUnscaled() + samplingXOffset, samplingY, speedMultiplier) * 2.0f - 1.0f);
    else
        return (PerlinNoiseGenerator::Instance().getPerlinNoiseValue(GameTime::getInstance().getDeltaTime() + samplingXOffset, samplingY, speedMultiplier) * 2.0f - 1.0f);
}