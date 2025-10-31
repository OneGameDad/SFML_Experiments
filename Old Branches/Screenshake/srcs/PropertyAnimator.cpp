#include "PropertyAnimator.hpp"
#include "SFML/Graphics.hpp"

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
    
float PropertyAnimator::update(double t)
{
    return (PerlinNoiseGenerator::Instance().getPerlinNoiseValue(t + samplingXOffset, samplingY, speedMultiplier) * 2.0f - 1.0f);
}