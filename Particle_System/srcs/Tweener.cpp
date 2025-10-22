#include "Tweener.hpp"
#include <cmath>

Tweener::Tweener(float a_start, float a_end, float a_duration, APropertyAnimator *a_animator)
    : start(a_start), end(a_end), duration(a_duration)
{
    animator = a_animator;
}

Tweener::~Tweener()
{
    delete animator;
}

void    Tweener::reset()
{
    currentTime = 0.0f;
}

void    Tweener::play()
{
    if (!isPlaying)
    {
        isPlaying = true;
        std::cout << "Tweener isPlaying = True\n";
    }
}

inline float lerp(float a, float b, float t)
{
    return (a + t * (b - a));
}

float    Tweener::update()
{
    if (isPlaying)
    {
        currentTime += GameTime::getInstance().getDeltaTime();
        std::cout << "Duration: " << duration << " CurrentTime: " << currentTime << std::endl;
        if (currentTime >= duration)
        {
            isPlaying = false;
            std::cout << "Tweener isPlaying = False\n";
            return (end);
        }
        float t = animator->update();
        float output = lerp(start, end, t);
        return (output);
    }
    return (start);
}

bool    Tweener::getIsPlaying() const { return (isPlaying); }

void    Tweener::restart(float a_start, float a_end, float a_duration)
{
    start = a_start;
    end = a_end;
    duration = a_duration;
}