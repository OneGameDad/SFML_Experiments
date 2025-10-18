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
    
float PropertyAnimator::update(bool useUnscaledTime)
{
    if (useUnscaledTime)
        return (PerlinNoiseGenerator::Instance().getPerlinNoiseValue(GameTime::getInstance().getCurrrentTimeUnscaled() + samplingXOffset, samplingY, speedMultiplier) * 2.0f - 1.0f);
    else
        return (PerlinNoiseGenerator::Instance().getPerlinNoiseValue(GameTime::getInstance().getCurrentTime() + samplingXOffset, samplingY, speedMultiplier) * 2.0f - 1.0f);
}