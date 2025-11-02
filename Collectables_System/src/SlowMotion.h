#pragma once

#include "GameTime.h"
#include "InputHandler.h"
#include "Game.h"

class Game;

class SlowMotion
{
private:
    Game* m_pGame;
    GameTime* clock;
    const float regularTime = 1.0f;
    float   slowTime = 0.1f;
    bool    isActive = false;
    const float duration = 3.5f;
    float   elapsed = 0.0f;

    void    reset();
public:
    SlowMotion();
    ~SlowMotion();

    void    activate();
    void    deactivate();
    void    update();
}