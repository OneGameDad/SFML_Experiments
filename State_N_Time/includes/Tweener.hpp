#pragma once

#include "APropertyAnimator.hpp"
#include "LinearAnimator.hpp"
#include "GameTime.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>

class Tweener
{
private:
    APropertyAnimator   *animator;
    float   start;
    float   end;
    float   duration;
    float   currentTime = 0.0f;
    bool    useUnscaledTime = false;
    bool    isPlaying = false;

public:
    Tweener(float a_start, float a_end, float a_duration, APropertyAnimator *a_animator);
    ~Tweener();

    void    reset();
    void    play();
    float   update();
    bool    getIsPlaying() const;
    void    restart(float a_start, float a_end, float a_duration);
};