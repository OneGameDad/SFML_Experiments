#pragma once

#include "APropertyAnimator.h"
#include "LinearAnimator.h"
#include "GameTime.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <memory>

class Tweener
{
private:
    std::unique_ptr<APropertyAnimator> animator;
    float   start;
    float   end;
    float   duration;
    float   currentTime = 0.0f;
    bool    useUnscaledTime = false;
    bool    isPlaying = false;

public:
    Tweener(float a_start, float a_end, float a_duration, std::unique_ptr<APropertyAnimator> a_animator);
    ~Tweener();

    void    reset();
    void    play();
    float   update();
    bool    getIsPlaying() const;
    void    restart(float a_start, float a_end, float a_duration);
};