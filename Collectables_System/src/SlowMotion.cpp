#include "SlowMotion.h"

SlowMotion::SlowMotion(Game* pGame)
    : m_pGame(pGame)
{}

SlowMotion::~SlowMotion(){}

void    SlowMotion::reset()
{
    if (GameTime::getInstance().getTimeScale() != regularTime || isActive == true)
    {    
        GameTime::getInstance().setTimeScale(regularTime);
        isActive = false;
    }
}

void    SlowMotion::activate()
{
    if (GameTime::getInstance().getTimeScale() != slowTime || isActive == false)
    {
        GameTime::getInstance().setTimeScale(slowTime);
        isActive = true;
    }
}

void    SlowMotion::deactivate()
{
    reset();
}

void    SlowMotion::update()
{
    if (isActive)
    {
        elapsed += GameTime::getInstance().getDeltaTimeUnscaled();
        if (elapsed >= duration)
        {
            reset();
            elapsed = 0.0f;
        }
    }
}